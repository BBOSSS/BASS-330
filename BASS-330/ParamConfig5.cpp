// ParamConfig5.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig5.h"
#include "BASS-330Dlg.h"

// CParamConfig5 �Ի���

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


// CParamConfig5 ��Ϣ�������

BOOL CParamConfig5::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// ��ʼ���Ӵ���ȫ��ָ��5
	pSubDlg5 = this;

	// ��ʼ�������汾��Ͽ�
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

	// ��ʼ��GPRS�б�ؼ�   
    // ��ȡ��������б���ͼ�ؼ���λ�úʹ�С  
	CRect rect;
    m5_GPRSList.GetClientRect(&rect);   
    // Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
    m5_GPRSList.SetExtendedStyle(m5_GPRSList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
    // Ϊ�б���ͼ�ؼ����10��   
    m5_GPRSList.InsertColumn(0, _T("���"), LVCFMT_CENTER, rect.Width()/15, 0);   
    m5_GPRSList.InsertColumn(1, _T("��վ����"), LVCFMT_CENTER, rect.Width()*2/15, 1);   
    m5_GPRSList.InsertColumn(2, _T("�豸�绰����"), LVCFMT_CENTER, rect.Width()*2/15, 2);   
	m5_GPRSList.InsertColumn(3, _T("�豸IP"), LVCFMT_CENTER, rect.Width()/15, 3);
	m5_GPRSList.InsertColumn(4, _T("�˿�"), LVCFMT_CENTER, rect.Width()/15, 4);
	m5_GPRSList.InsertColumn(5, _T("�汾��"), LVCFMT_CENTER, rect.Width()/15, 5);
	m5_GPRSList.InsertColumn(6, _T("����״̬"), LVCFMT_CENTER, rect.Width()*2/15, 6);
	m5_GPRSList.InsertColumn(7, _T("Э�鷢��"), LVCFMT_CENTER, rect.Width()*2/15, 7);
	m5_GPRSList.InsertColumn(8, _T("�澯"), LVCFMT_CENTER, rect.Width()/15, 8);
	m5_GPRSList.InsertColumn(9, _T("�豸ʱ��"), LVCFMT_CENTER, rect.Width()*2/15, 9);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CParamConfig5::OnBnClickedButtonBrowse()
{
	// ���ù�����   
    TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");   
    // ������ļ��Ի���   
    CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);   
    CString strFilePath;   
    // ��ʾ���ļ��Ի���   
    if (IDOK == fileDlg.DoModal())   
    {   
        // ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
        strFilePath = fileDlg.GetPathName();   
        SetDlgItemText(IDC_EDIT_UPDATE_FileName, strFilePath);   
    }   
}

void CParamConfig5::OnBnClickedButtonGetLocalIp()
{
	WSADATA		wsaData;						// ��ʼ��Winsock����
    WSAStartup( MAKEWORD(2, 2), &wsaData );		// Socket��ΪVersion2.2

    HOSTENT	FAR *pHost;

    char hostName[64] = {0};
    char *pTemp;

    if(0 != gethostname(hostName, 64))			// ��ȡ������
	{
		TRACE("Get hostname faild!\n");
		return;
	}
    pHost = gethostbyname(hostName);			// ͨ����������ȡ����IP
												// ����ת��
    pTemp = inet_ntoa( *((in_addr*)pHost->h_addr) ); 
	CString IPAddress( pTemp );

	((CEdit*)(GetDlgItem(IDC_EDIT_IP_1)))->SetWindowText( IPAddress );

	WSACleanup();								// �ͷ�Socket��ռ�õ���Դ
}
