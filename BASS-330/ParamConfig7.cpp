// ParamConfig7.cpp : 实现文件
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig7.h"
#include "BASS-330Dlg.h"
#include "ProtocolHandle.h"
#include "MySQLInterface.h"
#include <vector>
#include <string>
// CParamConfig7 对话框

IMPLEMENT_DYNAMIC(CParamConfig7, CDialog)

CParamConfig7::CParamConfig7(CWnd* pParent /*=NULL*/)
	: CDialog(CParamConfig7::IDD, pParent)
	, m_pGetSystimeAndPasswordThread(NULL)
	, m_pTestDoThread(NULL)
	, m_ParamSuccessCount(0)
	, m_pSetAllThread(NULL)
{

}

CParamConfig7::~CParamConfig7()
{
}

void CParamConfig7::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_7_5, m_Edit_Time_Passwod);
	DDX_Control(pDX, IDC_EDIT_7_2, m_Edit_AIDI);
	DDX_Control(pDX, IDC_COMBO_7_1, m_ComboBox_Param);
	DDX_Control(pDX, IDC_COMBO_7_2, m_ComboBox_Channel);
	DDX_Control(pDX, IDC_COMBO_7_3, m_ComboBox_List);
}


BEGIN_MESSAGE_MAP(CParamConfig7, CDialog)
	ON_BN_CLICKED(IDC_RADIO_7_1, &CParamConfig7::OnBnClickedRadio_7_1)
	ON_BN_CLICKED(IDC_RADIO_7_2, &CParamConfig7::OnBnClickedRadio_7_2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_7_1, &CParamConfig7::OnBnClickedCheck_7_1)
	ON_BN_CLICKED(IDC_CHECK_7_2, &CParamConfig7::OnBnClickedCheck_7_2)
	ON_BN_CLICKED(IDC_CHECK_7_3, &CParamConfig7::OnBnClickedCheck_7_3)
	ON_BN_CLICKED(IDC_CHECK_7_4, &CParamConfig7::OnBnClickedCheck_7_4)
	ON_BN_CLICKED(IDC_CHECK_7_5, &CParamConfig7::OnBnClickedCheck_7_5)
	ON_BN_CLICKED(IDC_CHECK_7_6, &CParamConfig7::OnBnClickedCheck_7_6)
	ON_BN_CLICKED(IDC_CHECK_7_7, &CParamConfig7::OnBnClickedCheck_7_7)
	ON_BN_CLICKED(IDC_CHECK_7_8, &CParamConfig7::OnBnClickedCheck_7_8)
	ON_BN_CLICKED(IDC_CHECK_7_9, &CParamConfig7::OnBnClickedCheck_7_9)
	ON_BN_CLICKED(IDC_CHECK_7_10, &CParamConfig7::OnBnClickedCheck_7_10)
	ON_BN_CLICKED(IDC_CHECK_7_11, &CParamConfig7::OnBnClickedCheck_7_11)
	ON_BN_CLICKED(IDC_CHECK_7_12, &CParamConfig7::OnBnClickedCheck_7_12)
	ON_BN_CLICKED(IDC_CHECK_7_13, &CParamConfig7::OnBnClickedCheck_7_13)
	ON_BN_CLICKED(IDC_CHECK_7_14, &CParamConfig7::OnBnClickedCheck_7_14)
	ON_BN_CLICKED(IDC_CHECK_7_15, &CParamConfig7::OnBnClickedCheck_7_15)
	ON_BN_CLICKED(IDC_CHECK_7_16, &CParamConfig7::OnBnClickedCheck_7_16)
	ON_BN_CLICKED(IDC_CHECK_7_17, &CParamConfig7::OnBnClickedCheck_7_17)
	ON_BN_CLICKED(IDC_CHECK_7_18, &CParamConfig7::OnBnClickedCheck_7_18)
	ON_BN_CLICKED(IDC_CHECK_7_19, &CParamConfig7::OnBnClickedCheck_7_19)
	ON_BN_CLICKED(IDC_CHECK_7_24, &CParamConfig7::OnBnClickedCheck_7_20)
	ON_BN_CLICKED(IDC_CHECK_7_25, &CParamConfig7::OnBnClickedCheck_7_21)
	ON_BN_CLICKED(IDC_CHECK_7_26, &CParamConfig7::OnBnClickedCheck_7_22)
	ON_BN_CLICKED(IDC_CHECK_7_27, &CParamConfig7::OnBnClickedCheck_7_23)
	ON_BN_CLICKED(IDC_BUTTON_7_5, &CParamConfig7::OnBnClickedButton_Get_Systime_And_SuperPassword)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_7_4, &CParamConfig7::OnBnClickedButton_Test)
	ON_BN_CLICKED(IDC_BUTTON_7_1, &CParamConfig7::OnBnClickedButtonParamExport)
	ON_CBN_SELCHANGE(IDC_COMBO_7_1, &CParamConfig7::OnCbnSelchangeComboParam)
	ON_BN_CLICKED(IDC_BUTTON_7_2, &CParamConfig7::OnBnClickedButtonChannelExport)
	ON_CBN_SELCHANGE(IDC_COMBO_7_2, &CParamConfig7::OnCbnSelchangeComboChannel)
	ON_CBN_SELCHANGE(IDC_COMBO_7_3, &CParamConfig7::OnCbnSelchangeComboList)
	ON_BN_CLICKED(IDC_BUTTON_7_3, &CParamConfig7::OnBnClickedButtonListExport)
	ON_BN_CLICKED(IDC_BUTTON_7_6, &CParamConfig7::OnBnClickedButtonParamResetCnt)
	ON_BN_CLICKED(IDC_BUTTON_7_7, &CParamConfig7::OnBnClickedButtonSetAll)
