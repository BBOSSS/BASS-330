#pragma once
#include "afxwin.h"

// CParamConfig2 �Ի���

class CParamConfig2 : public CDialog
{
	DECLARE_DYNAMIC(CParamConfig2)

public:
	CParamConfig2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CParamConfig2();

// �Ի�������
	enum { IDD = IDD_DIALOG_PARAM2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// ��Ͽ�10 �̵�����������
	CComboBox m10_linkType1;
	CComboBox m10_linkType2;
	CComboBox m10_linkType3;
	CComboBox m10_linkType4;
	CComboBox m10_linkType5;
	CComboBox m10_linkType6;
	// ��Ͽ�11 ��������
	CComboBox m11_optocoupler1;
	CComboBox m11_optocoupler2;
	CComboBox m11_optocoupler3;
	CComboBox m11_optocoupler4;
	CComboBox m11_optocoupler5;
	CComboBox m11_optocoupler6;

	// �����ݿ�������ò���
	bool LoadParamConfig();

	afx_msg void OnBnClickedRadio9Yes();
	afx_msg void OnBnClickedRadio9No();
	afx_msg void OnBnClickedRadio10Yes();
	afx_msg void OnBnClickedRadio10No();
	afx_msg void OnBnClickedRadio11Yes();
	afx_msg void OnBnClickedRadio11No();
};
