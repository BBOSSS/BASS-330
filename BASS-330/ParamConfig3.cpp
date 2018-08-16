// ParamConfig3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig3.h"
#include "BASS-330Dlg.h"

// CParamConfig3 �Ի���

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


// CParamConfig3 ��Ϣ�������

void CParamConfig3::OnStnClickedStatic123()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

// �Ի����� ��ʼ��
BOOL CParamConfig3::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	/************* ��ʼ���Ӵ���ȫ��ָ��3 **************/
	pSubDlg3 = this;

	/***************** ��ʼ����Ͽ�12 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO12_No ) )->SetCheck( TRUE );	// ѡ������

	/***************** ��ʼ����Ͽ�13 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO13_No ) )->SetCheck( TRUE );	// ѡ������
	// �յ�
	m13_airCondition.AddString(_T("00 - ȱ"));
	m13_airCondition.AddString(_T("01 - RC3000"));
	m13_airCondition.AddString(_T("02 - Hair"));
	m13_airCondition.AddString(_T("03 - ����ʽ"));
	m13_airCondition.AddString(_T("04 - STUZ"));
	// ��Դ
	m13_power.AddString(_T("00 - ȱ"));
	m13_power.AddString(_T("01 - ZD"));
	m13_power.AddString(_T("02 - SX6800"));
	m13_power.AddString(_T("03 - PSM10A"));
	m13_power.AddString(_T("04 - DK04II"));
	m13_power.AddString(_T("05 - DLY"));
	m13_power.AddString(_T("06 - COMLI"));
	m13_power.AddString(_T("07 - ZD-CU01"));
	m13_power.AddString(_T("08 - ZXDU58S301"));
	// UPS
	m13_UPS.AddString(_T("00 - ȱ"));
	// �ͻ�
	m13_oilEngine.AddString(_T("00 - ȱ"));
	m13_oilEngine.AddString(_T("01 - DF1"));
	m13_oilEngine.AddString(_T("02 - DF2"));
	// ���
	m13_elecMeter.AddString(_T("00 - ȱ"));
	// 231����
	m13_231Count.AddString(_T("00"));
	m13_231Count.AddString(_T("01"));
	//�յ�����
	m13_airConditionCount.AddString(_T("00"));
	m13_airConditionCount.AddString(_T("01"));
	m13_airConditionCount.AddString(_T("02"));
	// ����
	m13_saveEnergy.AddString(_T("00 - ȱ"));

	/***************** ��ʼ����Ͽ�14 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO14_No ) )->SetCheck( TRUE );	// ѡ������

	for(int i = 0; i <= 16; i++)
	{
		CString num;
		if( i < 10 )
		{
			num += "0";
		}
		num += ToString( i );
		m13_cutout.AddString( num );	// �ϵ����
		m14_phaseLoss.AddString( num );	// ȱ�����
		m14_overVolt.AddString( num );	// ��ѹ���
		m14_underVolt.AddString( num );	// Ƿѹ���
	}

	// ���������
	m14_threePhaseType.AddString(_T("00 - ����"));
	m14_threePhaseType.AddString(_T("01 - ��Դ"));

	/***************** ��ʼ����Ͽ�15 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO15_No ) )->SetCheck( TRUE );	// ѡ������
	// COM1 - COM3 ת��
	m15_seriesTransmit.AddString(_T("00 - ��"));
	// ����1 ������
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
	// ����1 ����λ
	m15_series1Databit.AddString(_T("05"));
	m15_series1Databit.AddString(_T("06"));
	m15_series1Databit.AddString(_T("07"));
	// ����1 ֹͣλ
	m15_series1Stopbit.AddString(_T("01"));
	m15_series1Stopbit.AddString(_T("02"));
	// ����1 ����
	m15_series1Checkbit.AddString(_T("00 - ��У��"));
	m15_series1Checkbit.AddString(_T("01 - ��У��"));
	m15_series1Checkbit.AddString(_T("02 - żУ��"));
	m15_series1Checkbit.AddString(_T("03 - 1У��"));
	m15_series1Checkbit.AddString(_T("04 - 0У��"));
	// ����2 ������
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
	// ����2 ����λ
	m15_series2Databit.AddString(_T("05"));
	m15_series2Databit.AddString(_T("06"));
	m15_series2Databit.AddString(_T("07"));
	// ����2 ֹͣλ
	m15_series2Stopbit.AddString(_T("01"));
	m15_series2Stopbit.AddString(_T("02"));
	// ����2 ����
	m15_series2Checkbit.AddString(_T("00 - ��У��"));
	m15_series2Checkbit.AddString(_T("01 - ��У��"));
	m15_series2Checkbit.AddString(_T("02 - żУ��"));
	m15_series2Checkbit.AddString(_T("03 - 1У��"));
	m15_series2Checkbit.AddString(_T("04 - 0У��"));

	/***************** ��ʼ����Ͽ�16 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO16_No ) )->SetCheck( TRUE );	// ѡ������

	/***************** ��ʼ����Ͽ�17 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO17_No ) )->SetCheck( TRUE );	// ѡ������

	/***************** ��ʼ����Ͽ�18 ******************/
	( ( CButton *)GetDlgItem(IDC_RADIO18_No ) )->SetCheck( TRUE );	// ѡ������

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// ѡ���������ղ���
void CParamConfig3::OnBnClickedRadio12Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_12 ) ) )->SetCheck( TRUE );
}
// ���������ղ���
void CParamConfig3::OnBnClickedRadio12No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_12 ) ) )->SetCheck( FALSE );
}
// ѡ���������ܼ��
void CParamConfig3::OnBnClickedRadio13Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_13 ) ) )->SetCheck( TRUE );
}
// ���������ܼ��
void CParamConfig3::OnBnClickedRadio13No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_13 ) ) )->SetCheck( FALSE );
}
// ѡ�����������
void CParamConfig3::OnBnClickedRadio14Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_14 ) ) )->SetCheck( TRUE );
}
// �����������
void CParamConfig3::OnBnClickedRadio14No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_14 ) ) )->SetCheck( FALSE );
}
// ѡ�����ô��ڲ���
void CParamConfig3::OnBnClickedRadio15Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_15 ) ) )->SetCheck( TRUE );
}
// �����ô��ڲ���
void CParamConfig3::OnBnClickedRadio15No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_15 ) ) )->SetCheck( FALSE );
}
// ѡ����������澯ͨ��
void CParamConfig3::OnBnClickedRadio16Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_16 ) ) )->SetCheck( TRUE );
}
// ����������澯ͨ��
void CParamConfig3::OnBnClickedRadio16No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_16 ) ) )->SetCheck( FALSE );
}
// ѡ�������񶯲���
void CParamConfig3::OnBnClickedRadio17Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_17 ) ) )->SetCheck( TRUE );
}
// �������񶯲���
void CParamConfig3::OnBnClickedRadio17No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_17 ) ) )->SetCheck( FALSE );
}
// ѡ�����ò忨ȡ��
void CParamConfig3::OnBnClickedRadio18Yes()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_18 ) ) )->SetCheck( TRUE );
}
// �����ò忨ȡ��
void CParamConfig3::OnBnClickedRadio18No()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_18 ) ) )->SetCheck( FALSE );
}

