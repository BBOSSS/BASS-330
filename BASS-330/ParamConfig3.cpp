// ParamConfig3.cpp : 实现文件
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig3.h"
#include "BASS-330Dlg.h"
#include "MySQLInterface.h"
#include <vector>
#include <string>

// CParamConfig3 对话框

IMPLEMENT_DYNAMIC(CParamConfig3, CDialog)

CParamConfig3::CParamConfig3(CWnd* pParent /*=NULL*/)
	: CDialog(CParamConfig3::IDD, pParent)
{

}

CParamConfig3::~CParamConfig3()
{
}

void CParamConfig3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO12_1, m12_photoCount);
	DDX_Control(pDX, IDC_COMBO13_1, m13_airCondition);
	DDX_Control(pDX, IDC_COMBO13_2, m13_power);
	DDX_Control(pDX, IDC_COMBO13_3, m13_UPS);
	DDX_Control(pDX, IDC_COMBO13_4, m13_oilEngine);
	DDX_Control(pDX, IDC_COMBO13_5, m13_elecMeter);
	DDX_Control(pDX, IDC_COMBO13_6, m13_231Count);
	DDX_Control(pDX, IDC_COMBO13_7, m13_airConditionCount);
	DDX_Control(pDX, IDC_COMBO13_8, m13_saveEnergy);
	DDX_Control(pDX, IDC_COMBO14_1, m13_cutout);
	DDX_Control(pDX, IDC_COMBO14_2, m14_phaseLoss);
	DDX_Control(pDX, IDC_COMBO14_3, m14_overVolt);
	DDX_Control(pDX, IDC_COMBO14_4, m14_underVolt);
	DDX_Control(pDX, IDC_COMBO14_5, m14_threePhaseType);
	DDX_Control(pDX, IDC_COMBO15_1, m15_seriesTransmit);
	DDX_Control(pDX, IDC_COMBO15_2, m15_series1Baudrate);
	DDX_Control(pDX, IDC_COMBO15_3, m15_series1Databit);
	DDX_Control(pDX, IDC_COMBO15_4, m15_series1Stopbit);
	DDX_Control(pDX, IDC_COMBO15_5, m15_series1Checkbit);
	DDX_Control(pDX, IDC_COMBO15_6, m15_series2Baudrate);
	DDX_Control(pDX, IDC_COMBO15_7, m15_series2Databit);
	DDX_Control(pDX, IDC_COMBO15_8, m15_series2Stopbit);
	DDX_Control(pDX, IDC_COMBO15_9, m15_series2Checkbit);
	DDX_Control(pDX, IDC_COMBO3, m_ComboBox_Param);
}


BEGIN_MESSAGE_MAP(CParamConfig3, CDialog)
	ON_STN_CLICKED(IDC_STATIC12_3, &CParamConfig3::OnStnClickedStatic123)
	ON_BN_CLICKED(IDC_RADIO12_Yes, &CParamConfig3::OnBnClickedRadio12Yes)
	ON_BN_CLICKED(IDC_RADIO12_No, &CParamConfig3::OnBnClickedRadio12No)
	ON_BN_CLICKED(IDC_RADIO13_Yes, &CParamConfig3::OnBnClickedRadio13Yes)
	ON_BN_CLICKED(IDC_RADIO13_No, &CParamConfig3::OnBnClickedRadio13No)
	ON_BN_CLICKED(IDC_RADIO14_Yes, &CParamConfig3::OnBnClickedRadio14Yes)
	ON_BN_CLICKED(IDC_RADIO14_No, &CParamConfig3::OnBnClickedRadio14No)
	ON_BN_CLICKED(IDC_RADIO15_Yes, &CParamConfig3::OnBnClickedRadio15Yes)
	ON_BN_CLICKED(IDC_RADIO15_No, &CParamConfig3::OnBnClickedRadio15No)
	ON_BN_CLICKED(IDC_RADIO16_Yes, &CParamConfig3::OnBnClickedRadio16Yes)
	ON_BN_CLICKED(IDC_RADIO16_No, &CParamConfig3::OnBnClickedRadio16No)
	ON_BN_CLICKED(IDC_RADIO17_Yes, &CParamConfig3::OnBnClickedRadio17Yes)
	ON_BN_CLICKED(IDC_RADIO17_No, &CParamConfig3::OnBnClickedRadio17No)
	ON_BN_CLICKED(IDC_RADIO18_Yes, &CParamConfig3::OnBnClickedRadio18Yes)
	ON_BN_CLICKED(IDC_RADIO18_No, &CParamConfig3::OnBnClickedRadio18No)
	ON_BN_CLICKED(IDC_BUTTON3_1, &CParamConfig3::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON3_2, &CParamConfig3::OnBnClickedButtonExport)
	ON_BN_CLICKED(IDC_BUTTON3_3, &CParamConfig3::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON3_4, &CParamConfig3::OnBnClickedButtonDelete)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CParamConfig3::OnCbnSelchangeComboParamExport)
END_MESSAGE_MAP()


// CParamConfig3 消息处理程序

