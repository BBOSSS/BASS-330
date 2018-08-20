
// BASS-330Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BASS-330.h"
#include "BASS-330Dlg.h"
#include "ProtocolHandle.h"
#include "IniFile.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CBASS330Dlg 对话框




CBASS330Dlg::CBASS330Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBASS330Dlg::IDD, pParent)
	, m_bIsOpenSerl(0)
	, m_bRecvPacketTail(false)
	, m_pDeviceInitThread(NULL)
	, m_pClearRecordThread(NULL)
	, m_pClearListThread(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_TOOL_ICON);
}

void CBASS330Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SERIES, m_comboSeries);
	DDX_Control(pDX, IDC_TAB, m_tab);
	DDX_Control(pDX, IDC_EDIT_RX, m_EdSerlRecv);
	DDX_Control(pDX, IDC_EDIT_TX, m_EdSerlSend);
}

BEGIN_MESSAGE_MAP(CBASS330Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CBASS330Dlg::OnTcnSelchangeTab)
	ON_STN_CLICKED(IDC_STATIC_DEBUG, &CBASS330Dlg::OnStnClickedStaticDebug)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, &CBASS330Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_CLOSE, &CBASS330Dlg::OnBnClickedButtonOpenOrClose)
	ON_MESSAGE(WM_COMM_RXCHAR, &CBASS330Dlg::FSerialRecv)
	ON_BN_CLICKED(IDC_BUTTON_RX, &CBASS330Dlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_TX, &CBASS330Dlg::OnBnClickedButtonTx)
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CBASS330Dlg::OnBnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CBASS330Dlg::OnBnClickedButtonClearRecord)
	ON_BN_CLICKED(IDC_BUTTON_CLEARLIST, &CBASS330Dlg::OnBnClickedButtonClearlist)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR2M, &CBASS330Dlg::OnBnClickedButtonClearList2M)
END_MESSAGE_MAP()


// CBASS330Dlg 消息处理程序

BOOL CBASS330Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 初始化主窗口全局指针
	pMainDlg = this;
		
	GetWindowRect(&m_AllRect);		// 获取主区域和调试区域的大小
	GetDlgItem(IDC_GROUP_MAIN)->GetWindowRect(&m_MainRect);
	OnStnClickedStaticDebug();		// 设置初始区域显示

	// 判断是否存在ini文件
	CIniFile iniFile;
	std::vector<CIniFile::Record> contents;
	if( !iniFile.Load("BASS330.ini", contents) )
	{
		iniFile.Create("BASS330.ini");
	}

	// 串口COM口选择初始化 
    FInitSerial();

	// Tab控件初始化 
	CRect tabRect;									// 标签控件客户区的位置和大小   
    m_tab.InsertItem(0, _T("参数配置一"));			// 插入第1个标签
    m_tab.InsertItem(1, _T("参数配置二"));			// 插入第2个标签
	m_tab.InsertItem(2, _T("参数配置三"));			// 插入第3个标签
    m_tab.InsertItem(3, _T("通道与名单设置"));	// 插入第4个标签
	m_tab.InsertItem(4, _T("GPRS通信"));			// 插入第5个标签
    m_tab.InsertItem(5, _T("采集和输出信息"));	// 插入第6个标签
	m_tab.InsertItem(6, _T("操作页面"));			// 插入第7个标签

    m_param1.Create(IDD_DIALOG_PARAM1, &m_tab);     // 创建第1个标签页   
    m_param2.Create(IDD_DIALOG_PARAM2, &m_tab);		// 创建第2个标签页
	m_param3.Create(IDD_DIALOG_PARAM3, &m_tab);		// 创建第3个标签页  
	m_param4.Create(IDD_DIALOG_PARAM4, &m_tab);		// 创建第4个标签页  
	m_param5.Create(IDD_DIALOG_PARAM5, &m_tab);		// 创建第5个标签页  
	m_param6.Create(IDD_DIALOG_PARAM6, &m_tab);		// 创建第6个标签页  
	m_param7.Create(IDD_DIALOG_PARAM7, &m_tab);		// 创建第7个标签页  
    m_tab.GetClientRect(&tabRect);					// 获取标签控件客户区Rect   
    // 调整tabRect，使其覆盖范围适合放置标签页   
    tabRect.left += 1;                  
    tabRect.right -= 1;   
    tabRect.top += 25;   
    tabRect.bottom -= 1;   
    // 根据调整好的tabRect放置子对话框，并设置为显示/隐藏  
    m_param1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);     
    m_param2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
	m_param3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_param4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_param5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_param6.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_param7.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW); //
	m_tab.SetCurSel( 6 );	 //  初始化显示操作页面标签
												
	InitRingBuffer(&m_RecvBuf, RECV_SIZE);						// 初始化环形缓冲区
							
	m_hSemaphore = CreateSemaphore(NULL, 0, 1, "BufferSenmap");	// 缓冲区信号量(接收满一帧则释放)

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBASS330Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

