// ParamConfig2.cpp : 实现文件
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig2.h"
#include "BASS-330Dlg.h"

// CParamConfig2 对话框

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


// CParamConfig2 消息处理程序

BOOL CParamConfig2::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	/************* 初始化子窗口全局指针2 **************/
	pSubDlg2 = this;

	/***************** 初始化组合框9 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO9_No ) )->SetCheck( TRUE );	// 选择不配置

	/***************** 初始化组合框10 *****************/
	( ( CButton *)GetDlgItem(IDC_RADIO10_No ) )->SetCheck( TRUE );	// 选择不配置
	// 联动类型1
	m10_linkType1.AddString(_T("00-闭合"));
	m10_linkType1.AddString(_T("01-断开"));
	m10_linkType1.AddString(_T("02-脉冲"));
	// 联动类型2
	m10_linkType2.AddString(_T("00-闭合"));
	m10_linkType2.AddString(_T("01-断开"));
	m10_linkType2.AddString(_T("02-脉冲"));
	// 联动类型3
	m10_linkType3.AddString(_T("00-闭合"));
	m10_linkType3.AddString(_T("01-断开"));
	m10_linkType3.AddString(_T("02-脉冲"));
	// 联动类型4
	m10_linkType4.AddString(_T("00-闭合"));
	m10_linkType4.AddString(_T("01-断开"));
	m10_linkType4.AddString(_T("02-脉冲"));
	// 联动类型5
	m10_linkType5.AddString(_T("00-闭合"));
	m10_linkType5.AddString(_T("01-断开"));
	m10_linkType5.AddString(_T("02-脉冲"));
	// 联动类型6
	m10_linkType6.AddString(_T("00-闭合"));
	m10_linkType6.AddString(_T("01-断开"));
	m10_linkType6.AddString(_T("02-脉冲"));

	/***************** 初始化组合框11 *****************/
	( ( CButton *)GetDlgItem(IDC_RADIO11_No ) )->SetCheck( TRUE );	// 选择不配置
	//继电器1 联动光耦
	m11_optocoupler1.AddString(_T("00+00+00+00+00+00+00+00"));
	m11_optocoupler1.AddString(_T("01+02+03+04+00+00+00+00"));
	//继电器2 联动光耦
	m11_optocoupler2.AddString(_T("00+00+00+00+00+00+00+00"));
	m11_optocoupler2.AddString(_T("01+02+03+04+00+00+00+00"));
	//继电器3 联动光耦
	m11_optocoupler3.AddString(_T("00+00+00+00+00+00+00+00"));
	m11_optocoupler3.AddString(_T("01+02+03+04+00+00+00+00"));
	//继电器4 联动光耦
	m11_optocoupler4.AddString(_T("00+00+00+00+00+00+00+00"));
	m11_optocoupler4.AddString(_T("01+02+03+04+00+00+00+00"));
	//继电器5 联动光耦
	m11_optocoupler5.AddString(_T("00+00+00+00+00+00+00+00"));
	m11_optocoupler5.AddString(_T("01+02+03+04+00+00+00+00"));
	//继电器6 联动光耦
	m11_optocoupler6.AddString(_T("00+00+00+00+00+00+00+00"));
	m11_optocoupler6.AddString(_T("01+02+03+04+00+00+00+00"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 选择配置防盗参数
void CParamConfig2::OnBnClickedRadio9Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_9 ) ) )->SetCheck( TRUE );
}
// 不配置防盗参数
void CParamConfig2::OnBnClickedRadio9No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_9 ) ) )->SetCheck( FALSE );
}
// 选择配置联动类型
void CParamConfig2::OnBnClickedRadio10Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_10 ) ) )->SetCheck( TRUE );
}
// 不配置联动类型
void CParamConfig2::OnBnClickedRadio10No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_10 ) ) )->SetCheck( FALSE );
}
// 选择配置告警联动
void CParamConfig2::OnBnClickedRadio11Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_11 ) ) )->SetCheck( TRUE );
}
// 不配置告警联动
void CParamConfig2::OnBnClickedRadio11No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_11 ) ) )->SetCheck( FALSE );
}
