#pragma once
#include "afxcmn.h"


// CProcessBar �Ի���

class CProcessBar : public CDialog
{
	DECLARE_DYNAMIC(CProcessBar)

public:
	CProcessBar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProcessBar();

// �Ի�������
	enum { IDD = IDD_DIALOG_BAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