END_MESSAGE_MAP()


// CParamConfig7 消息处理程序

BOOL CParamConfig7::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 初始化子窗口全局指针7
	pSubDlg7 = this;

	LoadParamConfig(PARAM_INIT);

	// 初始化定时器锁 临界区
	InitializeCriticalSection(&m_TimeLock);

	// 开启定时器
	SetTimer(SYSTEM_TIME_TIMER, 1000, NULL);

	// 设置编结果显示辑框字体
	m_Font.DeleteObject();
	m_Font.CreatePointFont(250, _T("微软雅黑"));
	m_Edit_Time_Passwod.SetFont(&m_Font);
	m_Edit_AIDI.SetFont(&m_Font);
	
	// 初始化参数配置下拉框
	InitParamComboBox();
	// 初始化通道配置下拉框
	InitChannelComboBox();
	// 初始化名单配置下拉框
	InitListComboBox();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 定时器回调函数
void CParamConfig7::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if( SYSTEM_TIME_TIMER == nIDEvent )
	{
		CTime RealTime = CTime::GetCurrentTime();
		SetDlgItemText(IDC_EDIT_RTC, RealTime.Format( _T(" %Y-%m-%d  %H:%M:%S") ) );
	}

	CDialog::OnTimer(nIDEvent);
}
// 销毁该对话框所有定时器
void CParamConfig7::StopAllTimer()
{
	EnterCriticalSection(&m_TimeLock);
	KillTimer( SYSTEM_TIME_TIMER );		// 销毁系统时间定时器
	LeaveCriticalSection(&m_TimeLock);

	DeleteCriticalSection(&m_TimeLock); // 删除定时器临界区
}
// 控件颜色更改
HBRUSH CParamConfig7::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch( pWnd->GetDlgCtrlID() )
	{
		case IDC_EDIT_7_5:
			 pDC->SetTextColor( m_ResColor7_5 );
			 break;
		case IDC_EDIT_7_2:
			 pDC->SetTextColor( m_ResColor7_2 );
			 break;
		case IDC_EDIT_7_7:
			 pDC->SetTextColor( m_ResColor7_7 );
			 break;
		default:
			 break;
	}
	return hbr;
}


