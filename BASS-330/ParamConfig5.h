#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TinyFunc.h"

// CParamConfig5 �Ի���

class CParamConfig5 : public CDialog
{
	DECLARE_DYNAMIC(CParamConfig5)

public:
	CParamConfig5(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CParamConfig5();

// �Ի�������
	enum { IDD = IDD_DIALOG_PARAM5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m5_updateVersion;
	CListCtrl m5_GPRSList;
	afx_msg void OnBnClickedButtonBrowse();
	afx_msg void OnBnClickedButtonGetLocalIp();
};