void CParamConfig3::OnStnClickedStatic123()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 对话框三 初始化
BOOL CParamConfig3::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	/************* 初始化子窗口全局指针3 **************/
	pSubDlg3 = this;

	// 空调
	m13_airCondition.AddString(_T("00 - 缺"));
	m13_airCondition.AddString(_T("01 - RC3000"));
	m13_airCondition.AddString(_T("02 - Hair"));
	m13_airCondition.AddString(_T("03 - 开关式"));
	m13_airCondition.AddString(_T("04 - STUZ"));
	// 电源
	m13_power.AddString(_T("00 - 缺"));
	m13_power.AddString(_T("01 - ZD"));
	m13_power.AddString(_T("02 - SX6800"));
	m13_power.AddString(_T("03 - PSM10A"));
	m13_power.AddString(_T("04 - DK04II"));
	m13_power.AddString(_T("05 - DLY"));
	m13_power.AddString(_T("06 - COMLI"));
	m13_power.AddString(_T("07 - ZD-CU01"));
	m13_power.AddString(_T("08 - ZXDU58S301"));
	// UPS
	m13_UPS.AddString(_T("00 - 缺"));
	// 油机
	m13_oilEngine.AddString(_T("00 - 缺"));
	m13_oilEngine.AddString(_T("01 - DF1"));
	m13_oilEngine.AddString(_T("02 - DF2"));
	// 电表
	m13_elecMeter.AddString(_T("00 - 缺"));
	// 231数量
	m13_231Count.AddString(_T("00"));
	m13_231Count.AddString(_T("01"));
	//空调数量
	m13_airConditionCount.AddString(_T("00"));
	m13_airConditionCount.AddString(_T("01"));
	m13_airConditionCount.AddString(_T("02"));
	// 节能
	m13_saveEnergy.AddString(_T("00 - 缺"));

	for(int i = 0; i <= 16; i++)
	{
		CString num;
		if( i < 10 )
		{
			num += "0";
		}
		num += ToString( i );
		m13_cutout.AddString( num );	// 断电输出
		m14_phaseLoss.AddString( num );	// 缺相输出
		m14_overVolt.AddString( num );	// 过压输出
		m14_underVolt.AddString( num );	// 欠压输出
	}

	// 三相电类型
	m14_threePhaseType.AddString(_T("00 - 外置"));
	m14_threePhaseType.AddString(_T("01 - 电源"));

	// COM1 - COM3 转发
	m15_seriesTransmit.AddString(_T("00 - 无"));
	// 串口1 波特率
	m15_series1Baudrate.AddString(_T("00 - 1200bps"));
	m15_series1Baudrate.AddString(_T("01 - 2400bps"));
	m15_series1Baudrate.AddString(_T("02 - 4800bps"));
	m15_series1Baudrate.AddString(_T("03 - 9600bps"));
	m15_series1Baudrate.AddString(_T("04 - 14400bps"));
	m15_series1Baudrate.AddString(_T("05 - 19200bps"));
	m15_series1Baudrate.AddString(_T("06 - 38400bps"));
	m15_series1Baudrate.AddString(_T("07 - 56000bps"));
	m15_series1Baudrate.AddString(_T("08 - 57600bps"));
	m15_series1Baudrate.AddString(_T("09 - 115200bps"));
	// 串口1 数据位
	m15_series1Databit.AddString(_T("05"));
	m15_series1Databit.AddString(_T("06"));
	m15_series1Databit.AddString(_T("07"));
	// 串口1 停止位
	m15_series1Stopbit.AddString(_T("01"));
	m15_series1Stopbit.AddString(_T("02"));
	// 串口1 检验
	m15_series1Checkbit.AddString(_T("00 - 无校验"));
	m15_series1Checkbit.AddString(_T("01 - 奇校验"));
	m15_series1Checkbit.AddString(_T("02 - 偶校验"));
	m15_series1Checkbit.AddString(_T("03 - 1校验"));
	m15_series1Checkbit.AddString(_T("04 - 0校验"));
	// 串口2 波特率
	m15_series2Baudrate.AddString(_T("00 - 1200bps"));
	m15_series2Baudrate.AddString(_T("01 - 2400bps"));
	m15_series2Baudrate.AddString(_T("02 - 4800bps"));
	m15_series2Baudrate.AddString(_T("03 - 9600bps"));
	m15_series2Baudrate.AddString(_T("04 - 14400bps"));
	m15_series2Baudrate.AddString(_T("05 - 19200bps"));
	m15_series2Baudrate.AddString(_T("06 - 38400bps"));
	m15_series2Baudrate.AddString(_T("07 - 56000bps"));
	m15_series2Baudrate.AddString(_T("08 - 57600bps"));
	m15_series2Baudrate.AddString(_T("09 - 115200bps"));
	// 串口2 数据位
	m15_series2Databit.AddString(_T("05"));
	m15_series2Databit.AddString(_T("06"));
	m15_series2Databit.AddString(_T("07"));
	// 串口2 停止位
	m15_series2Stopbit.AddString(_T("01"));
	m15_series2Stopbit.AddString(_T("02"));
	// 串口2 检验
	m15_series2Checkbit.AddString(_T("00 - 无校验"));
	m15_series2Checkbit.AddString(_T("01 - 奇校验"));
	m15_series2Checkbit.AddString(_T("02 - 偶校验"));
	m15_series2Checkbit.AddString(_T("03 - 1校验"));
	m15_series2Checkbit.AddString(_T("04 - 0校验"));

	if(LoadParamConfig("BASS330CPU测试") == false) 
	{
		AfxMessageBox("加载参数配置失败！");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 选择配置拍照参数
void CParamConfig3::OnBnClickedRadio12Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_12 ) ) )->SetCheck( TRUE );
}
// 不配置拍照参数
void CParamConfig3::OnBnClickedRadio12No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_12 ) ) )->SetCheck( FALSE );
}
// 选择配置智能监控
void CParamConfig3::OnBnClickedRadio13Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_13 ) ) )->SetCheck( TRUE );
}
// 不配置智能监控
void CParamConfig3::OnBnClickedRadio13No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_13 ) ) )->SetCheck( FALSE );
}
// 选择配置三相电
void CParamConfig3::OnBnClickedRadio14Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_14 ) ) )->SetCheck( TRUE );
}
// 不配置三相电
void CParamConfig3::OnBnClickedRadio14No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_14 ) ) )->SetCheck( FALSE );
}
// 选择配置串口参数
void CParamConfig3::OnBnClickedRadio15Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_15 ) ) )->SetCheck( TRUE );
}
// 不配置串口参数
void CParamConfig3::OnBnClickedRadio15No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_15 ) ) )->SetCheck( FALSE );
}
// 选择配置室外告警通道
void CParamConfig3::OnBnClickedRadio16Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_16 ) ) )->SetCheck( TRUE );
}
// 不配置室外告警通道
void CParamConfig3::OnBnClickedRadio16No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_16 ) ) )->SetCheck( FALSE );
}
// 选择配置振动参数
void CParamConfig3::OnBnClickedRadio17Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_17 ) ) )->SetCheck( TRUE );
}
// 不配置振动参数
void CParamConfig3::OnBnClickedRadio17No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_17 ) ) )->SetCheck( FALSE );
}
// 选择配置插卡取电
void CParamConfig3::OnBnClickedRadio18Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_18 ) ) )->SetCheck( TRUE );
}
// 不配置插卡取电
void CParamConfig3::OnBnClickedRadio18No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_18 ) ) )->SetCheck( FALSE );
}

