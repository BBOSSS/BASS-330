// ParamConfig7.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig7.h"
#include "BASS-330Dlg.h"
#include "ProtocolHandle.h"
#include "MySQLInterface.h"
#include <vector>
#include <string>
// CParamConfig7 �Ի���

IMPLEMENT_DYNAMIC(CParamConfig7, CDialog)

CParamConfig7::CParamConfig7(CWnd* pParent /*=NULL*/)
	: CDialog(CParamConfig7::IDD, pParent)
	, m_pGetSystimeAndPasswordThread(NULL)
	, m_pTestDoThread(NULL)
	, m_ParamSuccessCount(0)
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
END_MESSAGE_MAP()


// CParamConfig7 ��Ϣ�������

BOOL CParamConfig7::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// ��ʼ���Ӵ���ȫ��ָ��7
	pSubDlg7 = this;

	LoadParamConfig("BASS330CPU����");

	// ��ʼ����ʱ���� �ٽ���
	InitializeCriticalSection(&m_TimeLock);

	// ������ʱ��
	SetTimer(SYSTEM_TIME_TIMER, 1000, NULL);

	// ���ñ�����ʾ��������
	m_Font.DeleteObject();
	m_Font.CreatePointFont(250, _T("΢���ź�"));
	m_Edit_Time_Passwod.SetFont(&m_Font);
	m_Edit_AIDI.SetFont(&m_Font);
	
	// ��ʼ����������������
	InitParamComboBox();
	// ��ʼ��ͨ������������
	InitChannelComboBox();
	// ��ʼ����������������
	InitListComboBox();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// ��ʱ���ص�����
