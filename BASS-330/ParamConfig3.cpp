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

	/***************** 初始化组合框12 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO12_No ) )->SetCheck( TRUE );	// 选择不配置

	/***************** 初始化组合框13 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO13_No ) )->SetCheck( TRUE );	// 选择不配置
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

	/***************** 初始化组合框14 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO14_No ) )->SetCheck( TRUE );	// 选择不配置

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

	/***************** 初始化组合框15 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO15_No ) )->SetCheck( TRUE );	// 选择不配置
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

	/***************** 初始化组合框16 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO16_No ) )->SetCheck( TRUE );	// 选择不配置

	/***************** 初始化组合框17 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO17_No ) )->SetCheck( TRUE );	// 选择不配置

	/***************** 初始化组合框18 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO18_No ) )->SetCheck( TRUE );	// 选择不配置

	if(LoadParamConfig() == false) 
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

// 参数配置选择 新增按钮
void CParamConfig3::OnBnClickedButtonAdd()
{
	if( /*IfExistsFile(ComboBox1->Text)*/ FALSE) // TODO: 实现函数IfExistsFile
    {
		MessageBox("指定的配置文件已存在，请直接修改！", "提示", MB_ICONWARNING);
        return;

    }
    if( /*AddFileToBase() == FALSE*/ TRUE)		 // TODO: 实现函数AddFileToBase
    {
		MessageBox("参数配置文件新增失败！", "提示", MB_ICONWARNING);
        return ;
    }
    /*InitialParamCfgCombox();*/				 // TODO: 实现函数InitialParamCfgCombox
	MessageBox("参数配置文件新增成功！", "提示", MB_ICONWARNING);
}
// 参数配置选择 导出按钮
void CParamConfig3::OnBnClickedButtonExport()
{
	MessageBox("TODO: 实现导出按钮功能", "提示", MB_ICONWARNING);
	 /*InitialParamCfgCombox();*/				 // TODO: 实现函数InitialParamCfgCombox
	 /*AnsiString strSql = *** */				 // TODO: 实现Sql语句
												 // TODO: 根据Sql语句进行数据库操作
												 // TODO: 配置参数
}
// 参数配置选择 修改按钮
void CParamConfig3::OnBnClickedButtonModify()
{
	if( /*!(IfExistsFile(ComboBox1->Text))*/ TRUE)
    {
		MessageBox("指定的配置文件不存在，请新增！", "提示", MB_ICONWARNING);
        return;
    }
    /*InitialParamCfgCombox();*/
	if( IDCANCEL == MessageBox("确定修改参数吗？", "修改确认", MB_OKCANCEL | MB_ICONQUESTION) )
        return;
    if( /*DelParamFileFromBase(ComboBox1->Text) == false*/ FALSE)
    {
		MessageBox("修改失败！", "提示", MB_ICONWARNING);
        return ;
    }
    if( /*AddFileToBase() == false*/ TRUE)
    {
		MessageBox("修改失败！", "提示", MB_ICONWARNING);
        return ;
    }
	MessageBox("修改成功！", "提示", MB_ICONWARNING);
}
// 参数配置选择 删除按钮
void CParamConfig3::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if(IDCANCEL == MessageBox("确定删除所选的参数配置文件？", "删除确认", MB_OKCANCEL | MB_ICONQUESTION))
        return;
    if( /*DelParamFileFromBase(ComboBox1->Text) == false*/ TRUE)
    {
        MessageBox("删除失败！", "提示", MB_ICONWARNING);
        return ;
    }
    MessageBox("删除成功！", "提示", MB_ICONWARNING);
    /*InitialParamCfgCombox();*/
}

// 从数据库加载配置参数
bool CParamConfig3::LoadParamConfig()
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
	strsql += "QDDZH, QDDDYSH, QDKYXQ, QDCHKSHCH ";
	strsql += "FROM paramconfig WHERE PZMC = 'BASS330CPU测试';";

	if(uMySQL.Select(strsql, data) == false)
		return false;
	
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

	uMySQL.Close();
	return true;
}