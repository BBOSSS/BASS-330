// ParamConfig1.cpp : 实现文件
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig1.h"
#include "BASS-330Dlg.h"


// CParamConfig1 对话框

IMPLEMENT_DYNAMIC(CParamConfig1, CDialog)

CParamConfig1::CParamConfig1(CWnd* pParent /*=NULL*/)
	: CDialog(CParamConfig1::IDD, pParent)
{

}

CParamConfig1::~CParamConfig1()
{
}

void CParamConfig1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//
	DDX_Control(pDX, IDC_COMBO1_1, m1_trumpet);
	DDX_Control(pDX, IDC_COMBO1_2, m1_screen);
	DDX_Control(pDX, IDC_COMBO1_3, m1_keyboard);
	DDX_Control(pDX, IDC_COMBO1_4, m1_client);
	//
	DDX_Control(pDX, IDC_COMBO2_1, m2_ctrReference);
	DDX_Control(pDX, IDC_COMBO2_2, m2_roomTemp);
	DDX_Control(pDX, IDC_COMBO2_3, m2_windWarm1);
	DDX_Control(pDX, IDC_COMBO2_4, m2_windWarm2);
	DDX_Control(pDX, IDC_COMBO2_5, m2_ctrMode);
	//
	DDX_Control(pDX, IDC_COMBO4_1, m4_lockType);
	DDX_Control(pDX, IDC_COMBO4_2, m4_lockCount);
	DDX_Control(pDX, IDC_COMBO4_3, m4_cardReaderCount);
	DDX_Control(pDX, IDC_COMBO4_4, m4_slotCard1);
	DDX_Control(pDX, IDC_COMBO4_5, m4_slotCard2);
	DDX_Control(pDX, IDC_COMBO4_6, m4_switchReport);
	//
	DDX_Control(pDX, IDC_COMBO5_1, m5_guardType);
	DDX_Control(pDX, IDC_COMBO5_2, m5_listWorkMode);
	DDX_Control(pDX, IDC_COMBO5_3, m5_preventWay);
	DDX_Control(pDX, IDC_COMBO5_4, m5_blockMode);
	DDX_Control(pDX, IDC_COMBO5_5, m5_leave);
	DDX_Control(pDX, IDC_COMBO5_6, m5_cardID);
	DDX_Control(pDX, IDC_COMBO5_7, m5_cardType);
	//
	DDX_Control(pDX, IDC_COMBO6_1, m6_saveEnergy);
	DDX_Control(pDX, IDC_COMBO6_2, m6_airConditionCount);
	DDX_Control(pDX, IDC_COMBO6_3, m6_airConditionType);
	DDX_Control(pDX, IDC_COMBO6_4, m6_startEveryOtherDay);
	DDX_Control(pDX, IDC_COMBO6_5, m6_powerType);
	DDX_Control(pDX, IDC_COMBO6_6, m6_outputChannel);
	DDX_Control(pDX, IDC_COMBO6_7, m6_dataReport);
	DDX_Control(pDX, IDC_COMBO6_8, m6_fanType);
	//
	DDX_Control(pDX, IDC_COMBO7_1, m7_alarmSound);
	DDX_Control(pDX, IDC_COMBO7_2, m7_isReport);
	DDX_Control(pDX, IDC_COMBO7_3, m7_alarmType);
	DDX_Control(pDX, IDC_COMBO7_4, m7_alarmComfirm);
	DDX_Control(pDX, IDC_COMBO7_5, m7_saveReport);
	//
	DDX_Control(pDX, IDC_COMBO8_1, m8_linkChain);
	DDX_Control(pDX, IDC_COMBO8_2, m8_activeDial);
	DDX_Control(pDX, IDC_COMBO8_3, m8_boundSIM);
}