void CParamConfig7::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if( SYSTEM_TIME_TIMER == nIDEvent )
	{
		CTime RealTime = CTime::GetCurrentTime();
		SetDlgItemText(IDC_EDIT_RTC, RealTime.Format( _T(" %Y-%m-%d  %H:%M:%S") ) );
	}

	CDialog::OnTimer(nIDEvent);
}
// ���ٸöԻ������ж�ʱ��
void CParamConfig7::StopAllTimer()
{
	EnterCriticalSection(&m_TimeLock);
	KillTimer( SYSTEM_TIME_TIMER );		// ����ϵͳʱ�䶨ʱ��

	LeaveCriticalSection(&m_TimeLock);

	DeleteCriticalSection(&m_TimeLock); // ɾ����ʱ���ٽ���
}
// �ؼ���ɫ����
HBRUSH CParamConfig7::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch( pWnd->GetDlgCtrlID() )
	{
		case IDC_EDIT_7_5:
			 pDC->SetTextColor( m_ResColor );
			 break;
		case IDC_EDIT_7_2:
			 pDC->SetTextColor( m_ResColor );
			 break;
		default:
			 break;
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


// ���� "OnBnClickedCheck_7_1 - 7_23" ����ͬ������ҳ��Ͳ�������ҳ�������ѡ��
// ����������ť
void CParamConfig7::OnBnClickedCheck_7_1()		
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO1_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO1_No ) );	// �����ð�ť�ؼ�ָ��
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
// �յ�������ť
void CParamConfig7::OnBnClickedCheck_7_2()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO2_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO2_No ) );	// �����ð�ť�ؼ�ָ��
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
// �����������ð�ť
void CParamConfig7::OnBnClickedCheck_7_3()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO3_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO3_No ) );	// �����ð�ť�ؼ�ָ��
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
// ����������ť
void CParamConfig7::OnBnClickedCheck_7_4()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO4_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO4_No ) );	// �����ð�ť�ؼ�ָ��
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
// �Ž�������ť
void CParamConfig7::OnBnClickedCheck_7_5()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO5_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO5_No ) );	// �����ð�ť�ؼ�ָ��
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
// ���������ť
void CParamConfig7::OnBnClickedCheck_7_6()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO6_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO6_No ) );	// �����ð�ť�ؼ�ָ��
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
// �澯������ť
void CParamConfig7::OnBnClickedCheck_7_7()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO7_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO7_No ) );	// �����ð�ť�ؼ�ָ��
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
// ͨ�ŷ�ʽ��ť
void CParamConfig7::OnBnClickedCheck_7_8()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO8_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg1->GetDlgItem( IDC_RADIO8_No ) );	// �����ð�ť�ؼ�ָ��
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
// ����������ť
void CParamConfig7::OnBnClickedCheck_7_9()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO9_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO9_No ) );	// �����ð�ť�ؼ�ָ��
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
// �������Ͱ�ť
void CParamConfig7::OnBnClickedCheck_7_10()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO10_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO10_No ) );		// �����ð�ť�ؼ�ָ��
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
// �澯������ť
void CParamConfig7::OnBnClickedCheck_7_11()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO11_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg2->GetDlgItem( IDC_RADIO11_No ) );		// �����ð�ť�ؼ�ָ��
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
// �������ð�ť
void CParamConfig7::OnBnClickedCheck_7_12()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO12_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO12_No ) );		// �����ð�ť�ؼ�ָ��
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
// ���ܼ�ذ�ť
void CParamConfig7::OnBnClickedCheck_7_13()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO13_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO13_No ) );		// �����ð�ť�ؼ�ָ��
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
// ����簴ť
void CParamConfig7::OnBnClickedCheck_7_14()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO14_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO14_No ) );		// �����ð�ť�ؼ�ָ��
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
// ���ڲ�����ť
void CParamConfig7::OnBnClickedCheck_7_15()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO15_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO15_No ) );		// �����ð�ť�ؼ�ָ��
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
// ����澯��ť
void CParamConfig7::OnBnClickedCheck_7_16()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO16_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO16_No ) );		// �����ð�ť�ؼ�ָ��
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
// �����ð�ť
void CParamConfig7::OnBnClickedCheck_7_17()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO17_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO17_No ) );		// �����ð�ť�ؼ�ָ��
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
// �忨ȡ�簴ť
void CParamConfig7::OnBnClickedCheck_7_18()
{
	CButton * pRadioButtonYes = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO18_Yes ) );	// ���ð�ť�ؼ�ָ�� 
	CButton * pRadioButtonNo = ( CButton* )( pSubDlg3->GetDlgItem( IDC_RADIO18_No ) );		// �����ð�ť�ؼ�ָ��
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
// ����ϵͳʱ�� �ݿ�
void CParamConfig7::OnBnClickedCheck_7_19()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
// ѡ��16ͨ��,��32ͨ������
void CParamConfig7::OnBnClickedCheck_7_20()
{
	CButton * pRadioButton16CH = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_16CH ) );	// 16ͨ�� 
	CButton * pRadioButton32CH = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_32CH ) );	// 32ͨ��
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
// ѡ��32ͨ��,��16ͨ������
void CParamConfig7::OnBnClickedCheck_7_21()
{
	CButton * pRadioButton16CH = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_16CH ) );	// 16ͨ��
	CButton * pRadioButton32CH = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_32CH ) );	// 32ͨ��
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
// ѡͨ�ð汾,��2M�汾����
void CParamConfig7::OnBnClickedCheck_7_22()
{
	CButton * pRadioButtonTY = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_CFG_1 ) );	// ͨ�� 
	CButton * pRadioButton2M = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_CFG_2 ) );	// 2M
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_26 ) )->GetCheck( ) )
	{
		pRadioButtonTY->SetCheck( TRUE );
		pRadioButton2M->SetCheck( FALSE );
		if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_27 ) )->GetCheck( ) )
		{
			( ( CButton* )GetDlgItem( IDC_CHECK_7_27 ) )->SetCheck( FALSE );
		}
	}
	else
	{
		pRadioButtonTY->SetCheck( FALSE );
	}
}
// ѡ2M�汾,��ͨ�ð汾����
void CParamConfig7::OnBnClickedCheck_7_23()
{
	CButton * pRadioButtonTY = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_CFG_1 ) );	// ͨ�� 
	CButton * pRadioButton2M = ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_CFG_2 ) );	// 2M
	if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_27 ) )->GetCheck( ) )
	{
		pRadioButton2M->SetCheck( TRUE );
		pRadioButtonTY->SetCheck( FALSE );
		if( TRUE == ( ( CButton* )GetDlgItem( IDC_CHECK_7_26 ) )->GetCheck( ) )
		{
			( ( CButton* )GetDlgItem( IDC_CHECK_7_26 ) )->SetCheck( FALSE );
		}
	}
	else
	{
		pRadioButton2M->SetCheck( FALSE );
	}
}