// 以下 "OnBnClickedCheck_7_1 - 7_23" 函数同步操作页面和参数配置页面的配置选项
// 机器参数按钮
void CParamConfig7::OnBnClickedCheck_7_1()		
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO1_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO1_No ) );	// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_1 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}	
}
// 空调参数按钮
void CParamConfig7::OnBnClickedCheck_7_2()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO2_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO2_No ) );	// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_2 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 超级密码设置按钮
void CParamConfig7::OnBnClickedCheck_7_3()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO3_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO3_No ) );	// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_3 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 开锁参数按钮
void CParamConfig7::OnBnClickedCheck_7_4()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO4_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO4_No ) );	// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_4 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 门禁参数按钮
void CParamConfig7::OnBnClickedCheck_7_5()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO5_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO5_No ) );	// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_5 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 风机参数按钮
void CParamConfig7::OnBnClickedCheck_7_6()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO6_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO6_No ) );	// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_6 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 告警参数按钮
void CParamConfig7::OnBnClickedCheck_7_7()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO7_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO7_No ) );	// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_7 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 通信方式按钮
void CParamConfig7::OnBnClickedCheck_7_8()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO8_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO8_No ) );	// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_8 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 防盗参数按钮
void CParamConfig7::OnBnClickedCheck_7_9()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO9_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO9_No ) );	// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_9 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 联动类型按钮
void CParamConfig7::OnBnClickedCheck_7_10()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO10_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO10_No ) );		// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_10 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 告警联动按钮
void CParamConfig7::OnBnClickedCheck_7_11()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO11_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO11_No ) );		// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_11 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 拍照设置按钮
void CParamConfig7::OnBnClickedCheck_7_12()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO12_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO12_No ) );		// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_12 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 智能监控按钮
void CParamConfig7::OnBnClickedCheck_7_13()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO13_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO13_No ) );		// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_13 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 三相电按钮
void CParamConfig7::OnBnClickedCheck_7_14()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO14_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO14_No ) );		// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_14 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 串口参数按钮
void CParamConfig7::OnBnClickedCheck_7_15()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO15_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO15_No ) );		// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_15 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 室外告警按钮
void CParamConfig7::OnBnClickedCheck_7_16()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO16_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO16_No ) );		// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_16 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 振动设置按钮
void CParamConfig7::OnBnClickedCheck_7_17()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO17_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO17_No ) );		// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_17 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 插卡取电按钮
void CParamConfig7::OnBnClickedCheck_7_18()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO18_Yes ) );	// 配置按钮控件指针 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO18_No ) );		// 不配置按钮控件指针
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_18 ) )->GetCheck( ) )
	{
		pRadioButtonYes->SetCheck( TRUE );
		pRadioButtonNo->SetCheck( FALSE );
	}
	else
	{
		pRadioButtonNo->SetCheck( TRUE );
		pRadioButtonYes->SetCheck( FALSE );
	}
}
// 设置系统时间 暂空
void CParamConfig7::OnBnClickedCheck_7_19()
{
	// TODO: 在此添加控件通知处理程序代码

}
// 选择16通道,与32通道互斥
void CParamConfig7::OnBnClickedCheck_7_20()
{
	CButton * pRadioButton16CH = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_16CH ) );	// 16通道 
	CButton * pRadioButton32CH = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_32CH ) );	// 32通道
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_24 ) )->GetCheck( ) )
	{
		pRadioButton16CH->SetCheck( TRUE );
		pRadioButton32CH->SetCheck( FALSE );
		if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_25 ) )->GetCheck( ) )
		{
			( ( CButton* )GetDlgItem( IDC_CHECK_7_25 ) )->SetCheck( FALSE );
		}
	}
	else
	{
		pRadioButton16CH->SetCheck( FALSE );
	}
}
// 选择32通道,与16通道互斥
void CParamConfig7::OnBnClickedCheck_7_21()
{
	CButton * pRadioButton16CH = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_16CH ) );	// 16通道
	CButton * pRadioButton32CH = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_32CH ) );	// 32通道
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_25 ) )->GetCheck( ) )
	{
		pRadioButton32CH->SetCheck( TRUE );
		pRadioButton16CH->SetCheck( FALSE );
		if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_24 ) )->GetCheck( ) )
		{
			( ( CButton* )GetDlgItem( IDC_CHECK_7_24 ) )->SetCheck( FALSE );
		}
	}
	else
	{
		pRadioButton32CH->SetCheck( FALSE );
	}
}
// 选通用版本,与2M版本互斥
void CParamConfig7::OnBnClickedCheck_7_22()
{
	CButton * pRadioButtonTY = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_CFG_1 ) );	// 通用 
	CButton * pRadioButton2M = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_CFG_2 ) );	// 2M
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_26 ) )->GetCheck( ) )
	{
		pRadioButtonTY->SetCheck( TRUE );
		pRadioButton2M->SetCheck( FALSE );
		if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_27 ) )->GetCheck( ) )
		{
			( ( CButton* )GetDlgItem( IDC_CHECK_7_27 ) )->SetCheck( FALSE );
		}
		pSubDlg4->m_ComboBox_WorkList.EnableWindow( FALSE );
		pSubDlg4->m_DateTime.EnableWindow( FALSE );
	}
	else
	{
		pRadioButtonTY->SetCheck( FALSE );
		pSubDlg4->m_ComboBox_WorkList.EnableWindow( TRUE );
		pSubDlg4->m_DateTime.EnableWindow( TRUE );
	}
}
// 选2M版本,与通用版本互斥
void CParamConfig7::OnBnClickedCheck_7_23()
{
	CButton * pRadioButtonTY = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_CFG_1 ) );	// 通用 
	CButton * pRadioButton2M = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_CFG_2 ) );	// 2M
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_27 ) )->GetCheck( ) )
	{
		pRadioButton2M->SetCheck( TRUE );
		pRadioButtonTY->SetCheck( FALSE );
		if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_26 ) )->GetCheck( ) )
		{
			( ( CButton* )GetDlgItem( IDC_CHECK_7_26 ) )->SetCheck( FALSE );
			pSubDlg4->m_ComboBox_WorkList.EnableWindow( TRUE );
			pSubDlg4->m_DateTime.EnableWindow( TRUE );
		}
	}
	else
	{
		pRadioButton2M->SetCheck( FALSE );
		pSubDlg4->m_ComboBox_WorkList.EnableWindow( FALSE );
		pSubDlg4->m_DateTime.EnableWindow( FALSE );
	}
}

