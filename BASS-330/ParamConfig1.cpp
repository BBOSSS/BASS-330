// ParamConfig1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig1.h"
#include "BASS-330Dlg.h"


// CParamConfig1 �Ի���

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


// CParamConfig1 ��Ϣ�������

BOOL CParamConfig1::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	/************ ��ʼ���Ӵ���ȫ��ָ��1 **************/
	pSubDlg1 = this;

	/***************** ��ʼ�������� *******************/
	SCROLLINFO scrollinfo;
    GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);    
    scrollinfo.nPage = 50;    //���û����С
    scrollinfo.nMax = 100;     //���ù����������λ��0--75
    SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);

	/***************** ��ʼ����Ͽ�1 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO1_No ) )->SetCheck( TRUE );	// ѡ������
	// ����
    m1_trumpet.AddString(_T("00 - ��"));     
    m1_trumpet.AddString(_T("01 - ��"));
	// ����
    m1_screen.AddString(_T("00 - ��ֹ"));  
    m1_screen.AddString(_T("01 - ʹ��"));
	// ������ 
    m1_keyboard.AddString(_T("00 - ��"));   
    m1_keyboard.AddString(_T("01 - ��"));
	// �û���
    m1_client.AddString(_T("00 - ͨ��"));   
    m1_client.AddString(_T("01 - ����"));
	m1_client.AddString(_T("02 - ��ݸ"));     
    m1_client.AddString(_T("03 - ����"));
	m1_client.AddString(_T("04 - ÷��"));     
    m1_client.AddString(_T("05 - ����"));
	m1_client.AddString(_T("06 - ����"));     
    m1_client.AddString(_T("07 - ����VCOM"));
	m1_client.AddString(_T("08 - INCOM"));     
    m1_client.AddString(_T("09 - ����"));

	/***************** ��ʼ����Ͽ�2 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO2_No ) )->SetCheck( TRUE );	// ѡ������
	// ���Ʋο�
	m2_ctrReference.AddString(_T("00 - ����"));
	m2_ctrReference.AddString(_T("01 - ����"));
	m2_ctrReference.AddString(_T("02 - ����"));
	m2_ctrReference.AddString(_T("03 - �Ͽ�"));
	
	for(int i = 0; i <= 32; i++)
	{
		CString num;
		if( i < 10 )
		{
			num += "0";
		}
		num += ToString( i );
		m2_roomTemp.AddString( num );	// ����ͨ��
		m2_windWarm1.AddString( num );	// #1 ����ͨ��
		m2_windWarm2.AddString( num );	// #2 ����ͨ��
	}
	
	// ����ģʽ
	m2_ctrMode.AddString(_T("00"));
	m2_ctrMode.AddString(_T("01"));
	m2_ctrMode.AddString(_T("02"));

	/***************** ��ʼ����Ͽ�3 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO3_No ) )->SetCheck( TRUE );	// ѡ������

	/***************** ��ʼ����Ͽ�4 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO4_No ) )->SetCheck( TRUE );	// ѡ������
	// ������
	m4_lockType.AddString(_T("00 - ����"));
	m4_lockType.AddString(_T("01 - ����"));
	// ��������
	m4_lockCount.AddString(_T("00"));
	m4_lockCount.AddString(_T("01"));
	m4_lockCount.AddString(_T("02"));
	// ����ͷ����
	m4_cardReaderCount.AddString(_T("00"));
	m4_cardReaderCount.AddString(_T("01"));
	m4_cardReaderCount.AddString(_T("02"));
	m4_cardReaderCount.AddString(_T("03"));
	m4_cardReaderCount.AddString(_T("04"));
	// ����1��Ӧˢ��
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
	// ����2��Ӧˢ��
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
	// �Ž������Ƿ��ϱ�
	m4_switchReport.AddString(_T("00 - ��"));
	m4_switchReport.AddString(_T("01 - ��"));

	/***************** ��ʼ����Ͽ�5 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO5_No ) )->SetCheck( TRUE );	// ѡ������
	// �Ž�����
	m5_guardType.AddString(_T("00 - ����"));
	m5_guardType.AddString(_T("01 - ˢ��"));
	m5_guardType.AddString(_T("02 - ����"));
	// ����������ʽ
	m5_listWorkMode.AddString(_T("00 - ��"));
	m5_listWorkMode.AddString(_T("01 - ��"));
	// Ԥ����ʽ
	m5_preventWay.AddString(_T("00 - ����"));
	m5_preventWay.AddString(_T("01 - ��ť"));
	// ����ģʽ
	m5_blockMode.AddString(_T("00 - ����"));
	// �뿪
	m5_leave.AddString(_T("00 - ����ˢ��"));
	// ����
	m5_cardID.AddString(_T("01 - ����"));
	// ��������
	m5_cardType.AddString(_T("00 - MF"));

	/***************** ��ʼ����Ͽ�6 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO6_No ) )->SetCheck( TRUE );	// ѡ������
	// ��������
	m6_saveEnergy.AddString(_T("00 - ��"));
	m6_saveEnergy.AddString(_T("01 - ��"));
	// �յ�����
	m6_airConditionCount.AddString(_T("00"));
	m6_airConditionCount.AddString(_T("01"));
	m6_airConditionCount.AddString(_T("02"));
	// �յ�����
	m6_airConditionType.AddString(_T("00 - ����"));
	m6_airConditionType.AddString(_T("01 - ����"));
	// ���տ���
	m6_startEveryOtherDay.AddString(_T("00 - �ر�"));
	m6_startEveryOtherDay.AddString(_T("01 - ����"));
	m6_startEveryOtherDay.AddString(_T("02 - ����"));
	// �����Դ
	m6_powerType.AddString(_T("00 - ֱ��"));
	m6_powerType.AddString(_T("01 - ����"));
	// ���ͨ��
	m6_outputChannel.AddString(_T("00 - ����"));
	m6_outputChannel.AddString(_T("01 - ����"));
	// ��������
	m6_dataReport.AddString(_T("00 - ��"));
	m6_dataReport.AddString(_T("01 - ��"));
	// �������
	m6_fanType.AddString(_T("00 - ͨ��"));
	m6_fanType.AddString(_T("01 - ����"));

	/***************** ��ʼ����Ͽ�7 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO7_No ) )->SetCheck( TRUE );	// ѡ������
	// �澯��
	m7_alarmSound.AddString(_T("00 - �ر�"));
	m7_alarmSound.AddString(_T("01 - ����"));
	// �Ƿ�����
	m7_isReport.AddString(_T("00 - ��"));
	m7_isReport.AddString(_T("01 - ��"));
	m7_isReport.AddString(_T("00 - �Ž�"));
	m7_isReport.AddString(_T("01 - ����"));
	// �澯����
	m7_alarmType.AddString(_T("00 - ����"));
	m7_alarmType.AddString(_T("01 - ����"));
	// �澯ȷ��
	m7_alarmComfirm.AddString(_T("00 - ��"));
	m7_alarmComfirm.AddString(_T("01 - ��"));
	// �����Ƿ񱣴�
	m7_saveReport.AddString(_T("00 - ��"));
	m7_saveReport.AddString(_T("01 - ��"));

	/***************** ��ʼ����Ͽ�8 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO8_No ) )->SetCheck( TRUE );	// ѡ������
	// ��·
	m8_linkChain.AddString(_T("00 - GSM-SMS"));
	m8_linkChain.AddString(_T("01 - RS232"));
	m8_linkChain.AddString(_T("00 - MODEM"));
	m8_linkChain.AddString(_T("01 - GPRS"));
	// ��������
	m8_activeDial.AddString(_T("00 - ��"));
	m8_activeDial.AddString(_T("01 - ��"));
	// SIM���Ƿ��
	m8_boundSIM.AddString(_T("00 - ��"));
	m8_boundSIM.AddString(_T("01 - ��"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CParamConfig1::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
         scrollinfo.nPos += 1;	 // �˴�һ��Ҫע����ϻ���ĳ��ȣ������ж�
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
         scrollinfo.nPos += 5;  // �˴�һ��Ҫע����ϻ���ĳ��ȣ������ж�
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
// ѡ�����û�������
void CParamConfig1::OnBnClickedRadio1Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_1 ) ) )->SetCheck( TRUE );
}
// �����û�������
void CParamConfig1::OnBnClickedRadio1No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_1 ) ) )->SetCheck( FALSE );
}
// ѡ�����ÿյ�����
void CParamConfig1::OnBnClickedRadio2Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_2 ) ) )->SetCheck( TRUE );
}
// �����ÿյ�����
void CParamConfig1::OnBnClickedRadio2No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_2 ) ) )->SetCheck( FALSE );
}
// ѡ�����ó�������
void CParamConfig1::OnBnClickedRadio3Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_3 ) ) )->SetCheck( TRUE );
}
// �����ó�������
void CParamConfig1::OnBnClickedRadio3No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_3 ) ) )->SetCheck( FALSE );
}
// ѡ�����ÿ�������
void CParamConfig1::OnBnClickedRadio4Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_4 ) ) )->SetCheck( TRUE );
}
// �����ÿ�������
void CParamConfig1::OnBnClickedRadio4No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_4 ) ) )->SetCheck( FALSE );
}
// ѡ�������Ž�����
void CParamConfig1::OnBnClickedRadio5Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_5 ) ) )->SetCheck( TRUE );
}
// �������Ž�����
void CParamConfig1::OnBnClickedRadio5No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_5 ) ) )->SetCheck( FALSE );
}
// ѡ�����÷������
void CParamConfig1::OnBnClickedRadio6Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_6 ) ) )->SetCheck( TRUE );
}
// �����÷������
void CParamConfig1::OnBnClickedRadio6No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_6 ) ) )->SetCheck( FALSE );
}
// ѡ�����ø澯����
void CParamConfig1::OnBnClickedRadio7Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_7 ) ) )->SetCheck( TRUE );
}
// �����ø澯����
void CParamConfig1::OnBnClickedRadio7No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_7 ) ) )->SetCheck( FALSE );
}
// ѡ������ͨ�ŷ�ʽ
void CParamConfig1::OnBnClickedRadio8Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_8 ) ) )->SetCheck( TRUE );
}
// ������ͨ�ŷ�ʽ
void CParamConfig1::OnBnClickedRadio8No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_8 ) ) )->SetCheck( FALSE );
}
