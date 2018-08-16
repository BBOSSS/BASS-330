// ParamConfig6.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig6.h"
#include "BASS-330Dlg.h"

// CParamConfig6 �Ի���

IMPLEMENT_DYNAMIC(CParamConfig6, CDialog)

CParamConfig6::CParamConfig6(CWnd* pParent /*=NULL*/)
	: CDialog(CParamConfig6::IDD, pParent)
	, DeviValue(0)
{

}

CParamConfig6::~CParamConfig6()
{
}

void CParamConfig6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CParamConfig6, CDialog)
	ON_BN_CLICKED(IDC_RADIO_ALLSELECT1, &CParamConfig6::OnBnClickedRadioAllselect1)
	ON_BN_CLICKED(IDC_RADIO_ALLNOSELECT1, &CParamConfig6::OnBnClickedRadioAllnoselect1)
	ON_BN_CLICKED(IDC_RADIO_ALLSELECT2, &CParamConfig6::OnBnClickedRadioAllselect2)
	ON_BN_CLICKED(IDC_RADIO_ALLNOSELECT2, &CParamConfig6::OnBnClickedRadioAllnoselect2)
	ON_BN_CLICKED(IDC_BUTTON3_1, &CParamConfig6::OnBnClickedButton_Set)
END_MESSAGE_MAP()


// CParamConfig6 ��Ϣ�������

BOOL CParamConfig6::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// ��ʼ���Ӵ���ȫ��ָ��6
	pSubDlg6 = this;

	// AI/DI 1
	( ( CButton *)GetDlgItem( IDC_RADIO_ALLSELECT1 ) )->SetCheck( TRUE );
	// ȫѡ
	for(int i = IDC_CHECK_AIDI1; i <= IDC_CHECK_AIDI16; i++) 
	{
		( ( CButton *)GetDlgItem( i ) )->SetCheck( TRUE );
	}
	// AI/DI 1
	( ( CButton *)GetDlgItem( IDC_RADIO_ALLSELECT2 ) )->SetCheck( TRUE );
	// ȫѡ
	for(int i = IDC_CHECK_AIDI17; i <= IDC_CHECK_AIDI32; i++) 
	{
		( ( CButton *)GetDlgItem( i ) )->SetCheck( TRUE );
	}

	( ( CEdit *)GetDlgItem( IDC_EDIT_DB1 ) )->SetWindowText( "4000" );
	( ( CEdit *)GetDlgItem( IDC_EDIT_DB2 ) )->SetWindowText( "4060" );
	( ( CEdit *)GetDlgItem( IDC_EDIT_DB3 ) )->SetWindowText( "4060" );
	( ( CEdit *)GetDlgItem( IDC_EDIT_DB4 ) )->SetWindowText( "4060" );
	( ( CEdit *)GetDlgItem( IDC_EDIT_DB5 ) )->SetWindowText( "4060" );
	( ( CEdit *)GetDlgItem( IDC_EDIT_DB6 ) )->SetWindowText( "2100" );
	( ( CEdit *)GetDlgItem( IDC_EDIT_DB7 ) )->SetWindowText( "4060" );
	( ( CEdit *)GetDlgItem( IDC_EDIT_DB8 ) )->SetWindowText( "4060" );
	( ( CEdit *)GetDlgItem( IDC_EDIT_DB9 ) )->SetWindowText( "4060" );
	( ( CEdit *)GetDlgItem( IDC_EDIT_DB10 ))->SetWindowText( "4060" );
	( ( CEdit *)GetDlgItem( IDC_EDIT_DB11 ))->SetWindowText( "0" );
	( ( CEdit *)GetDlgItem( IDC_EDIT_DB12 ))->SetWindowText( "4060" );
	( ( CEdit *)GetDlgItem( IDC_EDIT_DB13 ))->SetWindowText( "4060" );
	( ( CEdit *)GetDlgItem( IDC_EDIT_DB14 ))->SetWindowText( "0" );
	( ( CEdit *)GetDlgItem( IDC_EDIT_DB15 ))->SetWindowText( "0" );
	( ( CEdit *)GetDlgItem( IDC_EDIT_DB16 ))->SetWindowText( "4060" );
	for(int i = IDC_EDIT_DB17; i <= IDC_EDIT_DB32; i++) 
	{
		( ( CEdit *)GetDlgItem( i ) )->SetWindowText( "0" );
	}
	( ( CEdit *)GetDlgItem( IDC_EDIT3_1 ) )->SetWindowText( "4000" );

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// AIDI1 ȫѡ
void CParamConfig6::OnBnClickedRadioAllselect1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(int i = IDC_CHECK_AIDI1; i <= IDC_CHECK_AIDI16; i++) 
	{
		( ( CButton *)GetDlgItem( i ) )->SetCheck( TRUE );
	}
}