// 全选按钮
void CParamConfig7::OnBnClickedRadio_7_1()
{
	for(int i = IDC_CHECK_7_1; i <= IDC_CHECK_7_19; i++) 
	{
		if( GetDlgItem( i ) ) // 防止空指针
		{
			( ( CButton *)GetDlgItem( i ) )->SetCheck( TRUE );
		}
	}
	// 配置按钮全选
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO1_Yes ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO2_Yes ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO3_Yes ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO4_Yes ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO5_Yes ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO6_Yes ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO7_Yes ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO8_Yes ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO9_Yes ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO10_Yes) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO11_Yes) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO12_Yes) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO13_Yes) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO14_Yes) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO15_Yes) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO16_Yes) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO17_Yes) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO18_Yes) ) )->SetCheck( TRUE );
	// 不配置按钮全不选
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO1_No ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO2_No ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO3_No ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO4_No ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO5_No ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO6_No ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO7_No ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO8_No ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO9_No ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO10_No) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO11_No) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO12_No) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO13_No) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO14_No) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO15_No) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO16_No) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO17_No) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO18_No) ) )->SetCheck( FALSE );
}

// 全不选按钮
void CParamConfig7::OnBnClickedRadio_7_2()
{
	for(int i = IDC_CHECK_7_1; i <= IDC_CHECK_7_19; i++) 
	{
		if( GetDlgItem( i ) ) // 防止空指针
		{
			( ( CButton *)GetDlgItem( i ) )->SetCheck( FALSE );
		}
	}
	// 不配置按钮全选
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO1_No ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO2_No ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO3_No ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO4_No ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO5_No ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO6_No ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO7_No ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO8_No ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO9_No ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO10_No) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO11_No) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO12_No) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO13_No) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO14_No) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO15_No) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO16_No) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO17_No) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO18_No) ) )->SetCheck( TRUE );
	// 配置按钮全不选
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO1_Yes ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO2_Yes ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO3_Yes ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO4_Yes ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO5_Yes ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO6_Yes ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO7_Yes ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO8_Yes ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO9_Yes ) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO10_Yes) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO11_Yes) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO12_Yes) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO13_Yes) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO14_Yes) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO15_Yes) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO16_Yes) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO17_Yes) ) )->SetCheck( FALSE );
	( ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO18_Yes) ) )->SetCheck( FALSE );
}

void CParamConfig7::OnBnClickedButton_Get_Systime_And_SuperPassword()
{
	if( !pMainDlg->m_bIsOpenSerl )
	{
		MessageBox("请先打开串口！", "提示", MB_ICONWARNING);
		return;
	}
	if( FALSE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_22 ) ) )->GetCheck( ) && \
		FALSE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_23 ) ) )->GetCheck( ) )
	{
		AfxMessageBox("请先勾选待读取选项！");
		return;
	}
	if(m_pGetSystimeAndPasswordThread)
    {
        ::TerminateThread(m_pGetSystimeAndPasswordThread->m_hThread, 0);
        m_pGetSystimeAndPasswordThread = NULL;
    }
	m_pGetSystimeAndPasswordThread = AfxBeginThread(GetSystimeAndPasswordThread, this);
}