// 判断是否存在 
bool CParamConfig3::IsExist(std::string target, std::string field, std::string table, MySQLInterface &uMySQL)
{
	using namespace std;
	uMySQL.SetMySQLConInfo(SERVER, USER, PASSWORD, DATABASE, PORT);

	if(uMySQL.Open() == false)
	{
		TRACE("MySQL Connect Faild!\r\n");
		return false;
	}
	vector<vector<string>> data;
	string strsql = "SELECT " + field + " FROM " + table + " WHERE " + field + " = '" + target + "'";
	if(uMySQL.Select(strsql, data) == false)
		return false;
	if(data.empty())
		return false;
	return true;
}

// 参数配置选择 新增按钮
void CParamConfig3::OnBnClickedButtonAdd()
{
	MySQLInterface uMySQL;
	CString TempStr;
	m_ComboBox_Param.GetWindowText(TempStr);
	std::string str(TempStr.GetBuffer());
	if(IsExist(str, "PZMC", "paramconfig", uMySQL))
    {
		MessageBox("指定的配置文件已存在，请直接修改！", "提示", MB_ICONWARNING);
		uMySQL.Close();
        return;
    }
	uMySQL.Close();

    if( SaveParamConfig() == false )	
    {
		AfxMessageBox("添加失败！");
        return ;
    }
	m_ComboBox_Param.AddString(TempStr);
	pSubDlg7->m_ComboBox_Param.AddString(TempStr);
	pSubDlg7->m_ComboBox_Param.SetWindowText(TempStr);

	MessageBox("添加成功！", "提示", MB_ICONINFORMATION);
}
// 参数配置选择 导出按钮
void CParamConfig3::OnBnClickedButtonExport()
{
	MySQLInterface uMySQL;
	CString TempStr;
	m_ComboBox_Param.GetWindowText(TempStr);
	std::string str(TempStr.GetBuffer());
	if(!IsExist(str, "PZMC", "paramconfig", uMySQL))
    {
		MessageBox("指定的配置文件不存在，请重新选择！", "提示", MB_ICONWARNING);
		uMySQL.Close();
        return;
    }
	uMySQL.Close();
	if(LoadParamConfig(str) == false) 
	{
		AfxMessageBox("导出失败！");
		return;
	}
	if(pSubDlg1->LoadParamConfig(str) == false) 
	{
		AfxMessageBox("导出失败！");
		return;
	}
	if(pSubDlg2->LoadParamConfig(str) == false)
	{
		AfxMessageBox("导出失败！");
		return;
	}
	if(pSubDlg7->LoadParamConfig(str) == false) 
	{
		AfxMessageBox("导出失败！");
		return;
	}
	pSubDlg7->m_ComboBox_Param.SetWindowText(TempStr);
	MessageBox("导出成功！", "提示", MB_ICONINFORMATION);
}
// 参数配置选择 修改按钮
void CParamConfig3::OnBnClickedButtonModify()
{
	MySQLInterface uMySQL;
	CString TempStr;
	m_ComboBox_Param.GetWindowText(TempStr);
	std::string str(TempStr.GetBuffer());
	if(!IsExist(str, "PZMC", "paramconfig", uMySQL))
    {
		MessageBox("指定的配置文件不存在，请新增！", "提示", MB_ICONWARNING);
		uMySQL.Close();
        return;
    }
	if( IDCANCEL == MessageBox("确定修改参数吗？", "修改确认", MB_OKCANCEL | MB_ICONQUESTION) )
	{
		uMySQL.Close();
        return;
	}
    std::string strsql = "DELETE FROM paramconfig WHERE PZMC = '" + str + "'";
	if(uMySQL.Query(strsql) == false)
	{
		AfxMessageBox("修改失败！");
		uMySQL.Close();
		return;
	}
	uMySQL.Close();
    if( SaveParamConfig() == false )
    {
		MessageBox("修改失败！", "提示", MB_ICONWARNING);
        return ;
    }
	pSubDlg7->m_ComboBox_Param.SetWindowText(TempStr);
	MessageBox("修改成功！", "提示", MB_ICONINFORMATION);
}
// 参数配置选择 删除按钮
void CParamConfig3::OnBnClickedButtonDelete()
{
	MySQLInterface uMySQL;
	CString TempStr;
	m_ComboBox_Param.GetWindowText(TempStr);
	std::string str(TempStr.GetBuffer());
	if(!IsExist(str, "PZMC", "paramconfig", uMySQL))
    {
		MessageBox("指定的配置文件不存在数据库中！", "提示", MB_ICONWARNING);
		uMySQL.Close();
        return;
    }
	if(IDCANCEL == MessageBox("确定删除所选的参数配置文件？", "删除确认", MB_OKCANCEL | MB_ICONQUESTION))
	{
		uMySQL.Close();
        return;
	}

	std::string strsql = "DELETE FROM paramconfig WHERE PZMC = '" + str + "'";
	if(uMySQL.Query(strsql) == false)
	{
		AfxMessageBox("删除失败！");
		uMySQL.Close();
		return;
	}
    MessageBox("删除成功！", "提示", MB_ICONINFORMATION);
	uMySQL.Close();
    pSubDlg7->InitParamComboBox();
}