// ȫѡ��ť
void CParamConfig7::OnBnClickedRadio_7_1()
{
	for(int i = IDC_CHECK_7_1; i <= IDC_CHECK_7_19; i++) 
	{
		if( GetDlgItem( i ) ) // ��ֹ��ָ��
		{
			( ( CButton *)GetDlgItem( i ) )->SetCheck( TRUE );
		}
	}
	// ���ð�ťȫѡ
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
	// �����ð�ťȫ��ѡ
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

// ȫ��ѡ��ť
void CParamConfig7::OnBnClickedRadio_7_2()
{
	for(int i = IDC_CHECK_7_1; i <= IDC_CHECK_7_19; i++) 
	{
		if( GetDlgItem( i ) ) // ��ֹ��ָ��
		{
			( ( CButton *)GetDlgItem( i ) )->SetCheck( FALSE );
		}
	}
	// �����ð�ťȫѡ
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
	// ���ð�ťȫ��ѡ
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
		MessageBox("���ȴ򿪴��ڣ�", "��ʾ", MB_ICONWARNING);
		return;
	}
	if( FALSE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_22 ) ) )->GetCheck( ) && \
		FALSE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_23 ) ) )->GetCheck( ) )
	{
		AfxMessageBox("���ȹ�ѡ����ȡѡ�");
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
	// ��ȡϵͳʱ��
    if( TRUE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_22 ) ) )->GetCheck( ) )
    {
		CProtocolHandle ComProto;
		BYTE RecvBuffer[PACKET_SIZE] = {0};

		int length = ComProto.Package(0x07, NULL, 0);
		pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// ��������

		WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// �ȴ����ڽ������һ֡����
		if(pMainDlg->m_bRecvPacketTail == false)						// ����־λ ����3��û�յ���β
		{
			TRACE("Receive overtime!\n");
			ResultEdit->SetWindowText(" 1-NG !");
			pSubDlg7->m_ResColor = cRED;
			return FALSE;
		}
		int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
		RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));

		if(FALSE == ComProto.GetPureData(0x07, RecvBuffer, RecvBufLen))
		{
			ResultEdit->SetWindowText(" 1-NG !");
			pSubDlg7->m_ResColor = cRED;
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
	// ��ȡ��������
	if( TRUE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_23 ) ) )->GetCheck( ) )
    {
		CProtocolHandle ComProto;
		BYTE RecvBuffer[PACKET_SIZE] = {0};

		int length = ComProto.Package(0x1D, NULL, 0);
		pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// ��������
		
		WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// �ȴ����ڽ������һ֡����
		if(pMainDlg->m_bRecvPacketTail == false)						// ����־λ ����3��û�յ���β
		{
			TRACE("Receive overtime!\n");
			ResultEdit->SetWindowText(" 1-NG !");
			pSubDlg7->m_ResColor = cRED;
			return FALSE;
		}

		int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
		RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));

		if(FALSE == ComProto.GetPureData(0x1D, RecvBuffer, RecvBufLen))
		{
			ResultEdit->SetWindowText(" 2-NG !");
			pSubDlg7->m_ResColor = cRED;
			return FALSE;
		}
		CString SuperPassword;
		SuperPassword += hexToStrNoBlank(ComProto.PureData, 3);
		( ( CEdit* )( pSubDlg7->GetDlgItem( IDC_EDIT_7_4 ) ) )->SetWindowText(SuperPassword);
    }
	ResultEdit->SetWindowText("  OK !");
	pSubDlg7->m_ResColor = cGREEN;

	return TRUE;
}
void CParamConfig7::OnBnClickedButton_Test()
{
	if( !pMainDlg->m_bIsOpenSerl )
	{
		MessageBox("���ȴ򿪴��ڣ�", "��ʾ", MB_ICONWARNING);
		return;
	}
	if( FALSE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_20 ) ) )->GetCheck( ) && \
		FALSE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_21 ) ) )->GetCheck( ) )
	{
		AfxMessageBox("���ȹ�ѡ������ѡ�");
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
	// ����AIDI�ɼ�
    if( TRUE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_20 ) ) )->GetCheck( ) )
    {
		CProtocolHandle ComProto;
		BYTE RecvBuffer[PACKET_SIZE] = {0};
		BYTE SendData = 0x00;
		int length = ComProto.Package(0x55, &SendData, 1);
		pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// ��������

		WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// �ȴ����ڽ������һ֡����
		if(pMainDlg->m_bRecvPacketTail == false)						// ����־λ ����3��û�յ���β
		{
			TRACE("Receive overtime!\n");
			ResultEdit->SetWindowText(" 1-NG !");
			pSubDlg7->m_ResColor = cRED;
			return FALSE;
		}
		int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
		RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));

		if(FALSE == ComProto.GetPureData(0x55, RecvBuffer, RecvBufLen))
		{
			ResultEdit->SetWindowText(" 1-NG !");
			pSubDlg7->m_ResColor = cRED;
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
			pSubDlg7->m_ResColor = cRED;
			return FALSE;
		}
    }
	// ���Լ̵����͹���
	if( TRUE == ( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_21 ) ) )->GetCheck( ) )
    {
		CProtocolHandle ComProto;
		BYTE RecvBuffer[PACKET_SIZE] = {0};
		BYTE SendData = 0x01;
		int length = ComProto.Package(0x55, &SendData, 1);
		pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// ��������

		WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// �ȴ����ڽ������һ֡����
		if(pMainDlg->m_bRecvPacketTail == false)						// ����־λ ����3��û�յ���β
		{
			TRACE("Receive overtime!\n");
			ResultEdit->SetWindowText(" 2-NG !");
			pSubDlg7->m_ResColor = cRED;
			return FALSE;
		}
		int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
		RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));

		if(FALSE == ComProto.isVaildPacket(0x55, RecvBuffer, RecvBufLen))
		{
			ResultEdit->SetWindowText(" 2-NG !");
			pSubDlg7->m_ResColor = cRED;
			return FALSE;
		}
    }
	ResultEdit->SetWindowText("  OK !");
	pSubDlg7->m_ResColor = cGREEN;

	return TRUE;
}