UINT CParamConfig7::GetSystimeAndPasswordThread(LPVOID pParam)
{
	CEdit *ResultEdit = ( CEdit* )( pSubDlg7->GetDlgItem( IDC_EDIT_7_5 ) );
	// 读取系统时间
    if( TRUE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_22 ) ) )->GetCheck( ) )
    {
		CProtocolHandle ComProto;
		BYTE RecvBuffer[PACKET_SIZE] = {0};

		int length = ComProto.Package(0x07, NULL, 0);
		pMainDlg->is2MPacket = false;
		pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// 发送数据

		WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// 等待串口接收完成一帧数据
		if(pMainDlg->m_bRecvPacketTail == false)						// 检查标志位 超过3秒没收到包尾
		{
			TRACE("Receive overtime!\n");
			ResultEdit->SetWindowText(" 1-NG !");
			pSubDlg7->m_ResColor7_5 = cRED;
			return FALSE;
		}
		int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
		RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));

		if(FALSE == ComProto.GetPureData(0x07, RecvBuffer, RecvBufLen))
		{
			ResultEdit->SetWindowText(" 1-NG !");
			pSubDlg7->m_ResColor7_5 = cRED;
			return FALSE;
		}
		CString BASS330Time;
		BASS330Time += ToString(ComProto.PureData[0]+2000);
		BASS330Time += "-";
		BASS330Time += ToString(ComProto.PureData[1]);
		BASS330Time += "-";
		BASS330Time += ToString(ComProto.PureData[2]);
		BASS330Time += " ";
		BASS330Time += ToString(ComProto.PureData[3]);
		BASS330Time += ":";
		BASS330Time += ToString(ComProto.PureData[4]);
		BASS330Time += ":";
		BASS330Time += ToString(ComProto.PureData[5]);
		( ( CEdit* )( pSubDlg7->GetDlgItem( IDC_EDIT_7_3 ) ) )->SetWindowText(BASS330Time);
    }
	// 读取超级密码
	if( TRUE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_23 ) ) )->GetCheck( ) )
    {
		CProtocolHandle ComProto;
		BYTE RecvBuffer[PACKET_SIZE] = {0};

		int length = ComProto.Package(0x1D, NULL, 0);
		pMainDlg->is2MPacket = false;
		pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// 发送数据
		
		WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// 等待串口接收完成一帧数据
		if(pMainDlg->m_bRecvPacketTail == false)						// 检查标志位 超过3秒没收到包尾
		{
			TRACE("Receive overtime!\n");
			ResultEdit->SetWindowText(" 1-NG !");
			pSubDlg7->m_ResColor7_5 = cRED;
			return FALSE;
		}

		int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
		RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));

		if(FALSE == ComProto.GetPureData(0x1D, RecvBuffer, RecvBufLen))
		{
			ResultEdit->SetWindowText(" 2-NG !");
			pSubDlg7->m_ResColor7_5 = cRED;
			return FALSE;
		}
		CString SuperPassword;
		SuperPassword += hexToStrNoBlank(ComProto.PureData, 3);
		( ( CEdit* )( pSubDlg7->GetDlgItem( IDC_EDIT_7_4 ) ) )->SetWindowText(SuperPassword);
    }
	ResultEdit->SetWindowText("  OK !");
	pSubDlg7->m_ResColor7_5 = cGREEN;

	return TRUE;
}
void CParamConfig7::OnBnClickedButton_Test()
{
	if( !pMainDlg->m_bIsOpenSerl )
	{
		MessageBox("请先打开串口！", "提示", MB_ICONWARNING);
		return;
	}
	if( FALSE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_20 ) ) )->GetCheck( ) && \
		FALSE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_21 ) ) )->GetCheck( ) )
	{
		AfxMessageBox("请先勾选待测试选项！");
		return;
	}
	if(m_pTestDoThread)
    {
        ::TerminateThread(m_pTestDoThread->m_hThread, 0);
        m_pTestDoThread = NULL;
    }
	m_pTestDoThread = AfxBeginThread(TestDoThread, this);
}