//  如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBASS330Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBASS330Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 初始化 串口
INT32 CBASS330Dlg::FInitSerial()
{
	m_comboSeries.AddString(_T("COM1"));     
    m_comboSeries.AddString(_T("COM2"));   
    m_comboSeries.AddString(_T("COM3"));     
    m_comboSeries.AddString(_T("COM4"));
	m_comboSeries.AddString(_T("COM5"));     
    m_comboSeries.AddString(_T("COM6"));   
    m_comboSeries.AddString(_T("COM7"));     
    m_comboSeries.AddString(_T("COM8"));
	m_comboSeries.AddString(_T("COM9"));
    m_comboSeries.SetCurSel( 7 );		// 默认选择第8项
	return 0;
}
// 打开串口
INT32 CBASS330Dlg::FSerialOpen()
{
	UINT  unPortName;  
    unPortName = m_comboSeries.GetCurSel()+1;	//获取串口号  
    if(!m_bIsOpenSerl)
    {
		if(m_CSerl.InitPort(this, unPortName, 9600, 'N', 8, 0))//0 = 1 1=1.5 2=2  
		{                           
			//打开串口成功
			m_CSerl.StartMonitoring();
			m_bIsOpenSerl = TRUE;
			//修改状态
			GetDlgItem(IDC_COMBO_SERIES)->EnableWindow(FALSE);
			SetDlgItemText(IDC_BUTTON_OPEN_CLOSE, _T("关闭串口"));
		}
        else
        {         
            MessageBox("没有发现此串口或被占用!\r\nDefault Config：Baud 9600,DataBits 8,Parity N, StopBits 0", "提示", MB_ICONWARNING);
            return -1;
        }
    }
    else
    {
		MessageBox("此串口已打开或被占用!", "提示", MB_ICONWARNING);
		return -1;
    }

    return 0;
}
// 关闭串口
INT32 CBASS330Dlg::FSerialClose()
{
	if (m_bIsOpenSerl)
	{
		//关闭串口
		m_CSerl.ClosePort();
		m_bIsOpenSerl = FALSE;

		//修改状态
		GetDlgItem(IDC_COMBO_SERIES)->EnableWindow(TRUE);
		SetDlgItemText(IDC_BUTTON_OPEN_CLOSE, _T("打开串口"));
	}
	else
	{
		MessageBox("没有串口被打开!", "提示", MB_ICONWARNING);
		return -1;
	}

	return 0;
}

// 打开或关闭串口按钮处理函数
void CBASS330Dlg::OnBnClickedButtonOpenOrClose()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_bIsOpenSerl)
		FSerialClose();
	else
		FSerialOpen();
}

// 串口接收处理函数
LONG CBASS330Dlg::FSerialRecv(WPARAM ch, LPARAM port)
{
	int nDataLen = 0;
	int nReadLen;
	BYTE RecvChar = ch;
	CString CH;
	CH.Format("%02X", ch);
	CH += " ";
	int len = m_EdSerlRecv.GetWindowTextLength();
	m_EdSerlRecv.SetSel(len, len);		//将插入光标放在最后
	m_EdSerlRecv.ReplaceSel(CH);
	m_EdSerlRecv.ScrollWindow(0, 0);	//滚动到插入点
	nDataLen = RingBufferLen(&m_RecvBuf);
	if(0 == nDataLen)
	{
		RingBufferFlush(&m_RecvBuf);
	}
	nReadLen = RingBufferWriteMax(&m_RecvBuf);
	if(nReadLen <= 0)
	{
		return -1;
	}
	if(TRUE != RingBufferWrite((unsigned char *)&ch, 1, &m_RecvBuf))
	{
		TRACE("RingBufferWrite Error!\n");
	}

	if(RecvChar == 0xFE) // 包尾标志
	{
		m_bRecvPacketTail = true;
		ReleaseSemaphore(m_hSemaphore, 1, NULL);
		TRACE("Get Packet Tail, Release Semaphore \r\n");
	}

	return 0;
}

// 串口发送函数
VOID CBASS330Dlg::FSerialSend(UINT8 *pSendData, UINT16 usLen)
{
	RingBufferFlush(&m_RecvBuf);
	m_bRecvPacketTail = false;
	m_CSerl.WriteToPort(pSendData, usLen);	//发送数据
	CString CH;
	for(int i = 0; i < usLen; i++)
	{
		CString temp;
		temp.Format("%02X", *pSendData++);
		CH += temp;
		CH += " ";
	}
	CH += "\r\n";
	//CH.Format("%s", pSendData);
	int len = m_EdSerlSend.GetWindowTextLength();
	m_EdSerlSend.SetSel(len, len);			//将插入光标放在最后
	m_EdSerlSend.ReplaceSel(CH);
	m_EdSerlSend.ScrollWindow(0, 0);		//滚动到插入点
}

