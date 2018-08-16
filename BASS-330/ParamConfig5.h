#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TinyFunc.h"

// CParamConfig5 对话框

class CParamConfig5 : public CDialog
{
	DECLARE_DYNAMIC(CParamConfig5)

public:
	CParamConfig5(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CParamConfig5();

// 对话框数据
	enum { IDD = IDD_DIALOG_PARAM5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m5_updateVersion;
	CListCtrl m5_GPRSList;
	afx_msg void OnBnClickedButtonBrowse();
	afx_msg void OnBnClickedButtonGetLocalIp();
};
