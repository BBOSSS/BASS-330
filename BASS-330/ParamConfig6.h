#pragma once
#include <vector>
// CParamConfig6 �Ի���

class CParamConfig6 : public CDialog
{
	DECLARE_DYNAMIC(CParamConfig6)

public:
	CParamConfig6(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CParamConfig6();

// �Ի�������
	enum { IDD = IDD_DIALOG_PARAM6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	int StdValues[32];
	int DeviValue;

	bool AiDiTest(std::vector<int> &AiDiValue);

	afx_msg void OnBnClickedRadioAllselect1();
	afx_msg void OnBnClickedRadioAllnoselect1();
	afx_msg void OnBnClickedRadioAllselect2();
	afx_msg void OnBnClickedRadioAllnoselect2();
	afx_msg void OnBnClickedButton_Set();
protected:
	virtual void OnOK();
};