// 清空接收框
void CBASS330Dlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EdSerlRecv.SetSel(0, -1);
	m_EdSerlRecv.Clear();
}
// 确认发送按钮
void CBASS330Dlg::OnBnClickedButtonTx()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bIsOpenSerl) 
	{
		MessageBox("请先打开串口!", "提示", MB_ICONWARNING);
		return;
	}
	CString SendText;
	m_EdSerlSend.GetWindowText(SendText);

	FSerialSend( (UINT8*)(SendText.GetBuffer(0)), SendText.GetLength() );
}


//切换标签页
void CBASS330Dlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CRect tabRect;    // 标签控件客户区的Rect   
    // 获取标签控件客户区Rect，并对其调整，以适合放置标签页   
    m_tab.GetClientRect(&tabRect);   
    tabRect.left += 1;   
    tabRect.right -= 1;   
    tabRect.top += 25;   
    tabRect.bottom -= 1;   
  
    switch (m_tab.GetCurSel())   
    {   
		// 如果标签控件当前选择标签为“参数配置一”，则显示该对话框，隐藏其余对话框   
		case 0:   
			m_param1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);//   
			m_param2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param6.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param7.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			break;   
		// 如果标签控件当前选择标签为“参数配置二”，则显示该对话框，隐藏其余对话框   
		case 1:   
			m_param1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
			m_param2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);//
			m_param3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param6.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param7.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			break;  
		case 2:   
			m_param1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
			m_param2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);//
			m_param4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param6.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param7.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			break;
		case 3:   
			m_param1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
			m_param2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);//
			m_param5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param6.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param7.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			break;
		case 4:   
			m_param1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
			m_param2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);//
			m_param6.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param7.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			break;
		case 5:   
			m_param1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
			m_param2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param6.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);//
			m_param7.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			break;
		case 6:   
			m_param1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
			m_param2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param6.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param7.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);//
			break;
		default:   
			break;   
    }   
}

// 调试窗口收缩处理函数
void CBASS330Dlg::OnStnClickedStaticDebug()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
    if (GetDlgItemText(IDC_STATIC_DEBUG, str), str == _T("\n\n\n\n\n\n\n\n\n\n>\n>\n>"))
		SetDlgItemText(IDC_STATIC_DEBUG, _T("\n\n\n\n\n\n\n\n\n\n<\n<\n<"));
    else
		SetDlgItemText(IDC_STATIC_DEBUG, _T("\n\n\n\n\n\n\n\n\n\n>\n>\n>"));
    CRect rtSmall;
    rtSmall.SetRectEmpty();
    if (rtSmall.IsRectEmpty())
    {
        rtSmall.left = m_AllRect.left;
        rtSmall.top = m_AllRect.top;
        rtSmall.right = m_MainRect.right+30;
        rtSmall.bottom = m_AllRect.bottom;
    }
    if (str == "\n\n\n\n\n\n\n\n\n\n<\n<\n<")
        SetWindowPos(NULL, 0, 0, rtSmall.Width(), rtSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);
    else
        SetWindowPos(NULL, 0, 0, m_AllRect.Width(), m_AllRect.Height(), SWP_NOMOVE | SWP_NOZORDER);
}

// 按红叉键退出时提示
void CBASS330Dlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	INT_PTR nRes;   
    // 显示消息对话框   
    nRes = MessageBox(_T("确定退出程序吗？"), _T("退出确认"), MB_OKCANCEL | MB_ICONQUESTION);   
    // 判断消息对话框返回值。如果为IDCANCEL就return，否则继续向下执行   
    if (IDCANCEL == nRes)   
        return;
	if(m_bIsOpenSerl)
		FSerialClose( );	// 关闭串口

	pSubDlg7->StopAllTimer();

	DeInitRingBuffer(&m_RecvBuf);

	CDialog::OnClose();
}

// 按退出键退出时提示
void CBASS330Dlg::OnBnClickedCancel()
{
	INT_PTR nRes;   
    // 显示消息对话框   
    nRes = MessageBox(_T("确定退出程序吗？"), _T("退出确认"), MB_OKCANCEL | MB_ICONQUESTION);   
    // 判断消息对话框返回值。如果为IDCANCEL就return，否则继续向下执行   
    if (IDCANCEL == nRes)   
        return;
	if(m_bIsOpenSerl)
		FSerialClose( );	// 关闭串口

	pSubDlg7->StopAllTimer();

	DeInitRingBuffer(&m_RecvBuf);

	OnCancel();
}


