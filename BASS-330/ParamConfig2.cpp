// ParamConfig2.cpp : 实现文件
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig2.h"
#include "BASS-330Dlg.h"
#include "MySQLInterface.h"
#include <vector>
#include <string>

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

	if(LoadParamConfig() == false) 
	{
		AfxMessageBox("加载参数配置失败！");
	}

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

// 从数据库加载配置参数
bool CParamConfig2::LoadParamConfig()
{
	using namespace std;

	MySQLInterface uMySQL;
	uMySQL.SetMySQLConInfo(SERVER, USER, PASSWORD, DATABASE, PORT);

	if(uMySQL.Open() == false)
	{
		TRACE("MySQL Connect Faild!\r\n");
		return false;
	}
	vector<vector<string>> data;
	string strsql = "SELECT XHSHJ, TDH1, YYXSJ1, YYXJS1, GJYS1, TDH2, YYXSJ2, YYXJS2, GJYS2, TDH3, YYXSJ3, YYXJS3, GJYS3, TDH4, YYXSJ4, YYXJS4, GJYS4, ";
	strsql += "TDH5, YYXSJ5, YYXJS5, GJYS5, TDH6, YYXSJ6, YYXJS6, GJYS6, TDH7, YYXSJ7, YYXJS7, GJYS7, TDH8, YYXSJ8, YYXJS8, GJYS8, ";
	strsql += "YLDLX, YMK, ELDLX, EMK, SanLDLX, SanMK, SiLDLX, SiMK, WLDLX, WMK, LLDLX, LMK, ";
	strsql += "YLDGO, ELDGO, SanLDGO, SiLDGO, WLDGO, LLDGO ";
	strsql += "FROM paramconfig WHERE PZMC = 'BASS330CPU测试';";

	if(uMySQL.Select(strsql, data) == false)
		return false;
	
	CString TempStr;
	// 防盗设置
	TempStr = data[0][0].c_str();
	SetDlgItemText(IDC_EDIT9_1, TempStr);  

	TempStr = data[0][1].c_str();
	SetDlgItemText(IDC_EDIT9_1_1, TempStr);
	TempStr = data[0][2].c_str();
	SetDlgItemText(IDC_EDIT9_1_2, TempStr);
	TempStr = data[0][3].c_str();
	SetDlgItemText(IDC_EDIT9_1_3, TempStr);
	TempStr = data[0][4].c_str();
	SetDlgItemText(IDC_EDIT9_1_4, TempStr);

	TempStr = data[0][5].c_str();
	SetDlgItemText(IDC_EDIT9_2_1, TempStr);
	TempStr = data[0][6].c_str();
	SetDlgItemText(IDC_EDIT9_2_2, TempStr);
	TempStr = data[0][7].c_str();
	SetDlgItemText(IDC_EDIT9_2_3, TempStr);
	TempStr = data[0][8].c_str();
	SetDlgItemText(IDC_EDIT9_2_4, TempStr);

	TempStr = data[0][9].c_str();
	SetDlgItemText(IDC_EDIT9_3_1, TempStr);
	TempStr = data[0][10].c_str();
	SetDlgItemText(IDC_EDIT9_3_2, TempStr);
	TempStr = data[0][11].c_str();
	SetDlgItemText(IDC_EDIT9_3_3, TempStr);
	TempStr = data[0][12].c_str();
	SetDlgItemText(IDC_EDIT9_3_4, TempStr);

	TempStr = data[0][13].c_str();
	SetDlgItemText(IDC_EDIT9_4_1, TempStr);
	TempStr = data[0][14].c_str();
	SetDlgItemText(IDC_EDIT9_4_2, TempStr);
	TempStr = data[0][15].c_str();
	SetDlgItemText(IDC_EDIT9_4_3, TempStr);
	TempStr = data[0][16].c_str();
	SetDlgItemText(IDC_EDIT9_4_4, TempStr);

	TempStr = data[0][17].c_str();
	SetDlgItemText(IDC_EDIT9_5_1, TempStr);
	TempStr = data[0][18].c_str();
	SetDlgItemText(IDC_EDIT9_5_2, TempStr);
	TempStr = data[0][19].c_str();
	SetDlgItemText(IDC_EDIT9_5_3, TempStr);
	TempStr = data[0][20].c_str();
	SetDlgItemText(IDC_EDIT9_5_4, TempStr);

	TempStr = data[0][21].c_str();
	SetDlgItemText(IDC_EDIT9_6_1, TempStr);
	TempStr = data[0][22].c_str();
	SetDlgItemText(IDC_EDIT9_6_2, TempStr);
	TempStr = data[0][23].c_str();
	SetDlgItemText(IDC_EDIT9_6_3, TempStr);
	TempStr = data[0][24].c_str();
	SetDlgItemText(IDC_EDIT9_6_4, TempStr);

	TempStr = data[0][25].c_str();
	SetDlgItemText(IDC_EDIT9_7_1, TempStr);
	TempStr = data[0][26].c_str();
	SetDlgItemText(IDC_EDIT9_7_2, TempStr);
	TempStr = data[0][27].c_str();
	SetDlgItemText(IDC_EDIT9_7_3, TempStr);
	TempStr = data[0][28].c_str();
	SetDlgItemText(IDC_EDIT9_7_4, TempStr);

	TempStr = data[0][29].c_str();
	SetDlgItemText(IDC_EDIT9_8_1, TempStr);
	TempStr = data[0][30].c_str();
	SetDlgItemText(IDC_EDIT9_8_2, TempStr);
	TempStr = data[0][31].c_str();
	SetDlgItemText(IDC_EDIT9_8_3, TempStr);
	TempStr = data[0][32].c_str();
	SetDlgItemText(IDC_EDIT9_8_4, TempStr);

	// 联动类型
	TempStr = data[0][33].c_str();
	SetDlgItemText(IDC_COMBO10_1_1, TempStr);
	TempStr = data[0][34].c_str();
	SetDlgItemText(IDC_EDIT10_1_1, TempStr);

	TempStr = data[0][35].c_str();
	SetDlgItemText(IDC_COMBO10_2_1, TempStr);
	TempStr = data[0][36].c_str();
	SetDlgItemText(IDC_EDIT10_2_1, TempStr);

	TempStr = data[0][37].c_str();
	SetDlgItemText(IDC_COMBO10_3_1, TempStr);
	TempStr = data[0][38].c_str();
	SetDlgItemText(IDC_EDIT10_3_1, TempStr);

	TempStr = data[0][39].c_str();
	SetDlgItemText(IDC_COMBO10_4_1, TempStr);
	TempStr = data[0][40].c_str();
	SetDlgItemText(IDC_EDIT10_4_1, TempStr);

	TempStr = data[0][41].c_str();
	SetDlgItemText(IDC_COMBO10_5_1, TempStr);
	TempStr = data[0][42].c_str();
	SetDlgItemText(IDC_EDIT10_5_1, TempStr);

	TempStr = data[0][43].c_str();
	SetDlgItemText(IDC_COMBO10_6_1, TempStr);
	TempStr = data[0][44].c_str();
	SetDlgItemText(IDC_EDIT10_6_1, TempStr);

	// 告警联动
	TempStr = data[0][45].c_str();
	SetDlgItemText(IDC_COMBO11_1, TempStr);
	TempStr = data[0][46].c_str();
	SetDlgItemText(IDC_COMBO11_2, TempStr);
	TempStr = data[0][47].c_str();
	SetDlgItemText(IDC_COMBO11_3, TempStr);
	TempStr = data[0][48].c_str();
	SetDlgItemText(IDC_COMBO11_4, TempStr);
	TempStr = data[0][49].c_str();
	SetDlgItemText(IDC_COMBO11_5, TempStr);
	TempStr = data[0][50].c_str();
	SetDlgItemText(IDC_COMBO11_6, TempStr);

	uMySQL.Close();
	return true;
}