BEGIN_MESSAGE_MAP(CParamConfig1, CDialog)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_RADIO1_Yes, &CParamConfig1::OnBnClickedRadio1Yes)
	ON_BN_CLICKED(IDC_RADIO1_No, &CParamConfig1::OnBnClickedRadio1No)
	ON_BN_CLICKED(IDC_RADIO2_Yes, &CParamConfig1::OnBnClickedRadio2Yes)
	ON_BN_CLICKED(IDC_RADIO2_No, &CParamConfig1::OnBnClickedRadio2No)
	ON_BN_CLICKED(IDC_RADIO3_Yes, &CParamConfig1::OnBnClickedRadio3Yes)
	ON_BN_CLICKED(IDC_RADIO3_No, &CParamConfig1::OnBnClickedRadio3No)
	ON_BN_CLICKED(IDC_RADIO4_Yes, &CParamConfig1::OnBnClickedRadio4Yes)
	ON_BN_CLICKED(IDC_RADIO4_No, &CParamConfig1::OnBnClickedRadio4No)
	ON_BN_CLICKED(IDC_RADIO5_Yes, &CParamConfig1::OnBnClickedRadio5Yes)
	ON_BN_CLICKED(IDC_RADIO5_No, &CParamConfig1::OnBnClickedRadio5No)
	ON_BN_CLICKED(IDC_RADIO6_Yes, &CParamConfig1::OnBnClickedRadio6Yes)
	ON_BN_CLICKED(IDC_RADIO6_No, &CParamConfig1::OnBnClickedRadio6No)
	ON_BN_CLICKED(IDC_RADIO7_Yes, &CParamConfig1::OnBnClickedRadio7Yes)
	ON_BN_CLICKED(IDC_RADIO7_No, &CParamConfig1::OnBnClickedRadio7No)
	ON_BN_CLICKED(IDC_RADIO8_Yes, &CParamConfig1::OnBnClickedRadio8Yes)
	ON_BN_CLICKED(IDC_RADIO8_No, &CParamConfig1::OnBnClickedRadio8No)
END_MESSAGE_MAP()


// CParamConfig1 消息处理程序

