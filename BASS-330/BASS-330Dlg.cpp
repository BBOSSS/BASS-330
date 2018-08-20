
// BASS-330Dlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CBASS330Dlg �Ի���




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


// CBASS330Dlg ��Ϣ�������

BOOL CBASS330Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	// ��ʼ��������ȫ��ָ��
	pMainDlg = this;
		
	GetWindowRect(&m_AllRect);		// ��ȡ������͵�������Ĵ�С
	GetDlgItem(IDC_GROUP_MAIN)->GetWindowRect(&m_MainRect);
	OnStnClickedStaticDebug();		// ���ó�ʼ������ʾ

	// �ж��Ƿ����ini�ļ�
	CIniFile iniFile;
	std::vector<CIniFile::Record> contents;
	if( !iniFile.Load("BASS330.ini", contents) )
	{
		iniFile.Create("BASS330.ini");
	}

	// ����COM��ѡ���ʼ�� 
    FInitSerial();

	// Tab�ؼ���ʼ�� 
	CRect tabRect;									// ��ǩ�ؼ��ͻ�����λ�úʹ�С   
    m_tab.InsertItem(0, _T("��������һ"));			// �����1����ǩ
    m_tab.InsertItem(1, _T("�������ö�"));			// �����2����ǩ
	m_tab.InsertItem(2, _T("����������"));			// �����3����ǩ
    m_tab.InsertItem(3, _T("ͨ������������"));	// �����4����ǩ
	m_tab.InsertItem(4, _T("GPRSͨ��"));			// �����5����ǩ
    m_tab.InsertItem(5, _T("�ɼ��������Ϣ"));	// �����6����ǩ
	m_tab.InsertItem(6, _T("����ҳ��"));			// �����7����ǩ

    m_param1.Create(IDD_DIALOG_PARAM1, &m_tab);     // ������1����ǩҳ   
    m_param2.Create(IDD_DIALOG_PARAM2, &m_tab);		// ������2����ǩҳ
	m_param3.Create(IDD_DIALOG_PARAM3, &m_tab);		// ������3����ǩҳ  
	m_param4.Create(IDD_DIALOG_PARAM4, &m_tab);		// ������4����ǩҳ  
	m_param5.Create(IDD_DIALOG_PARAM5, &m_tab);		// ������5����ǩҳ  
	m_param6.Create(IDD_DIALOG_PARAM6, &m_tab);		// ������6����ǩҳ  
	m_param7.Create(IDD_DIALOG_PARAM7, &m_tab);		// ������7����ǩҳ  
    m_tab.GetClientRect(&tabRect);					// ��ȡ��ǩ�ؼ��ͻ���Rect   
    // ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ   
    tabRect.left += 1;                  
    tabRect.right -= 1;   
    tabRect.top += 25;   
    tabRect.bottom -= 1;   
    // ���ݵ����õ�tabRect�����ӶԻ��򣬲�����Ϊ��ʾ/����  
    m_param1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);     
    m_param2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
	m_param3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_param4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_param5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_param6.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_param7.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW); //
	m_tab.SetCurSel( 6 );	 //  ��ʼ����ʾ����ҳ���ǩ
												
	InitRingBuffer(&m_RecvBuf, RECV_SIZE);						// ��ʼ�����λ�����
							
	m_hSemaphore = CreateSemaphore(NULL, 0, 1, "BufferSenmap");	// �������ź���(������һ֡���ͷ�)

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

//  �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBASS330Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBASS330Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ��ʼ�� ����
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
    m_comboSeries.SetCurSel( 7 );		// Ĭ��ѡ���8��
	return 0;
}
// �򿪴���
INT32 CBASS330Dlg::FSerialOpen()
{
	UINT  unPortName;  
    unPortName = m_comboSeries.GetCurSel()+1;	//��ȡ���ں�  
    if(!m_bIsOpenSerl)
    {
		if(m_CSerl.InitPort(this, unPortName, 9600, 'N', 8, 0))//0 = 1 1=1.5 2=2  
		{                           
			//�򿪴��ڳɹ�
			m_CSerl.StartMonitoring();
			m_bIsOpenSerl = TRUE;
			//�޸�״̬
			GetDlgItem(IDC_COMBO_SERIES)->EnableWindow(FALSE);
			SetDlgItemText(IDC_BUTTON_OPEN_CLOSE, _T("�رմ���"));
		}
        else
        {         
            MessageBox("û�з��ִ˴��ڻ�ռ��!\r\nDefault Config��Baud 9600,DataBits 8,Parity N, StopBits 0", "��ʾ", MB_ICONWARNING);
            return -1;
        }
    }
    else
    {
		MessageBox("�˴����Ѵ򿪻�ռ��!", "��ʾ", MB_ICONWARNING);
		return -1;
    }

    return 0;
}
// �رմ���
INT32 CBASS330Dlg::FSerialClose()
{
	if (m_bIsOpenSerl)
	{
		//�رմ���
		m_CSerl.ClosePort();
		m_bIsOpenSerl = FALSE;

		//�޸�״̬
		GetDlgItem(IDC_COMBO_SERIES)->EnableWindow(TRUE);
		SetDlgItemText(IDC_BUTTON_OPEN_CLOSE, _T("�򿪴���"));
	}
	else
	{
		MessageBox("û�д��ڱ���!", "��ʾ", MB_ICONWARNING);
		return -1;
	}

	return 0;
}