// 从数据库加载配置参数
bool CParamConfig3::LoadParamConfig(std::string pzmc)
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
	string strsql = "SELECT KaiShiYS, XiangJianSJ, PaiZhaoSL, GaoJingTD1, GaoJingTD2, ";
	strsql += "KongT1, DianY1, UPS, YouJ, DianB, 231SL, KongTsl, ShangS, ZHNJKJN, ";
	strsql += "DuanX, QueX, GuoY, QianY, SanXLX, SanXYSH, ";
	strsql += "COM13ZHF, CK1BTL, CK1SHJW, CK1TZHW, CK1JY, CK2BTL, CK2SHJW, CK2TZHW, CK2JY, ";
	strsql += "GaoJYS, ShiYGJTD1, ShiYGJTD2, ShiYGJTD3, ShiYGJTD4, ShiYGJTD5, ShiYGJTD6, ShiYGJTD7, ShiYGJTD8, ";
	strsql += "EYXSJ, EYXJS, EGJYS, ";
	strsql += "QDDZH, QDDDYSH, QDKYXQ, QDCHKSHCH, ";
	strsql += "Radio12_Yes, Radio12_No, Radio13_Yes, Radio13_No, Radio14_Yes, Radio14_No, ";
	strsql += "Radio15_Yes, Radio15_No, Radio16_Yes, Radio16_No, Radio17_Yes, Radio17_No, Radio18_Yes, Radio18_No ";
	strsql += "FROM paramconfig WHERE PZMC = '" + pzmc + "'";
	if(uMySQL.Select(strsql, data) == false)
	{
		uMySQL.Close();
		return false;
	}
	
	CString TempStr;
	// 拍照设置
	TempStr = data[0][0].c_str();
	SetDlgItemText(IDC_EDIT12_1, TempStr);  
	TempStr = data[0][1].c_str();
	SetDlgItemText(IDC_EDIT12_2, TempStr);  
	TempStr = data[0][2].c_str();
	SetDlgItemText(IDC_COMBO12_1, TempStr);  
	TempStr = data[0][3].c_str();
	SetDlgItemText(IDC_EDIT12_3, TempStr);  
	TempStr = data[0][4].c_str();
	SetDlgItemText(IDC_EDIT12_4, TempStr);  

	// 智能监控
	TempStr = data[0][5].c_str();
	SetDlgItemText(IDC_COMBO13_1, TempStr); 
	TempStr = data[0][6].c_str();
	SetDlgItemText(IDC_COMBO13_2, TempStr); 
	TempStr = data[0][7].c_str();
	SetDlgItemText(IDC_COMBO13_3, TempStr); 
	TempStr = data[0][8].c_str();
	SetDlgItemText(IDC_COMBO13_4, TempStr); 
	TempStr = data[0][9].c_str();
	SetDlgItemText(IDC_COMBO13_5, TempStr); 
	TempStr = data[0][10].c_str();
	SetDlgItemText(IDC_COMBO13_6, TempStr); 
	TempStr = data[0][11].c_str();
	SetDlgItemText(IDC_COMBO13_7, TempStr); 
	TempStr = data[0][12].c_str();
	SetDlgItemText(IDC_EDIT13_1, TempStr); 
	TempStr = data[0][13].c_str();
	SetDlgItemText(IDC_COMBO13_8, TempStr); 

	// 三相电设置
	TempStr = data[0][14].c_str();
	SetDlgItemText(IDC_COMBO14_1, TempStr); 
	TempStr = data[0][15].c_str();
	SetDlgItemText(IDC_COMBO14_2, TempStr); 
	TempStr = data[0][16].c_str();
	SetDlgItemText(IDC_COMBO14_3, TempStr); 
	TempStr = data[0][17].c_str();
	SetDlgItemText(IDC_COMBO14_4, TempStr); 
	TempStr = data[0][18].c_str();
	SetDlgItemText(IDC_COMBO14_5, TempStr); 
	TempStr = data[0][19].c_str();
	SetDlgItemText(IDC_EDIT14_1, TempStr); 

	// 串口参数
	TempStr = data[0][20].c_str();
	SetDlgItemText(IDC_COMBO15_1, TempStr); 
	TempStr = data[0][21].c_str();
	SetDlgItemText(IDC_COMBO15_2, TempStr); 
	TempStr = data[0][22].c_str();
	SetDlgItemText(IDC_COMBO15_3, TempStr); 
	TempStr = data[0][23].c_str();
	SetDlgItemText(IDC_COMBO15_4, TempStr); 
	TempStr = data[0][24].c_str();
	SetDlgItemText(IDC_COMBO15_5, TempStr); 
	TempStr = data[0][25].c_str();
	SetDlgItemText(IDC_COMBO15_6, TempStr); 
	TempStr = data[0][26].c_str();
	SetDlgItemText(IDC_COMBO15_7, TempStr); 
	TempStr = data[0][27].c_str();
	SetDlgItemText(IDC_COMBO15_8, TempStr); 
	TempStr = data[0][28].c_str();
	SetDlgItemText(IDC_COMBO15_9, TempStr); 

	// 室外告警通道
	TempStr = data[0][29].c_str();
	SetDlgItemText(IDC_EDIT16_1, TempStr); 
	TempStr = data[0][30].c_str();
	SetDlgItemText(IDC_EDIT16_2, TempStr); 
	TempStr = data[0][31].c_str();
	SetDlgItemText(IDC_EDIT16_3, TempStr); 
	TempStr = data[0][32].c_str();
	SetDlgItemText(IDC_EDIT16_4, TempStr); 
	TempStr = data[0][33].c_str();
	SetDlgItemText(IDC_EDIT16_5, TempStr); 
	TempStr = data[0][34].c_str();
	SetDlgItemText(IDC_EDIT16_6, TempStr); 
	TempStr = data[0][35].c_str();
	SetDlgItemText(IDC_EDIT16_7, TempStr); 
	TempStr = data[0][36].c_str();
	SetDlgItemText(IDC_EDIT16_8, TempStr); 
	TempStr = data[0][37].c_str();
	SetDlgItemText(IDC_EDIT16_9, TempStr); 

	// 振动参数
	TempStr = data[0][38].c_str();
	SetDlgItemText(IDC_EDIT17_1, TempStr); 
	TempStr = data[0][39].c_str();
	SetDlgItemText(IDC_EDIT17_2, TempStr); 
	TempStr = data[0][40].c_str();
	SetDlgItemText(IDC_EDIT17_3, TempStr); 

	// 插卡取电
	TempStr = data[0][41].c_str();
	SetDlgItemText(IDC_EDIT18_1, TempStr); 
	TempStr = data[0][42].c_str();
	SetDlgItemText(IDC_EDIT18_2, TempStr); 
	TempStr = data[0][43].c_str();
	SetDlgItemText(IDC_EDIT18_3, TempStr); 
	TempStr = data[0][44].c_str();
	SetDlgItemText(IDC_EDIT18_4, TempStr); 

	// 选择是否配置
	((CButton*)GetDlgItem(IDC_RADIO12_Yes))->SetCheck(stoi(data[0][45]));
	((CButton*)GetDlgItem(IDC_RADIO12_No ))->SetCheck(stoi(data[0][46]));
	((CButton*)GetDlgItem(IDC_RADIO13_Yes))->SetCheck(stoi(data[0][47]));
	((CButton*)GetDlgItem(IDC_RADIO13_No ))->SetCheck(stoi(data[0][48]));
	((CButton*)GetDlgItem(IDC_RADIO14_Yes))->SetCheck(stoi(data[0][49]));
	((CButton*)GetDlgItem(IDC_RADIO14_No ))->SetCheck(stoi(data[0][50]));
	((CButton*)GetDlgItem(IDC_RADIO15_Yes))->SetCheck(stoi(data[0][51]));
	((CButton*)GetDlgItem(IDC_RADIO15_No ))->SetCheck(stoi(data[0][52]));
	((CButton*)GetDlgItem(IDC_RADIO16_Yes))->SetCheck(stoi(data[0][53]));
	((CButton*)GetDlgItem(IDC_RADIO16_No ))->SetCheck(stoi(data[0][54]));
	((CButton*)GetDlgItem(IDC_RADIO17_Yes))->SetCheck(stoi(data[0][55]));
	((CButton*)GetDlgItem(IDC_RADIO17_No ))->SetCheck(stoi(data[0][56]));
	((CButton*)GetDlgItem(IDC_RADIO18_Yes))->SetCheck(stoi(data[0][57]));
	((CButton*)GetDlgItem(IDC_RADIO18_No ))->SetCheck(stoi(data[0][58]));

	uMySQL.Close();
	return true;
}

