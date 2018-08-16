// ParamConfig2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig2.h"
#include "BASS-330Dlg.h"

// CParamConfig2 �Ի���

IMPLEMENT_DYNAMIC(CParamConfig2, CDialog)

CParamConfig2::CParamConfig2(CWnd* pParent /*=NULL*/)
	: CDialog(CParamConfig2::IDD, pParent)
{

}

CParamConfig2::~CParamConfig2()
{
}

void CParamConfig2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//
	DDX_Control(pDX, IDC_COMBO10_1_1, m10_linkType1);
	DDX_Control(pDX, IDC_COMBO10_2_1, m10_linkType2);
	DDX_Control(pDX, IDC_COMBO10_3_1, m10_linkType3);
	DDX_Control(pDX, IDC_COMBO10_4_1, m10_linkType4);
	DDX_Control(pDX, IDC_COMBO10_5_1, m10_linkType5);
	DDX_Control(pDX, IDC_COMBO10_6_1, m10_linkType6);
	//
	DDX_Control(pDX, IDC_COMBO11_1, m11_optocoupler1);
	DDX_Control(pDX, IDC_COMBO11_2, m11_optocoupler2);
	DDX_Control(pDX, IDC_COMBO11_3, m11_optocoupler3);
	DDX_Control(pDX, IDC_COMBO11_4, m11_optocoupler4);
	DDX_Control(pDX, IDC_COMBO11_5, m11_optocoupler5);
	DDX_Control(pDX, IDC_COMBO11_6, m11_optocoupler6);
}


BEGIN_MESSAGE_MAP(CParamConfig2, CDialog)
	ON_BN_CLICKED(IDC_RADIO9_Yes, &CParamConfig2::OnBnClickedRadio9Yes)
	ON_BN_CLICKED(IDC_RADIO9_No, &CParamConfig2::OnBnClickedRadio9No)
	ON_BN_CLICKED(IDC_RADIO10_Yes, &CParamConfig2::OnBnClickedRadio10Yes)
	ON_BN_CLICKED(IDC_RADIO10_No, &CParamConfig2::OnBnClickedRadio10No)
	ON_BN_CLICKED(IDC_RADIO11_Yes, &CParamConfig2::OnBnClickedRadio11Yes)
	ON_BN_CLICKED(IDC_RADIO11_No, &CParamConfig2::OnBnClickedRadio11No)
END_MESSAGE_MAP()


// CParamConfig2 ��Ϣ�������

BOOL CParamConfig2::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	/************* ��ʼ���Ӵ���ȫ��ָ��2 **************/
	pSubDlg2 = this;

	/***************** ��ʼ����Ͽ�9 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO9_No ) )->SetCheck( TRUE );	// ѡ������

	/***************** ��ʼ����Ͽ�10 *****************/
	( ( CButton *)GetDlgItem(IDC_RADIO10_No ) )->SetCheck( TRUE );	// ѡ������
	// ��������1
	m10_linkType1.AddString(_T("00-�պ�"));
	m10_linkType1.AddString(_T("01-�Ͽ�"));
	m10_linkType1.AddString(_T("02-����"));
	// ��������2
	m10_linkType2.AddString(_T("00-�պ�"));
	m10_linkType2.AddString(_T("01-�Ͽ�"));
	m10_linkType2.AddString(_T("02-����"));
	// ��������3
	m10_linkType3.AddString(_T("00-�պ�"));
	m10_linkType3.AddString(_T("01-�Ͽ�"));
	m10_linkType3.AddString(_T("02-����"));
	// ��������4
	m10_linkType4.AddString(_T("00-�պ�"));
	m10_linkType4.AddString(_T("01-�Ͽ�"));
	m10_linkType4.AddString(_T("02-����"));
	// ��������5
	m10_linkType5.AddString(_T("00-�պ�"));
	m10_linkType5.AddString(_T("01-�Ͽ�"));
	m10_linkType5.AddString(_T("02-����"));
	// ��������6
	m10_linkType6.AddString(_T("00-�պ�"));
	m10_linkType6.AddString(_T("01-�Ͽ�"));
	m10_linkType6.AddString(_T("02-����"));

	/***************** ��ʼ����Ͽ�11 *****************/
	( ( CButton *)GetDlgItem(IDC_RADIO11_No ) )->SetCheck( TRUE );	// ѡ������
	//�̵���1 ��������
	m11_optocoupler1.AddString(_T("00+00+00+00+00+00+00+00"));
	m11_optocoupler1.AddString(_T("01+02+03+04+00+00+00+00"));
	//�̵���2 ��������
	m11_optocoupler2.AddString(_T("00+00+00+00+00+00+00+00"));
	m11_optocoupler2.AddString(_T("01+02+03+04+00+00+00+00"));
	//�̵���3 ��������
	m11_optocoupler3.AddString(_T("00+00+00+00+00+00+00+00"));
	m11_optocoupler3.AddString(_T("01+02+03+04+00+00+00+00"));
	//�̵���4 ��������
	m11_optocoupler4.AddString(_T("00+00+00+00+00+00+00+00"));
	m11_optocoupler4.AddString(_T("01+02+03+04+00+00+00+00"));
	//�̵���5 ��������
	m11_optocoupler5.AddString(_T("00+00+00+00+00+00+00+00"));
	m11_optocoupler5.AddString(_T("01+02+03+04+00+00+00+00"));
	//�̵���6 ��������
	m11_optocoupler6.AddString(_T("00+00+00+00+00+00+00+00"));
	m11_optocoupler6.AddString(_T("01+02+03+04+00+00+00+00"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// ѡ�����÷�������
void CParamConfig2::OnBnClickedRadio9Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_9 ) ) )->SetCheck( TRUE );
}
// �����÷�������
void CParamConfig2::OnBnClickedRadio9No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_9 ) ) )->SetCheck( FALSE );
}
// ѡ��������������
void CParamConfig2::OnBnClickedRadio10Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_10 ) ) )->SetCheck( TRUE );
}
// ��������������
void CParamConfig2::OnBnClickedRadio10No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_10 ) ) )->SetCheck( FALSE );
}
// ѡ�����ø澯����
void CParamConfig2::OnBnClickedRadio11Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_11 ) ) )->SetCheck( TRUE );
}
// �����ø澯����
void CParamConfig2::OnBnClickedRadio11No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_11 ) ) )->SetCheck( FALSE );
}