// ��������ѡ�� ������ť
void CParamConfig3::OnBnClickedButtonAdd()
{
	if( /*IfExistsFile(ComboBox1->Text)*/ FALSE) // TODO: ʵ�ֺ���IfExistsFile
    {
		MessageBox("ָ���������ļ��Ѵ��ڣ���ֱ���޸ģ�", "��ʾ", MB_ICONWARNING);
        return;

    }
    if( /*AddFileToBase() == FALSE*/ TRUE)		 // TODO: ʵ�ֺ���AddFileToBase
    {
		MessageBox("���������ļ�����ʧ�ܣ�", "��ʾ", MB_ICONWARNING);
        return ;
    }
    /*InitialParamCfgCombox();*/				 // TODO: ʵ�ֺ���InitialParamCfgCombox
	MessageBox("���������ļ������ɹ���", "��ʾ", MB_ICONWARNING);
}
// ��������ѡ�� ������ť
void CParamConfig3::OnBnClickedButtonExport()
{
	MessageBox("TODO: ʵ�ֵ�����ť����", "��ʾ", MB_ICONWARNING);
	 /*InitialParamCfgCombox();*/				 // TODO: ʵ�ֺ���InitialParamCfgCombox
	 /*AnsiString strSql = *** */				 // TODO: ʵ��Sql���
												 // TODO: ����Sql���������ݿ����
												 // TODO: ���ò���
}
// ��������ѡ�� �޸İ�ť
void CParamConfig3::OnBnClickedButtonModify()
{
	if( /*!(IfExistsFile(ComboBox1->Text))*/ TRUE)
    {
		MessageBox("ָ���������ļ������ڣ���������", "��ʾ", MB_ICONWARNING);
        return;
    }
    /*InitialParamCfgCombox();*/
	if( IDCANCEL == MessageBox("ȷ���޸Ĳ�����", "�޸�ȷ��", MB_OKCANCEL | MB_ICONQUESTION) )
        return;
    if( /*DelParamFileFromBase(ComboBox1->Text) == false*/ FALSE)
    {
		MessageBox("�޸�ʧ�ܣ�", "��ʾ", MB_ICONWARNING);
        return ;
    }
    if( /*AddFileToBase() == false*/ TRUE)
    {
		MessageBox("�޸�ʧ�ܣ�", "��ʾ", MB_ICONWARNING);
        return ;
    }
	MessageBox("�޸ĳɹ���", "��ʾ", MB_ICONWARNING);
}
// ��������ѡ�� ɾ����ť
void CParamConfig3::OnBnClickedButtonDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(IDCANCEL == MessageBox("ȷ��ɾ����ѡ�Ĳ��������ļ���", "ɾ��ȷ��", MB_OKCANCEL | MB_ICONQUESTION))
        return;
    if( /*DelParamFileFromBase(ComboBox1->Text) == false*/ TRUE)
    {
        MessageBox("ɾ��ʧ�ܣ�", "��ʾ", MB_ICONWARNING);
        return ;
    }
    MessageBox("ɾ���ɹ���", "��ʾ", MB_ICONWARNING);
    /*InitialParamCfgCombox();*/
}