UINT CParamConfig7::TestDoThread(LPVOID pParam)
{
	CEdit *ResultEdit = ( CEdit* )( pSubDlg7->GetDlgItem( IDC_EDIT_7_2 ) );
	// 测试AIDI采集
    if( TRUE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_20 ) ) )->GetCheck( ) )
    {
		CProtocolHandle ComProto;
		BYTE RecvBuffer[PACKET_SIZE] = {0};
		BYTE SendData = 0x00;
		int length = ComProto.Package(0x55, &SendData, 1);
		pMainDlg->is2MPacket = false;
		pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// 发送数据

		WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// 等待串口接收完成一帧数据
		if(pMainDlg->m_bRecvPacketTail == false)						// 检查标志位 超过3秒没收到包尾
		{
			TRACE("Receive overtime!\n");
			ResultEdit->SetWindowText(" 1-NG !");
			pSubDlg7->m_ResColor7_2 = cRED;
			return FALSE;
		}
		int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
		RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));

		if(FALSE == ComProto.GetPureData(0x55, RecvBuffer, RecvBufLen))
		{
			ResultEdit->SetWindowText(" 1-NG !");
			pSubDlg7->m_ResColor7_2 = cRED;
			return FALSE;
		}
		std::vector<int> AiDiValue(32, 0);
		for(int i = 0, j = 0; i < 64; i++, j++)
		{
			AiDiValue[j] += ComProto.PureData[i]; 
			AiDiValue[j] = (AiDiValue[j] << 8);
			AiDiValue[j] += ComProto.PureData[++i];
		}
		if(pSubDlg6->AiDiTest(AiDiValue) == false)
		{
			ResultEdit->SetWindowText(" 1-NG !");
			pSubDlg7->m_ResColor7_2 = cRED;
			return FALSE;
		}
    }
	// 测试继电器和光耦
	if( TRUE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_21 ) ) )->GetCheck( ) )
    {
		CProtocolHandle ComProto;
		BYTE RecvBuffer[PACKET_SIZE] = {0};
		BYTE SendData = 0x01;
		int length = ComProto.Package(0x55, &SendData, 1);
		pMainDlg->is2MPacket = false;
		pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// 发送数据

		WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// 等待串口接收完成一帧数据
		if(pMainDlg->m_bRecvPacketTail == false)						// 检查标志位 超过3秒没收到包尾
		{
			TRACE("Receive overtime!\n");
			ResultEdit->SetWindowText(" 2-NG !");
			pSubDlg7->m_ResColor7_2 = cRED;
			return FALSE;
		}
		int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
		RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));

		if(FALSE == ComProto.isVaildPacket(0x55, RecvBuffer, RecvBufLen))
		{
			ResultEdit->SetWindowText(" 2-NG !");
			pSubDlg7->m_ResColor7_2 = cRED;
			return FALSE;
		}
    }
	ResultEdit->SetWindowText("  OK !");
	pSubDlg7->m_ResColor7_2 = cGREEN;

	return TRUE;
}

// 初始化参数配置下拉框
bool CParamConfig7::InitParamComboBox()
{
	using namespace std;

	m_ComboBox_Param.ResetContent();
	pSubDlg3->m_ComboBox_Param.ResetContent();

	MySQLInterface uMySQL;
	uMySQL.SetMySQLConInfo(SERVER, USER, PASSWORD, DATABASE, PORT);

	if(uMySQL.Open() == false)
	{
		TRACE("MySQL Connect Faild!\r\n");
		return false;
	}
	vector<vector<string>> data;
	string strsql = "SELECT DISTINCT PZMC FROM paramconfig";
	uMySQL.Select(strsql, data);

	for(unsigned int i = 0; i < data.size(); i++)
	{
		CString temp(data[i][0].c_str());
		m_ComboBox_Param.AddString(temp);
		(pSubDlg3->m_ComboBox_Param).AddString(temp);
	}
	m_ComboBox_Param.SetCurSel( 0 );
	(pSubDlg3->m_ComboBox_Param).SetCurSel( 0 );
	uMySQL.Close();
	return true;
}

// 初始化通道配置下拉框
bool CParamConfig7::InitChannelComboBox()
{
	using namespace std;

	m_ComboBox_Channel.ResetContent();
	pSubDlg4->m_ComboBox_Channel.ResetContent();

	MySQLInterface uMySQL;
	uMySQL.SetMySQLConInfo(SERVER, USER, PASSWORD, DATABASE, PORT);

	if(uMySQL.Open() == false)
	{
		TRACE("MySQL Connect Faild!\r\n");
		return false;
	}
	vector<vector<string>> data;
	string strsql = "SELECT DISTINCT PeiZhiMC FROM channelconfig";
	uMySQL.Select(strsql, data);

	for(unsigned int i = 0; i < data.size(); i++)
	{
		CString temp(data[i][0].c_str());
		m_ComboBox_Channel.AddString(temp);
		(pSubDlg4->m_ComboBox_Channel).AddString(temp);
	}
	m_ComboBox_Channel.SetCurSel( 3 );
	(pSubDlg4->m_ComboBox_Channel).SetCurSel( 3 );
	uMySQL.Close();
	return true;
}