// �򿪻�رմ��ڰ�ť������
void CBASS330Dlg::OnBnClickedButtonOpenOrClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_bIsOpenSerl)
		FSerialClose();
	else
		FSerialOpen();
}

// ���ڽ��մ�����
LONG CBASS330Dlg::FSerialRecv(WPARAM ch, LPARAM port)
{
	int nDataLen = 0;
	int nReadLen;
	BYTE RecvChar = ch;
	CString CH;
	CH.Format("%02X", ch);
	CH += " ";
	int len = m_EdSerlRecv.GetWindowTextLength();
	m_EdSerlRecv.SetSel(len, len);		//��������������
	m_EdSerlRecv.ReplaceSel(CH);
	m_EdSerlRecv.ScrollWindow(0, 0);	//�����������
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

	if(RecvChar == 0xFE) // ��β��־
	{
		m_bRecvPacketTail = true;
		ReleaseSemaphore(m_hSemaphore, 1, NULL);
		TRACE("Get Packet Tail, Release Semaphore \r\n");
	}

	return 0;
}

// ���ڷ��ͺ���
VOID CBASS330Dlg::FSerialSend(UINT8 *pSendData, UINT16 usLen)
{
	RingBufferFlush(&m_RecvBuf);
	m_bRecvPacketTail = false;
	m_CSerl.WriteToPort(pSendData, usLen);	//��������
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
	m_EdSerlSend.SetSel(len, len);			//��������������
	m_EdSerlSend.ReplaceSel(CH);
	m_EdSerlSend.ScrollWindow(0, 0);		//�����������
}

// ��ս��տ�
void CBASS330Dlg::OnBnClickedButtonClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_EdSerlRecv.SetSel(0, -1);
	m_EdSerlRecv.Clear();
}
// ȷ�Ϸ��Ͱ�ť
void CBASS330Dlg::OnBnClickedButtonTx()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_bIsOpenSerl) 
	{
		MessageBox("���ȴ򿪴���!", "��ʾ", MB_ICONWARNING);
		return;
	}
	CString SendText;
	m_EdSerlSend.GetWindowText(SendText);

	FSerialSend( (UINT8*)(SendText.GetBuffer(0)), SendText.GetLength() );
}


//�л���ǩҳ
void CBASS330Dlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect   
    // ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ   
    m_tab.GetClientRect(&tabRect);   
    tabRect.left += 1;   
    tabRect.right -= 1;   
    tabRect.top += 25;   
    tabRect.bottom -= 1;   
  
    switch (m_tab.GetCurSel())   
    {   
		// �����ǩ�ؼ���ǰѡ���ǩΪ����������һ��������ʾ�öԻ�����������Ի���   
		case 0:   
			m_param1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);//   
			m_param2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param3.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param4.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param5.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param6.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			m_param7.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
			break;   
		// �����ǩ�ؼ���ǰѡ���ǩΪ���������ö���������ʾ�öԻ�����������Ի���   
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

// ���Դ�������������
void CBASS330Dlg::OnStnClickedStaticDebug()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

// �������˳�ʱ��ʾ
void CBASS330Dlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	INT_PTR nRes;   
    // ��ʾ��Ϣ�Ի���   
    nRes = MessageBox(_T("ȷ���˳�������"), _T("�˳�ȷ��"), MB_OKCANCEL | MB_ICONQUESTION);   
    // �ж���Ϣ�Ի��򷵻�ֵ�����ΪIDCANCEL��return�������������ִ��   
    if (IDCANCEL == nRes)   
        return;
	if(m_bIsOpenSerl)
		FSerialClose( );	// �رմ���

	pSubDlg7->StopAllTimer();

	DeInitRingBuffer(&m_RecvBuf);

	CDialog::OnClose();
}

