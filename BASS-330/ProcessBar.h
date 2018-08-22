#pragma once
#include "afxcmn.h"


// CProcessBar 对话框

class CProcessBar : public CDialog
{
	DECLARE_DYNAMIC(CProcessBar)

public:
	CProcessBar(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProcessBar();

// 对话框数据
	enum { IDD = IDD_DIALOG_BAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CProgressCtrl m_Bar;
	int m_maxRange;
	void UpdateBar(int step);
protected:
	virtual void OnCancel();
public:
	afx_msg void OnClose();
};