// ��ʼ����������������
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

// ��ʼ��ͨ������������
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

// ��ʼ����������������
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

// �����ݿ�������ò���
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
	strsql += "Radio_7_3, Radio_7_4, Radio_7_5, Radio_7_6, Radio_7_7 ";
	strsql += "FROM paramconfig WHERE PZMC = '" + pzmc + "'";

	if(uMySQL.Select(strsql, data) == false)
	{
		uMySQL.Close();
		return false;
	}

	// ѡ���Ƿ�����
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

	uMySQL.Close();
	return true;
}
// �������õ�����ť
void CParamConfig7::OnBnClickedButtonParamExport()
{
	CString TempStr;
	m_ComboBox_Param.GetWindowText(TempStr);
	pSubDlg3->m_ComboBox_Param.SetWindowText(TempStr);
	pSubDlg3->OnBnClickedButtonExport();
}
// ͬ��������Ͽ�
void CParamConfig7::OnCbnSelchangeComboParam()
{
	CString TempStr;
	int nSel = m_ComboBox_Param.GetCurSel();    
    m_ComboBox_Param.GetLBText(nSel, TempStr);
	pSubDlg3->m_ComboBox_Param.SetWindowText(TempStr);
}

// ͨ�����õ�����ť
void CParamConfig7::OnBnClickedButtonChannelExport()
{
	CString TempStr;
	m_ComboBox_Channel.GetWindowText(TempStr);
	pSubDlg4->m_ComboBox_Channel.SetWindowText(TempStr);
	pSubDlg4->OnBnClickedButtonPathExport();
}
// ͬ��ͨ����Ͽ�
void CParamConfig7::OnCbnSelchangeComboChannel()
{
	CString TempStr;
	int nSel = m_ComboBox_Channel.GetCurSel();    
    m_ComboBox_Channel.GetLBText(nSel, TempStr);
	pSubDlg4->m_ComboBox_Channel.SetWindowText(TempStr);
}


// �������õ�����ť
void CParamConfig7::OnBnClickedButtonListExport()
{
	CString TempStr;
	m_ComboBox_List.GetWindowText(TempStr);
	pSubDlg4->m_ComboBox_List.SetWindowText(TempStr);
	pSubDlg4->OnBnClickedButtonListExport();
}
// ͬ��������Ͽ�
void CParamConfig7::OnCbnSelchangeComboList()
{
	CString TempStr;
	int nSel = m_ComboBox_List.GetCurSel();    
    m_ComboBox_List.GetLBText(nSel, TempStr);
	pSubDlg4->m_ComboBox_List.SetWindowText(TempStr);
}

// �������óɹ���������
void CParamConfig7::OnBnClickedButtonParamResetCnt()
{
	m_ParamSuccessCount = 0;
	SetDlgItemText(IDC_EDIT_7_6, ToString(m_ParamSuccessCount));
}