// 保存配置参数到数据库
bool CParamConfig3::SaveParamConfig()
{
	using namespace std;

	MySQLInterface uMySQL;
	uMySQL.SetMySQLConInfo(SERVER, USER, PASSWORD, DATABASE, PORT);

	if(uMySQL.Open() == false)
	{
		TRACE("MySQL Connect Faild!\r\n");
		return false;
	}
	CString strsql = "INSERT INTO paramconfig";
	// 机器参数
	strsql += "(PZMC, DiZhi, XTMiMa, MJMiMa, CXMiMa, LaBa, PingBao, AnJianYin, KH2M5, ";
	// 空调设置
	strsql += "KongZhiCK, SWTD, YFWTD, EFWTD, KZMS, SXWD, XXWD, LHSJ, ";
	// 超级密码
	strsql += "CJMM, ";
	// 开锁设置
	strsql += "SLX, MCK, MSSL, DKTSL, YDYSK, EDYSK, MJSG, ";
	// 门禁设置
	strsql += "MJLX, PBSJ, PBTS, MDGZFS, SFFS, PBMS, Lk, KH, KaLeiX, ZCM, MiMa, QuHao, ZhanHao, ";
	// 风机设置
	strsql += "QYJN, FJQKWD, FJQD, FJGB, KTSL, JCSJ, KTLX, ZRWD, GRKQ, RWWC, KTJG, FMTD, ";
	strsql += "FDTD, ZRWW, FJJG, FJSWWD, FJSX3, FJDY3, SCTD3, SJSS3, FJLX3, JGSJ, YSSJ, ";
	// 告警参数
	strsql += "GJY, SFSS, DQYS, JDFW, MJYS, GJLX, YouXSJ, GaoJCS, PingBSJ, GJQR, GJSFBC, ";
	// 通信方式
	strsql += "LianLu2M, BoHao, DHCD, DianHuaSheZhi, JKCD, JianKongSheZhi, IPDKHao, IPDiZhi, JKXTJG7, SIMKBD, SIM, SIMWS, ";
	// 防盗设置
	strsql += "XHSHJ, TDH1, YYXSJ1, YYXJS1, GJYS1, TDH2, YYXSJ2, YYXJS2, GJYS2, TDH3, YYXSJ3, YYXJS3, GJYS3, TDH4, YYXSJ4, YYXJS4, GJYS4, ";
	strsql += "TDH5, YYXSJ5, YYXJS5, GJYS5, TDH6, YYXSJ6, YYXJS6, GJYS6, TDH7, YYXSJ7, YYXJS7, GJYS7, TDH8, YYXSJ8, YYXJS8, GJYS8, ";
	// 联动类型
	strsql += "YLDLX, YMK, ELDLX, EMK, SanLDLX, SanMK, SiLDLX, SiMK, WLDLX, WMK, LLDLX, LMK, ";
	// 告警联动
	strsql += "YLDGO, ELDGO, SanLDGO, SiLDGO, WLDGO, LLDGO, ";
	// 拍照设置
	strsql += "KaiShiYS, XiangJianSJ, PaiZhaoSL, GaoJingTD1, GaoJingTD2, ";
	// 智能监控
	strsql += "KongT1, DianY1, UPS, YouJ, DianB, 231SL, KongTsl, ShangS, ZHNJKJN, ";
	// 三相电设置
	strsql += "DuanX, QueX, GuoY, QianY, SanXLX, SanXYSH, ";
	// 串口参数
	strsql += "COM13ZHF, CK1BTL, CK1SHJW, CK1TZHW, CK1JY, CK2BTL, CK2SHJW, CK2TZHW, CK2JY, ";
	// 室外告警
	strsql += "GaoJYS, ShiYGJTD1, ShiYGJTD2, ShiYGJTD3, ShiYGJTD4, ShiYGJTD5, ShiYGJTD6, ShiYGJTD7, ShiYGJTD8, ";
	// 振动设置
	strsql += "EYXSJ, EYXJS, EGJYS, ";
	// 插卡取电
	strsql += "QDDZH, QDDDYSH, QDKYXQ, QDCHKSHCH, ";
	// 配置选项
	strsql += "Radio1_Yes, Radio1_No, Radio2_Yes, Radio2_No, Radio3_Yes, Radio3_No, Radio4_Yes, Radio4_No, ";
	strsql += "Radio5_Yes, Radio5_No, Radio6_Yes, Radio6_No, Radio7_Yes, Radio7_No, Radio8_Yes, Radio8_No, ";
	strsql += "Radio9_Yes, Radio9_No, Radio10_Yes, Radio10_No, Radio11_Yes, Radio11_No, ";
	strsql += "Radio12_Yes, Radio12_No, Radio13_Yes, Radio13_No, Radio14_Yes, Radio14_No, ";
	strsql += "Radio15_Yes, Radio15_No, Radio16_Yes, Radio16_No, Radio17_Yes, Radio17_No, Radio18_Yes, Radio18_No, ";
	strsql += "Check_7_1, Check_7_2, Check_7_3, Check_7_4, Check_7_5, Check_7_6, Check_7_7, ";
	strsql += "Check_7_8, Check_7_9, Check_7_10, Check_7_11, Check_7_12, Check_7_13, Check_7_14, Check_7_15, ";
	strsql += "Check_7_16, Check_7_17, Check_7_18, Check_7_19, Check_7_20, Check_7_21, Check_7_22, Check_7_23, ";
	strsql += "Radio_7_3, Radio_7_4, Radio_7_5, Radio_7_6, Radio_7_7) ";
	strsql += "VALUES( '";
	CString TempStr;
	// 新增配置的名称
	GetDlgItemText(IDC_COMBO3, TempStr); strsql += (TempStr + "', '");
	// 机器参数
	pSubDlg1->GetDlgItemText(IDC_EDIT1_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT1_2, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT1_3, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT1_4, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO1_1, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO1_2, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO1_3, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO1_4, TempStr); strsql += (TempStr + "', '");
	// 空调设置
	pSubDlg1->GetDlgItemText(IDC_COMBO2_1, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO2_2, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO2_3, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO2_4, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO2_5, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT2_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT2_2, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT2_3, TempStr);  strsql += (TempStr + "', '");
	// 超级密码
	pSubDlg1->GetDlgItemText(IDC_EDIT3_1, TempStr);  strsql += (TempStr + "', '");
	// 开锁设置
	pSubDlg1->GetDlgItemText(IDC_COMBO4_1, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT4_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO4_2, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO4_3, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO4_4, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO4_5, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO4_6, TempStr); strsql += (TempStr + "', '");
	// 门禁设置
	pSubDlg1->GetDlgItemText(IDC_COMBO5_1, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT5_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT5_2, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO5_2, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO5_3, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO5_4, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO5_5, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO5_6, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO5_7, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT5_3, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT5_4, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT5_5, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT5_6, TempStr);  strsql += (TempStr + "', '");
	// 风机设置
	pSubDlg1->GetDlgItemText(IDC_COMBO6_1, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT6_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT6_2, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT6_3, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO6_2, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT6_4, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO6_3, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT6_5, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO6_4, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT6_6, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT6_7, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT6_8, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT6_9, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT6_10, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT6_11, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT6_12, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT6_13, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO6_5, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO6_6, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO6_7, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO6_8, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT6_14, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT6_15, TempStr);  strsql += (TempStr + "', '");
	// 告警参数
	pSubDlg1->GetDlgItemText(IDC_COMBO7_1, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO7_2, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT7_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT7_2, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT7_3, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO7_3, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT7_4, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT7_5, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT7_6, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO7_4, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO7_5, TempStr); strsql += (TempStr + "', '");
	// 通信方式
	pSubDlg1->GetDlgItemText(IDC_COMBO8_1, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO8_2, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT8_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT8_2, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT8_3, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT8_4, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT8_5, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT8_6, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT8_7, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_COMBO8_3, TempStr); strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT8_8, TempStr);  strsql += (TempStr + "', '");
	pSubDlg1->GetDlgItemText(IDC_EDIT8_9, TempStr);  strsql += (TempStr + "', '");
	// 防盗设置
	pSubDlg2->GetDlgItemText(IDC_EDIT9_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_1_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_1_2, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_1_3, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_1_4, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_2_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_2_2, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_2_3, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_2_4, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_3_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_3_2, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_3_3, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_3_4, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_4_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_4_2, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_4_3, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_4_4, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_5_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_5_2, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_5_3, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_5_4, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_6_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_6_2, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_6_3, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_6_4, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_7_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_7_2, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_7_3, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_7_4, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_8_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_8_2, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_8_3, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT9_8_4, TempStr);  strsql += (TempStr + "', '");
	// 联动类型
	pSubDlg2->GetDlgItemText(IDC_COMBO10_1_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT10_1_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_COMBO10_2_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT10_2_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_COMBO10_3_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT10_3_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_COMBO10_4_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT10_4_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_COMBO10_5_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT10_5_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_COMBO10_6_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_EDIT10_6_1, TempStr);  strsql += (TempStr + "', '");
	// 告警联动
	pSubDlg2->GetDlgItemText(IDC_COMBO11_1, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_COMBO11_2, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_COMBO11_3, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_COMBO11_4, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_COMBO11_5, TempStr);  strsql += (TempStr + "', '");
	pSubDlg2->GetDlgItemText(IDC_COMBO11_6, TempStr);  strsql += (TempStr + "', '");
	// 拍照设置
	GetDlgItemText(IDC_EDIT12_1, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT12_2, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO12_1, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT12_3, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT12_4, TempStr);  strsql += (TempStr + "', '");
	// 智能监控
	GetDlgItemText(IDC_COMBO13_1, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO13_2, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO13_3, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO13_4, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO13_5, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO13_6, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO13_7, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT13_1, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO13_8, TempStr);  strsql += (TempStr + "', '");
	// 三相电设置
	GetDlgItemText(IDC_COMBO14_1, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO14_2, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO14_3, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO14_4, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO14_5, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT14_1, TempStr);  strsql += (TempStr + "', '");
	// 串口参数	
	GetDlgItemText(IDC_COMBO15_1, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO15_2, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO15_3, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO15_4, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO15_5, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO15_6, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO15_7, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO15_8, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_COMBO15_9, TempStr);  strsql += (TempStr + "', '");
	// 室外告警
	GetDlgItemText(IDC_EDIT16_1, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT16_2, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT16_3, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT16_4, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT16_5, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT16_6, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT16_7, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT16_8, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT16_9, TempStr);  strsql += (TempStr + "', '");
	// 振动设置
	GetDlgItemText(IDC_EDIT17_1, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT17_2, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT17_3, TempStr);  strsql += (TempStr + "', '");
	// 插卡取电
	GetDlgItemText(IDC_EDIT18_1, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT18_2, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT18_3, TempStr);  strsql += (TempStr + "', '");
	GetDlgItemText(IDC_EDIT18_4, TempStr);  strsql += (TempStr + "', '");
	// 配置选项
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO1_Yes)))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO1_No )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO2_Yes)))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO2_No )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO3_Yes)))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO3_No )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO4_Yes)))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO4_No )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO5_Yes)))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO5_No )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO6_Yes)))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO6_No )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO7_Yes)))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO7_No )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO8_Yes)))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg1->GetDlgItem(IDC_RADIO8_No )))->GetCheck()); strsql += (TempStr + "', '");

	TempStr = ToString(((CButton*)(pSubDlg2->GetDlgItem(IDC_RADIO9_Yes)))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg2->GetDlgItem(IDC_RADIO9_No )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg2->GetDlgItem(IDC_RADIO10_Yes)))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg2->GetDlgItem(IDC_RADIO10_No )))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg2->GetDlgItem(IDC_RADIO11_Yes)))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg2->GetDlgItem(IDC_RADIO11_No )))->GetCheck());strsql += (TempStr + "', '");

	TempStr = ToString(((CButton*)(GetDlgItem(IDC_RADIO12_Yes)))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(GetDlgItem(IDC_RADIO12_No )))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(GetDlgItem(IDC_RADIO13_Yes)))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(GetDlgItem(IDC_RADIO13_No )))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(GetDlgItem(IDC_RADIO14_Yes)))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(GetDlgItem(IDC_RADIO14_No )))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(GetDlgItem(IDC_RADIO15_Yes)))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(GetDlgItem(IDC_RADIO15_No )))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(GetDlgItem(IDC_RADIO16_Yes)))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(GetDlgItem(IDC_RADIO16_No )))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(GetDlgItem(IDC_RADIO17_Yes)))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(GetDlgItem(IDC_RADIO17_No )))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(GetDlgItem(IDC_RADIO18_Yes)))->GetCheck());strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(GetDlgItem(IDC_RADIO18_No )))->GetCheck());strsql += (TempStr + "', '");
	
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_1 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_2 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_3 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_4 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_5 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_6 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_7 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_8 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_9 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_10 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_11 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_12 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_13 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_14 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_15 )))->GetCheck()); strsql += (TempStr + "', '");//
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_16 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_17 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_18 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_19 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_24 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_25 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_26 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_27 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_RADIO_7_3 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_RADIO_7_4 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_RADIO_7_5 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_RADIO_7_6 )))->GetCheck()); strsql += (TempStr + "', '");
	TempStr = ToString(((CButton*)(pSubDlg7->GetDlgItem(IDC_RADIO_7_7 )))->GetCheck()); strsql += (TempStr + "');");//

	std::string QueryStr(strsql.GetBuffer());
	if(uMySQL.Query(QueryStr) == false)
	{
		uMySQL.Close();
		return false;
	}
	uMySQL.Close();
	return true;
}
// 同步参数组合框
void CParamConfig3::OnCbnSelchangeComboParamExport()
{
	CString TempStr;
	int nSel = m_ComboBox_Param.GetCurSel();    
    m_ComboBox_Param.GetLBText(nSel, TempStr);
	pSubDlg7->m_ComboBox_Param.SetWindowText(TempStr);
}