// ���˳����˳�ʱ��ʾ
void CBASS330Dlg::OnBnClickedCancel()
{
	INT_PTR nRes;   
    // ��ʾ��Ϣ�Ի���   
    nRes = MessageBox(_T("ȷ���˳�������"), _T("�˳�ȷ��"), MB_OKCANCEL | MB_ICONQUESTION);   
    // �ж���Ϣ�Ի��򷵻�ֵ�����ΪIDCANCEL��return�������������ִ��   
    if (IDCANCEL == nRes)   
        return;
	if(m_bIsOpenSerl)
		FSerialClose( );	// �رմ���

	pSubDlg7->StopAllTimer();

	DeInitRingBuffer(&m_RecvBuf);

	OnCancel();
}


void CBASS330Dlg::OnBnClickedButtonInit()
{
	if( !m_bIsOpenSerl )
	{
		MessageBox("���ȴ򿪴���!", "��ʾ", MB_ICONWARNING);
		return;
	}
	if(IDCANCEL == MessageBox("����ʼ�����в�����ȷ����", "��ʾ", MB_OKCANCEL | MB_ICONQUESTION))
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
	pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// ��������

	WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// �ȴ����ڽ������һ֡����
	if(pMainDlg->m_bRecvPacketTail == false)						// ����־λ ����3��û�յ���β
	{
		TRACE("Receive overtime!\n");
		AfxMessageBox("�豸��ʼ��ʧ�ܣ�");
		return FALSE;
	}
	int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
	RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));

	if(FALSE == ComProto.isVaildPacket(0x02, RecvBuffer, RecvBufLen))
	{
		AfxMessageBox("�豸��ʼ��ʧ�ܣ�");
		return FALSE;
	}
	pMainDlg->MessageBox("�豸��ʼ���ɹ���", "��ʾ", MB_ICONINFORMATION);
	return TRUE;
}

void CBASS330Dlg::OnBnClickedButtonClearRecord()
{
	if( !m_bIsOpenSerl )
	{
		MessageBox("���ȴ򿪴���!", "��ʾ", MB_ICONWARNING);
		return;
	}
	if(IDCANCEL == MessageBox("����������Ž���¼��ȷ����", "��ʾ", MB_OKCANCEL | MB_ICONQUESTION))
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
	pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// ��������

	WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// �ȴ����ڽ������һ֡����
	if(pMainDlg->m_bRecvPacketTail == false)						// ����־λ ����3��û�յ���β
	{
		TRACE("Receive overtime!\n");
		AfxMessageBox("����Ž���¼ʧ�ܣ�");
		return FALSE;
	}
	int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
	RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));

	if(FALSE == ComProto.isVaildPacket(0x35, RecvBuffer, RecvBufLen))
	{
		AfxMessageBox("����Ž���¼ʧ��ʧ�ܣ�");
		return FALSE;
	}
	pMainDlg->MessageBox("����Ž���¼�ɹ���", "��ʾ", MB_ICONINFORMATION);
	return TRUE;
}


void CBASS330Dlg::OnBnClickedButtonClearlist()
{
	if( !m_bIsOpenSerl )
	{
		MessageBox("���ȴ򿪴���!", "��ʾ", MB_ICONWARNING);
		return;
	}
	if(IDCANCEL == MessageBox("������ڰ�������ȷ����", "��ʾ", MB_OKCANCEL | MB_ICONQUESTION))
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
	pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// ��������

	WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// �ȴ����ڽ������һ֡����
	if(pMainDlg->m_bRecvPacketTail == false)						// ����־λ ����3��û�յ���β
	{
		TRACE("Receive overtime!\n");
		AfxMessageBox("����Ž���¼ʧ�ܣ�");
		return FALSE;
	}
	int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
	RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));

	if(FALSE == ComProto.isVaildPacket(0x38, RecvBuffer, RecvBufLen))
	{
		AfxMessageBox("����Ž���¼ʧ��ʧ�ܣ�");
		return FALSE;
	}
	pMainDlg->MessageBox("����Ž���¼�ɹ���", "��ʾ", MB_ICONINFORMATION);
	return TRUE;
}

void CBASS330Dlg::OnBnClickedButtonClearList2M()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox("TODO: 2M�汾������δʵ��", "��ʾ", MB_ICONINFORMATION);
}