void CBASS330Dlg::OnBnClickedButtonInit()
{
	if( !m_bIsOpenSerl )
	{
		MessageBox("请先打开串口!", "提示", MB_ICONWARNING);
		return;
	}
	if(IDCANCEL == MessageBox("将初始化所有参数，确认吗？", "提示", MB_OKCANCEL | MB_ICONQUESTION))
        return ;
	if(m_pDeviceInitThread)
    {
        ::TerminateThread(m_pDeviceInitThread->m_hThread, 0);
        m_pDeviceInitThread = NULL;
    }
	m_pDeviceInitThread = AfxBeginThread(DeviceInitThread, this);
}

UINT CBASS330Dlg::DeviceInitThread(LPVOID pParam)
{
	CProtocolHandle ComProto;
	BYTE RecvBuffer[PACKET_SIZE] = {0};
	int length = ComProto.Package(0x02, NULL, 0);
	pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// 发送数据

	WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// 等待串口接收完成一帧数据
	if(pMainDlg->m_bRecvPacketTail == false)						// 检查标志位 超过3秒没收到包尾
	{
		TRACE("Receive overtime!\n");
		AfxMessageBox("设备初始化失败！");
		return FALSE;
	}
	int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
	RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));

	if(FALSE == ComProto.isVaildPacket(0x02, RecvBuffer, RecvBufLen))
	{
		AfxMessageBox("设备初始化失败！");
		return FALSE;
	}
	pMainDlg->MessageBox("设备初始化成功！", "提示", MB_ICONINFORMATION);
	return TRUE;
}

void CBASS330Dlg::OnBnClickedButtonClearRecord()
{
	if( !m_bIsOpenSerl )
	{
		MessageBox("请先打开串口!", "提示", MB_ICONWARNING);
		return;
	}
	if(IDCANCEL == MessageBox("将清除所有门禁记录，确认吗？", "提示", MB_OKCANCEL | MB_ICONQUESTION))
        return;
	if(m_pClearRecordThread)
    {
        ::TerminateThread(m_pClearRecordThread->m_hThread, 0);
        m_pClearRecordThread = NULL;
    }
	m_pClearRecordThread = AfxBeginThread(ClearRecordThread, this);
}

UINT CBASS330Dlg::ClearRecordThread(LPVOID pParam)
{
	CProtocolHandle ComProto;
	BYTE RecvBuffer[PACKET_SIZE] = {0};
	int length = ComProto.Package(0x35, NULL, 0);
	pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// 发送数据

	WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// 等待串口接收完成一帧数据
	if(pMainDlg->m_bRecvPacketTail == false)						// 检查标志位 超过3秒没收到包尾
	{
		TRACE("Receive overtime!\n");
		AfxMessageBox("清除门禁记录失败！");
		return FALSE;
	}
	int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
	RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));

	if(FALSE == ComProto.isVaildPacket(0x35, RecvBuffer, RecvBufLen))
	{
		AfxMessageBox("清除门禁记录失败失败！");
		return FALSE;
	}
	pMainDlg->MessageBox("清除门禁记录成功！", "提示", MB_ICONINFORMATION);
	return TRUE;
}


void CBASS330Dlg::OnBnClickedButtonClearlist()
{
	if( !m_bIsOpenSerl )
	{
		MessageBox("请先打开串口!", "提示", MB_ICONWARNING);
		return;
	}
	if(IDCANCEL == MessageBox("将清除黑白名单，确认吗？", "提示", MB_OKCANCEL | MB_ICONQUESTION))
        return;
	if(m_pClearListThread)
    {
        ::TerminateThread(m_pClearListThread->m_hThread, 0);
        m_pClearListThread = NULL;
    }
	m_pClearListThread = AfxBeginThread(ClearListThread, this);
}

UINT CBASS330Dlg::ClearListThread(LPVOID pParam)
{
	CProtocolHandle ComProto;
	BYTE RecvBuffer[PACKET_SIZE] = {0};
	int length = ComProto.Package(0x38, NULL, 0);
	pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// 发送数据

	WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// 等待串口接收完成一帧数据
	if(pMainDlg->m_bRecvPacketTail == false)						// 检查标志位 超过3秒没收到包尾
	{
		TRACE("Receive overtime!\n");
		AfxMessageBox("清除门禁记录失败！");
		return FALSE;
	}
	int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
	RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));

	if(FALSE == ComProto.isVaildPacket(0x38, RecvBuffer, RecvBufLen))
	{
		AfxMessageBox("清除门禁记录失败失败！");
		return FALSE;
	}
	pMainDlg->MessageBox("清除门禁记录成功！", "提示", MB_ICONINFORMATION);
	return TRUE;
}

void CBASS330Dlg::OnBnClickedButtonClearList2M()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox("TODO: 2M版本功能尚未实现", "提示", MB_ICONINFORMATION);
}