// AIDI1 ȫ��ѡ
void CParamConfig6::OnBnClickedRadioAllnoselect1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(int i = IDC_CHECK_AIDI1; i <= IDC_CHECK_AIDI16; i++) 
	{
		( ( CButton *)GetDlgItem( i ) )->SetCheck( FALSE );
	}
}

// AIDI2 ȫѡ
void CParamConfig6::OnBnClickedRadioAllselect2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(int i = IDC_CHECK_AIDI17; i <= IDC_CHECK_AIDI32; i++) 
	{
		( ( CButton *)GetDlgItem( i ) )->SetCheck( TRUE );
	}
}

// AIDI2 ȫ��ѡ
void CParamConfig6::OnBnClickedRadioAllnoselect2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for(int i = IDC_CHECK_AIDI17; i <= IDC_CHECK_AIDI32; i++) 
	{
		( ( CButton *)GetDlgItem( i ) )->SetCheck( FALSE );
	}
}

// ���Բɼ�ֵ��Ա�ֵ�Ƿ���ȷ
bool CParamConfig6::AiDiTest(std::vector<int> &AiDiValue)
{
	bool ret = true;
	for(int i = 0, IDC = IDC_CHECK_AIDI1; i < 32 && IDC <= IDC_CHECK_AIDI32; i++, IDC++) 
	{
		CButton* pCheck = ( CButton *)GetDlgItem( IDC );	// �鿴Resource.h
		CEdit* pCJEdit = ( CEdit *)GetDlgItem( IDC + 32 );	// �ؼ�ID��ƫ��Ϊ32
		CEdit* pDBEdit = ( CEdit *)GetDlgItem( IDC + 64 );	// �ؼ�ID��ƫ��Ϊ64
		CEdit* pRESEdit= ( CEdit *)GetDlgItem( IDC + 96 );	// �ؼ�ID��ƫ��Ϊ96
		if(pCheck->GetCheck() == FALSE)
		{
			pCJEdit->SetWindowText("");
			pRESEdit->SetWindowText("--");
			continue;
		}
		CString CJValue = ToString( AiDiValue[i] );
		pCJEdit->SetWindowText( CJValue );
		if( abs(AiDiValue[i]-StdValues[i]) > DeviValue )
		{
			pRESEdit->SetWindowText("��ͨ��");
			ret = false;
		}
		else
			pRESEdit->SetWindowText("  O K ");
	}
	return ret;
}
void CParamConfig6::OnBnClickedButton_Set()
{
	CString EditValue;
	for(int i = 0, IDC = IDC_EDIT_DB1; IDC <= IDC_EDIT_DB32; IDC++) 
	{
		( ( CEdit *)GetDlgItem( IDC ) )->GetWindowText( EditValue );
		if(EditValue.IsEmpty())
		{
			AfxMessageBox("�Ա�ֵ����Ϊ��, �����������ֵ��");
			return;
		}
		StdValues[i++] = ToInt(EditValue);
	}
	( ( CEdit *)GetDlgItem( IDC_EDIT3_1 ) )->GetWindowText( EditValue );
	if(EditValue.IsEmpty())
	{
		AfxMessageBox("ƫ��ֵ����Ϊ��, �����������ֵ��");
		return;
	}
	DeviValue = ToInt(EditValue);
	MessageBox("����ƫ��ֵ�ͶԱ�ֵ�ɹ���", "��ʾ", MB_ICONINFORMATION);
}

void CParamConfig6::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	// CDialog::OnOK();
}
