// ParamConfig6.cpp : 实现文件
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig6.h"
#include "BASS-330Dlg.h"
#include "IniFile.h"
#include <vector>

// CParamConfig6 对话框

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


// CParamConfig6 消息处理程序

BOOL CParamConfig6::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 初始化子窗口全局指针6
	pSubDlg6 = this;

	// ini配置文件
	CIniFile iniFile;
	std::vector<CIniFile::Record> records;
	records = iniFile.GetSection("AiDiCfg", "BASS330.ini");
	if( !records.empty() )
	{
		CString temp(records[0].Value.c_str());
		( ( CEdit *)GetDlgItem( IDC_EDIT3_1 ) )->SetWindowText( temp );
		DeviValue = ToInt( temp );

		for(int i = 32, j = 0, IDC = IDC_EDIT_DB1; i > 0; i--, j++, IDC++)
		{
			CString temp(records[i].Value.c_str());
			( ( CEdit *)GetDlgItem( IDC ) )->SetWindowText( temp );
			StdValues[j] = ToInt( temp );
		}
	}

	// AI/DI 1
	( ( CButton *)GetDlgItem( IDC_RADIO_ALLSELECT1 ) )->SetCheck( TRUE );
	// 全选
	for(int i = IDC_CHECK_AIDI1; i <= IDC_CHECK_AIDI16; i++) 
	{
		( ( CButton *)GetDlgItem( i ) )->SetCheck( TRUE );
	}
	// AI/DI 1
	( ( CButton *)GetDlgItem( IDC_RADIO_ALLSELECT2 ) )->SetCheck( TRUE );
	// 全选
	for(int i = IDC_CHECK_AIDI17; i <= IDC_CHECK_AIDI32; i++) 
	{
		( ( CButton *)GetDlgItem( i ) )->SetCheck( TRUE );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// AIDI1 全选
void CParamConfig6::OnBnClickedRadioAllselect1()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i = IDC_CHECK_AIDI1; i <= IDC_CHECK_AIDI16; i++) 
	{
		( ( CButton *)GetDlgItem( i ) )->SetCheck( TRUE );
	}
}

// AIDI1 全不选
void CParamConfig6::OnBnClickedRadioAllnoselect1()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i = IDC_CHECK_AIDI1; i <= IDC_CHECK_AIDI16; i++) 
	{
		( ( CButton *)GetDlgItem( i ) )->SetCheck( FALSE );
	}
}

// AIDI2 全选
void CParamConfig6::OnBnClickedRadioAllselect2()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i = IDC_CHECK_AIDI17; i <= IDC_CHECK_AIDI32; i++) 
	{
		( ( CButton *)GetDlgItem( i ) )->SetCheck( TRUE );
	}
}

// AIDI2 全不选
void CParamConfig6::OnBnClickedRadioAllnoselect2()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i = IDC_CHECK_AIDI17; i <= IDC_CHECK_AIDI32; i++) 
	{
		( ( CButton *)GetDlgItem( i ) )->SetCheck( FALSE );
	}
}

// 测试采集值与对比值是否正确
bool CParamConfig6::AiDiTest(std::vector<int> &AiDiValue)
{
	bool ret = true;
	for(int i = 0, IDC = IDC_CHECK_AIDI1; i < 32 && IDC <= IDC_CHECK_AIDI32; i++, IDC++) 
	{
		CButton* pCheck = ( CButton *)GetDlgItem( IDC );	// 查看Resource.h
		CEdit* pCJEdit = ( CEdit *)GetDlgItem( IDC + 32 );	// 控件ID的偏移为32
		CEdit* pDBEdit = ( CEdit *)GetDlgItem( IDC + 64 );	// 控件ID的偏移为64
		CEdit* pRESEdit= ( CEdit *)GetDlgItem( IDC + 96 );	// 控件ID的偏移为96
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
			pRESEdit->SetWindowText("不通过");
			ret = false;
		}
		else
			pRESEdit->SetWindowText("  O K ");
	}
	return ret;
}
void CParamConfig6::OnBnClickedButton_Set()
{
	CIniFile iniFile;
	if( !iniFile.SectionExists("AiDiCfg", "BASS330.ini") )
	{
		iniFile.AddSection("AiDiCfg", "BASS330.ini");
	}
	CString EditValue;
	for(int i = 0, IDC = IDC_EDIT_DB1; IDC <= IDC_EDIT_DB32; i++, IDC++) 
	{
		( ( CEdit *)GetDlgItem( IDC ) )->GetWindowText( EditValue );
		if(EditValue.IsEmpty())
		{
			AfxMessageBox("对比值不能为空, 请输入具体数值。");
			return;
		}
		StdValues[i] = ToInt(EditValue);
		iniFile.SetValue("AiDi"+itos(i+1), itos(StdValues[i]), "AiDiCfg", "BASS330.ini");
	}
	( ( CEdit *)GetDlgItem( IDC_EDIT3_1 ) )->GetWindowText( EditValue );
	if(EditValue.IsEmpty())
	{
		AfxMessageBox("偏差值不能为空, 请输入具体数值。");
		return;
	}
	DeviValue = ToInt(EditValue);
	iniFile.SetValue("Tolerance", itos(DeviValue), "AiDiCfg", "BASS330.ini");
	MessageBox("设置偏差值和对比值成功！", "提示", MB_ICONINFORMATION);
}

void CParamConfig6::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	// CDialog::OnOK();
}