// 初始化名单配置下拉框
bool CParamConfig7::InitListComboBox()
{
	using namespace std;

	m_ComboBox_List.ResetContent();
	pSubDlg4->m_ComboBox_List.ResetContent();

	MySQLInterface uMySQL;
	uMySQL.SetMySQLConInfo(SERVER, USER, PASSWORD, DATABASE, PORT);

	if(uMySQL.Open() == false)
	{
		TRACE("MySQL Connect Faild!\r\n");
		return false;
	}
	vector<vector<string>> data;
	string strsql = "SELECT DISTINCT PZMingCheng FROM listconfig";
	uMySQL.Select(strsql, data);

	for(unsigned int i = 0; i < data.size(); i++)
	{
		CString temp(data[i][0].c_str());
		m_ComboBox_List.AddString(temp);
		(pSubDlg4->m_ComboBox_List).AddString(temp);
	}
	m_ComboBox_List.SetCurSel( 0 );
	(pSubDlg4->m_ComboBox_List).SetCurSel( 0 );
	uMySQL.Close();
	return true;
}

// 从数据库加载配置参数
bool CParamConfig7::LoadParamConfig(std::string pzmc)
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
	string strsql = "SELECT Check_7_1, Check_7_2, Check_7_3, Check_7_4, Check_7_5, Check_7_6, Check_7_7, ";
	strsql += "Check_7_8, Check_7_9, Check_7_10, Check_7_11, Check_7_12, Check_7_13, Check_7_14, Check_7_15, ";
	strsql += "Check_7_16, Check_7_17, Check_7_18, Check_7_19, Check_7_20, Check_7_21, Check_7_22, Check_7_23, ";
	strsql += "Radio_7_3, Radio_7_4, Radio_7_5, Radio_7_6, Radio_7_7, Radio_16CH, Radio_32CH, Radio_TY, Radio_2M ";
	strsql += "FROM paramconfig WHERE PZMC = '" + pzmc + "'";

	if(uMySQL.Select(strsql, data) == false)
	{
		uMySQL.Close();
		return false;
	}

	// 选择是否配置
	((CButton*)GetDlgItem(IDC_CHECK_7_1))->SetCheck(stoi(data[0][0]));
	((CButton*)GetDlgItem(IDC_CHECK_7_2))->SetCheck(stoi(data[0][1]));
	((CButton*)GetDlgItem(IDC_CHECK_7_3))->SetCheck(stoi(data[0][2]));
	((CButton*)GetDlgItem(IDC_CHECK_7_4))->SetCheck(stoi(data[0][3]));
	((CButton*)GetDlgItem(IDC_CHECK_7_5))->SetCheck(stoi(data[0][4]));
	((CButton*)GetDlgItem(IDC_CHECK_7_6))->SetCheck(stoi(data[0][5]));
	((CButton*)GetDlgItem(IDC_CHECK_7_7))->SetCheck(stoi(data[0][6]));
	((CButton*)GetDlgItem(IDC_CHECK_7_8))->SetCheck(stoi(data[0][7]));
	((CButton*)GetDlgItem(IDC_CHECK_7_9))->SetCheck(stoi(data[0][8]));
	((CButton*)GetDlgItem(IDC_CHECK_7_10))->SetCheck(stoi(data[0][9]));
	((CButton*)GetDlgItem(IDC_CHECK_7_11))->SetCheck(stoi(data[0][10]));
	((CButton*)GetDlgItem(IDC_CHECK_7_12))->SetCheck(stoi(data[0][11]));
	((CButton*)GetDlgItem(IDC_CHECK_7_13))->SetCheck(stoi(data[0][12]));
	((CButton*)GetDlgItem(IDC_CHECK_7_14))->SetCheck(stoi(data[0][13]));
	((CButton*)GetDlgItem(IDC_CHECK_7_15))->SetCheck(stoi(data[0][14]));
	((CButton*)GetDlgItem(IDC_CHECK_7_16))->SetCheck(stoi(data[0][15]));
	((CButton*)GetDlgItem(IDC_CHECK_7_17))->SetCheck(stoi(data[0][16]));
	((CButton*)GetDlgItem(IDC_CHECK_7_18))->SetCheck(stoi(data[0][17]));
	((CButton*)GetDlgItem(IDC_CHECK_7_19))->SetCheck(stoi(data[0][18]));
	((CButton*)GetDlgItem(IDC_CHECK_7_24))->SetCheck(stoi(data[0][19]));
	((CButton*)GetDlgItem(IDC_CHECK_7_25))->SetCheck(stoi(data[0][20]));
	((CButton*)GetDlgItem(IDC_CHECK_7_26))->SetCheck(stoi(data[0][21]));
	((CButton*)GetDlgItem(IDC_CHECK_7_27))->SetCheck(stoi(data[0][22]));
	((CButton*)GetDlgItem(IDC_RADIO_7_3))->SetCheck(stoi(data[0][23]));
	((CButton*)GetDlgItem(IDC_RADIO_7_4))->SetCheck(stoi(data[0][24]));
	((CButton*)GetDlgItem(IDC_RADIO_7_5))->SetCheck(stoi(data[0][25]));
	((CButton*)GetDlgItem(IDC_RADIO_7_6))->SetCheck(stoi(data[0][26]));
	((CButton*)GetDlgItem(IDC_RADIO_7_7))->SetCheck(stoi(data[0][27]));

	((CButton*)(pSubDlg4->GetDlgItem(IDC_RADIO_16CH)))->SetCheck(stoi(data[0][28]));
	((CButton*)(pSubDlg4->GetDlgItem(IDC_RADIO_32CH)))->SetCheck(stoi(data[0][29]));
	((CButton*)(pSubDlg4->GetDlgItem(IDC_RADIO_CFG_1)))->SetCheck(stoi(data[0][30]));
	((CButton*)(pSubDlg4->GetDlgItem(IDC_RADIO_CFG_2)))->SetCheck(stoi(data[0][31]));

	uMySQL.Close();
	return true;
}
// 参数配置导出按钮
void CParamConfig7::OnBnClickedButtonParamExport()
{
	CString TempStr;
	m_ComboBox_Param.GetWindowText(TempStr);
	pSubDlg3->m_ComboBox_Param.SetWindowText(TempStr);
	pSubDlg3->OnBnClickedButtonExport();
}
// 同步参数组合框
void CParamConfig7::OnCbnSelchangeComboParam()
{
	CString TempStr;
	int nSel = m_ComboBox_Param.GetCurSel();    
    m_ComboBox_Param.GetLBText(nSel, TempStr);
	pSubDlg3->m_ComboBox_Param.SetWindowText(TempStr);
}

