// ParamConfig5.cpp : 实现文件
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig5.h"
#include "BASS-330Dlg.h"

// CParamConfig5 对话框

IMPLEMENT_DYNAMIC(CParamConfig5, CDialog)

CParamConfig5::CParamConfig5(CWnd* pParent /*=NULL*/)
	: CDialog(CParamConfig5::IDD, pParent)
{

}

CParamConfig5::~CParamConfig5()
{
}

void CParamConfig5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_UPDATE, m5_updateVersion);
	DDX_Control(pDX, IDC_LIST_GPRS, m5_GPRSList);
}


BEGIN_MESSAGE_MAP(CParamConfig5, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_1, &CParamConfig5::OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_IP, &CParamConfig5::OnBnClickedButtonGetLocalIp)
END_MESSAGE_MAP()


// CParamConfig5 消息处理程序

BOOL CParamConfig5::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 初始化子窗口全局指针5
	pSubDlg5 = this;

	// 初始化升级版本组合框
	for(int i = 0; i <= 20; i++)
	{
		CString version("BASS-330 TY V5.");
		if( i < 10 )
		{
			version += "0";
		}
		version += ToString( i );
		m5_updateVersion.AddString( version );
	}

	// 初始化GPRS列表控件   
    // 获取编程语言列表视图控件的位置和大小  
	CRect rect;
    m5_GPRSList.GetClientRect(&rect);   
    // 为列表视图控件添加全行选中和栅格风格   
    m5_GPRSList.SetExtendedStyle(m5_GPRSList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
    // 为列表视图控件添加10列   
    m5_GPRSList.InsertColumn(0, _T("编号"), LVCFMT_CENTER, rect.Width()/15, 0);   
    m5_GPRSList.InsertColumn(1, _T("基站名称"), LVCFMT_CENTER, rect.Width()*2/15, 1);   
    m5_GPRSList.InsertColumn(2, _T("设备电话号码"), LVCFMT_CENTER, rect.Width()*2/15, 2);   
	m5_GPRSList.InsertColumn(3, _T("设备IP"), LVCFMT_CENTER, rect.Width()/15, 3);
	m5_GPRSList.InsertColumn(4, _T("端口"), LVCFMT_CENTER, rect.Width()/15, 4);
	m5_GPRSList.InsertColumn(5, _T("版本号"), LVCFMT_CENTER, rect.Width()/15, 5);
	m5_GPRSList.InsertColumn(6, _T("连接状态"), LVCFMT_CENTER, rect.Width()*2/15, 6);
	m5_GPRSList.InsertColumn(7, _T("协议发送"), LVCFMT_CENTER, rect.Width()*2/15, 7);
	m5_GPRSList.InsertColumn(8, _T("告警"), LVCFMT_CENTER, rect.Width()/15, 8);
	m5_GPRSList.InsertColumn(9, _T("设备时间"), LVCFMT_CENTER, rect.Width()*2/15, 9);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CParamConfig5::OnBnClickedButtonBrowse()
{
	// 设置过滤器   
    TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");   
    // 构造打开文件对话框   
    CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);   
    CString strFilePath;   
    // 显示打开文件对话框   
    if (IDOK == fileDlg.DoModal())   
    {   
        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
        strFilePath = fileDlg.GetPathName();   
        SetDlgItemText(IDC_EDIT_UPDATE_FileName, strFilePath);   
    }   
}

void CParamConfig5::OnBnClickedButtonGetLocalIp()
{
	WSADATA		wsaData;						// 初始化Winsock服务
    WSAStartup( MAKEWORD(2, 2), &wsaData );		// Socket库为Version2.2

    HOSTENT	FAR *pHost;

    char hostName[64] = {0};
    char *pTemp;

    if(0 != gethostname(hostName, 64))			// 获取主机名
	{
		TRACE("Get hostname faild!\n");
		return;
	}
    pHost = gethostbyname(hostName);			// 通过主机名获取本地IP
												// 类型转换
    pTemp = inet_ntoa( *((in_addr*)pHost->h_addr) ); 
	CString IPAddress( pTemp );

	((CEdit*)(GetDlgItem(IDC_EDIT_IP_1)))->SetWindowText( IPAddress );

	WSACleanup();								// 释放Socket库占用的资源
}