BOOL CParamConfig1::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	/************ 初始化子窗口全局指针1 **************/
	pSubDlg1 = this;

	/***************** 初始化滚动条 *******************/
	SCROLLINFO scrollinfo;
    GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);    
    scrollinfo.nPage = 50;    //设置滑块大小
    scrollinfo.nMax = 100;     //设置滚动条的最大位置0--75
    SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);

	/***************** 初始化组合框1 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO1_No ) )->SetCheck( TRUE );	// 选择不配置
	// 喇叭
    m1_trumpet.AddString(_T("00 - 关"));     
    m1_trumpet.AddString(_T("01 - 开"));
	// 屏保
    m1_screen.AddString(_T("00 - 禁止"));  
    m1_screen.AddString(_T("01 - 使用"));
	// 按键声 
    m1_keyboard.AddString(_T("00 - 关"));   
    m1_keyboard.AddString(_T("01 - 开"));
	// 用户名
    m1_client.AddString(_T("00 - 通用"));   
    m1_client.AddString(_T("01 - 深圳"));
	m1_client.AddString(_T("02 - 东莞"));     
    m1_client.AddString(_T("03 - 揭阳"));
	m1_client.AddString(_T("04 - 梅州"));     
    m1_client.AddString(_T("05 - 宁德"));
	m1_client.AddString(_T("06 - 河南"));     
    m1_client.AddString(_T("07 - 河南VCOM"));
	m1_client.AddString(_T("08 - INCOM"));     
    m1_client.AddString(_T("09 - 江西"));

	/***************** 初始化组合框2 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO2_No ) )->SetCheck( TRUE );	// 选择不配置
	// 控制参考
	m2_ctrReference.AddString(_T("00 - 风温"));
	m2_ctrReference.AddString(_T("01 - 室温"));
	m2_ctrReference.AddString(_T("02 - 智能"));
	m2_ctrReference.AddString(_T("03 - 上控"));
	
	for(int i = 0; i <= 32; i++)
	{
		CString num;
		if( i < 10 )
		{
			num += "0";
		}
		num += ToString( i );
		m2_roomTemp.AddString( num );	// 室温通道
		m2_windWarm1.AddString( num );	// #1 风温通道
		m2_windWarm2.AddString( num );	// #2 风温通道
	}
	
	// 控制模式
	m2_ctrMode.AddString(_T("00"));
	m2_ctrMode.AddString(_T("01"));
	m2_ctrMode.AddString(_T("02"));

	/***************** 初始化组合框3 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO3_No ) )->SetCheck( TRUE );	// 选择不配置

	/***************** 初始化组合框4 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO4_No ) )->SetCheck( TRUE );	// 选择不配置
	// 锁类型
	m4_lockType.AddString(_T("00 - 常闭"));
	m4_lockType.AddString(_T("01 - 常开"));
	// 门锁数量
	m4_lockCount.AddString(_T("00"));
	m4_lockCount.AddString(_T("01"));
	m4_lockCount.AddString(_T("02"));
	// 读卡头数量
	m4_cardReaderCount.AddString(_T("00"));
	m4_cardReaderCount.AddString(_T("01"));
	m4_cardReaderCount.AddString(_T("02"));
	m4_cardReaderCount.AddString(_T("03"));
	m4_cardReaderCount.AddString(_T("04"));
	// 门锁1对应刷卡
	m4_slotCard1.AddString(_T("0+0+0+0"));
	m4_slotCard1.AddString(_T("1+0+0+0"));
	m4_slotCard1.AddString(_T("2+0+0+0"));
	m4_slotCard1.AddString(_T("3+0+0+0"));
	m4_slotCard1.AddString(_T("4+0+0+0"));
	m4_slotCard1.AddString(_T("1+2+3+4"));
	m4_slotCard1.AddString(_T("1+2+0+0"));
	m4_slotCard1.AddString(_T("1+3+0+0"));
	m4_slotCard1.AddString(_T("1+4+0+0"));
	m4_slotCard1.AddString(_T("2+3+0+0"));
	m4_slotCard1.AddString(_T("2+4+0+0"));
	m4_slotCard1.AddString(_T("3+4+0+0"));
	m4_slotCard1.AddString(_T("1+2+3+0"));
	m4_slotCard1.AddString(_T("1+3+4+0"));
	m4_slotCard1.AddString(_T("2+3+4+0"));
	// 门锁2对应刷卡
	m4_slotCard2.AddString(_T("0+0+0+0"));
	m4_slotCard2.AddString(_T("1+0+0+0"));
	m4_slotCard2.AddString(_T("2+0+0+0"));
	m4_slotCard2.AddString(_T("3+0+0+0"));
	m4_slotCard2.AddString(_T("4+0+0+0"));
	m4_slotCard2.AddString(_T("1+2+3+4"));
	m4_slotCard2.AddString(_T("1+2+0+0"));
	m4_slotCard2.AddString(_T("1+3+0+0"));
	m4_slotCard2.AddString(_T("1+4+0+0"));
	m4_slotCard2.AddString(_T("2+3+0+0"));
	m4_slotCard2.AddString(_T("2+4+0+0"));
	m4_slotCard2.AddString(_T("3+4+0+0"));
	m4_slotCard2.AddString(_T("1+2+3+0"));
	m4_slotCard2.AddString(_T("1+3+4+0"));
	m4_slotCard2.AddString(_T("2+3+4+0"));
	// 门禁开关是否上报
	m4_switchReport.AddString(_T("00 - 否"));
	m4_switchReport.AddString(_T("01 - 是"));

	/***************** 初始化组合框5 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO5_No ) )->SetCheck( TRUE );	// 选择不配置
	// 门禁类型
	m5_guardType.AddString(_T("00 - 密码"));
	m5_guardType.AddString(_T("01 - 刷卡"));
	m5_guardType.AddString(_T("02 - 禁用"));
	// 名单工作方式
	m5_listWorkMode.AddString(_T("00 - 黑"));
	m5_listWorkMode.AddString(_T("01 - 白"));
	// 预防方式
	m5_preventWay.AddString(_T("00 - 关门"));
	m5_preventWay.AddString(_T("01 - 按钮"));
	// 屏蔽模式
	m5_blockMode.AddString(_T("00 - 开门"));
	// 离开
	m5_leave.AddString(_T("00 - 门外刷卡"));
	// 卡号
	m5_cardID.AddString(_T("01 - 正常"));
	// 卡号类型
	m5_cardType.AddString(_T("00 - MF"));

	/***************** 初始化组合框6 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO6_No ) )->SetCheck( TRUE );	// 选择不配置
	// 启动节能
	m6_saveEnergy.AddString(_T("00 - 否"));
	m6_saveEnergy.AddString(_T("01 - 是"));
	// 空调数量
	m6_airConditionCount.AddString(_T("00"));
	m6_airConditionCount.AddString(_T("01"));
	m6_airConditionCount.AddString(_T("02"));
	// 空调类型
	m6_airConditionType.AddString(_T("00 - 单冷"));
	m6_airConditionType.AddString(_T("01 - 冷热"));
	// 隔日开启
	m6_startEveryOtherDay.AddString(_T("00 - 关闭"));
	m6_startEveryOtherDay.AddString(_T("01 - 两天"));
	m6_startEveryOtherDay.AddString(_T("02 - 三天"));
	// 风机电源
	m6_powerType.AddString(_T("00 - 直流"));
	m6_powerType.AddString(_T("01 - 交流"));
	// 输出通道
	m6_outputChannel.AddString(_T("00 - 内置"));
	m6_outputChannel.AddString(_T("01 - 外置"));
	// 数据上送
	m6_dataReport.AddString(_T("00 - 否"));
	m6_dataReport.AddString(_T("01 - 是"));
	// 风机类型
	m6_fanType.AddString(_T("00 - 通风"));
	m6_fanType.AddString(_T("01 - 换热"));

	/***************** 初始化组合框7 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO7_No ) )->SetCheck( TRUE );	// 选择不配置
	// 告警音
	m7_alarmSound.AddString(_T("00 - 关闭"));
	m7_alarmSound.AddString(_T("01 - 开启"));
	// 是否上送
	m7_isReport.AddString(_T("00 - 否"));
	m7_isReport.AddString(_T("01 - 是"));
	m7_isReport.AddString(_T("00 - 门禁"));
	m7_isReport.AddString(_T("01 - 动环"));
	// 告警类型
	m7_alarmType.AddString(_T("00 - 常闭"));
	m7_alarmType.AddString(_T("01 - 常开"));
	// 告警确认
	m7_alarmComfirm.AddString(_T("00 - 否"));
	m7_alarmComfirm.AddString(_T("01 - 是"));
	// 上送是否保存
	m7_saveReport.AddString(_T("00 - 否"));
	m7_saveReport.AddString(_T("01 - 是"));

	/***************** 初始化组合框8 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO8_No ) )->SetCheck( TRUE );	// 选择不配置
	// 链路
	m8_linkChain.AddString(_T("00 - GSM-SMS"));
	m8_linkChain.AddString(_T("01 - RS232"));
	m8_linkChain.AddString(_T("00 - MODEM"));
	m8_linkChain.AddString(_T("01 - GPRS"));
	// 主动拨号
	m8_activeDial.AddString(_T("00 - 否"));
	m8_activeDial.AddString(_T("01 - 是"));
	// SIM卡是否绑定
	m8_boundSIM.AddString(_T("00 - 否"));
	m8_boundSIM.AddString(_T("01 - 是"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CParamConfig1::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SCROLLINFO scrollinfo;
    GetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
    int unit=3;        
     switch (nSBCode)  
     {      
     case SB_LINEUP:          //Scroll one line up
         scrollinfo.nPos -= 1;  
         if (scrollinfo.nPos < scrollinfo.nMin)
         {  
             scrollinfo.nPos = scrollinfo.nMin;  
             break;  
         }  
         SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);  
         ScrollWindow(0, unit); 
         break;  
     case SB_LINEDOWN:           // Scroll one line down
         scrollinfo.nPos += 1;	 // 此处一定要注意加上滑块的长度，再作判断
         if ((UINT)scrollinfo.nPos + scrollinfo.nPage > (UINT)scrollinfo.nMax)  
         {  
             scrollinfo.nPos = scrollinfo.nMax;  
             break;  
         }  
         SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);  
         ScrollWindow(0, -unit);  
         break;  
     case SB_PAGEUP:            // Scroll one page up.
         scrollinfo.nPos -= 5;  
         if (scrollinfo.nPos <= scrollinfo.nMin)
         {  
             scrollinfo.nPos = scrollinfo.nMin;  
             break;  
         }  
         SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);  
         ScrollWindow(0, unit * 5);  
         break;  
     case SB_PAGEDOWN:			// Scroll one page down        
         scrollinfo.nPos += 5;  // 此处一定要注意加上滑块的长度，再作判断
         if ((UINT)scrollinfo.nPos + scrollinfo.nPage >= (UINT)scrollinfo.nMax)  
         {  
             scrollinfo.nPos = scrollinfo.nMax;  
             break;  
         }  
         SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);  
         ScrollWindow(0, -unit * 5);  
         break;  
     case SB_ENDSCROLL:      //End scroll     
         break;  
     case SB_THUMBPOSITION:  //Scroll to the absolute position. The current position is provided in nPos
         break;  
     case SB_THUMBTRACK:                  //Drag scroll box to specified position. The current position is provided in nPos
         ScrollWindow(0, (scrollinfo.nPos-nPos) * unit);  
         scrollinfo.nPos = nPos;  
         SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);
         break;  
     }

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
// 选择配置机器参数
void CParamConfig1::OnBnClickedRadio1Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_1 ) ) )->SetCheck( TRUE );
}
// 不配置机器参数
void CParamConfig1::OnBnClickedRadio1No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_1 ) ) )->SetCheck( FALSE );
}
// 选择配置空调参数
void CParamConfig1::OnBnClickedRadio2Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_2 ) ) )->SetCheck( TRUE );
}
// 不配置空调参数
void CParamConfig1::OnBnClickedRadio2No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_2 ) ) )->SetCheck( FALSE );
}
// 选择配置超级密码
void CParamConfig1::OnBnClickedRadio3Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_3 ) ) )->SetCheck( TRUE );
}
// 不配置超级密码
void CParamConfig1::OnBnClickedRadio3No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_3 ) ) )->SetCheck( FALSE );
}
// 选择配置开锁参数
void CParamConfig1::OnBnClickedRadio4Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_4 ) ) )->SetCheck( TRUE );
}
// 不配置开锁参数
void CParamConfig1::OnBnClickedRadio4No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_4 ) ) )->SetCheck( FALSE );
}
// 选择配置门禁参数
void CParamConfig1::OnBnClickedRadio5Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_5 ) ) )->SetCheck( TRUE );
}
// 不配置门禁参数
void CParamConfig1::OnBnClickedRadio5No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_5 ) ) )->SetCheck( FALSE );
}
// 选择配置风机参数
void CParamConfig1::OnBnClickedRadio6Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_6 ) ) )->SetCheck( TRUE );
}
// 不配置风机参数
void CParamConfig1::OnBnClickedRadio6No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_6 ) ) )->SetCheck( FALSE );
}
// 选择配置告警参数
void CParamConfig1::OnBnClickedRadio7Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_7 ) ) )->SetCheck( TRUE );
}
// 不配置告警参数
void CParamConfig1::OnBnClickedRadio7No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_7 ) ) )->SetCheck( FALSE );
}
// 选择配置通信方式
void CParamConfig1::OnBnClickedRadio8Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_8 ) ) )->SetCheck( TRUE );
}
// 不配置通信方式
void CParamConfig1::OnBnClickedRadio8No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_8 ) ) )->SetCheck( FALSE );
}