// 通道配置导出按钮
void CParamConfig7::OnBnClickedButtonChannelExport()
{
	CString TempStr;
	m_ComboBox_Channel.GetWindowText(TempStr);
	pSubDlg4->m_ComboBox_Channel.SetWindowText(TempStr);
	pSubDlg4->OnBnClickedButtonPathExport();
}
// 同步通道组合框
void CParamConfig7::OnCbnSelchangeComboChannel()
{
	CString TempStr;
	int nSel = m_ComboBox_Channel.GetCurSel();    
    m_ComboBox_Channel.GetLBText(nSel, TempStr);
	pSubDlg4->m_ComboBox_Channel.SetWindowText(TempStr);
}


// 名单配置导出按钮
void CParamConfig7::OnBnClickedButtonListExport()
{
	CString TempStr;
	m_ComboBox_List.GetWindowText(TempStr);
	pSubDlg4->m_ComboBox_List.SetWindowText(TempStr);
	pSubDlg4->OnBnClickedButtonListExport();
}
// 同步名单组合框
void CParamConfig7::OnCbnSelchangeComboList()
{
	CString TempStr;
	int nSel = m_ComboBox_List.GetCurSel();    
    m_ComboBox_List.GetLBText(nSel, TempStr);
	pSubDlg4->m_ComboBox_List.SetWindowText(TempStr);
}

// 参数配置成功次数清零
void CParamConfig7::OnBnClickedButtonParamResetCnt()
{
	m_ParamSuccessCount = 0;
	SetDlgItemText(IDC_EDIT_7_6, ToString(m_ParamSuccessCount));
}

// 开始配置所有参数
void CParamConfig7::OnBnClickedButtonSetAll()
{
	if( !pMainDlg->m_bIsOpenSerl )
	{
		MessageBox("请先打开串口！", "提示", MB_ICONWARNING);
		return;
	}
	if(IDCANCEL == MessageBox("确认配置所有参数吗？", "提示", MB_OKCANCEL | MB_ICONQUESTION))
        return;

	if(m_pSetAllThread)
    {
        ::TerminateThread(m_pSetAllThread->m_hThread, 0);
        m_pSetAllThread = NULL;
    }
	m_pSetAllThread = AfxBeginThread(SetAllThread, this);
}

UINT CParamConfig7::SetAllThread(LPVOID pParam)
{
	if(((CButton*)(pSubDlg7->GetDlgItem(IDC_CHECK_7_1)))->GetCheck() == TRUE)
	{
		
	}
	return TRUE;
}
