#pragma once
#include "afxwin.h"
#include "TinyFunc.h"

// CParamConfig1 对话框

class CParamConfig1 : public CDialog
{
	DECLARE_DYNAMIC(CParamConfig1)

public:
	CParamConfig1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CParamConfig1();

// 对话框数据
	enum { IDD = IDD_DIALOG_PARAM1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 重写对话框初始化函数
	virtual BOOL OnInitDialog();

	// 重写滚动条函数
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	// 1.机器参数组合框成员变量
	CComboBox m1_trumpet;
	CComboBox m1_screen;
	CComboBox m1_keyboard;
	CComboBox m1_client;
	// 2.空调设置组合框成员变量
	CComboBox m2_ctrReference;
	CComboBox m2_roomTemp;
	CComboBox m2_windWarm1;
	CComboBox m2_windWarm2;
	CComboBox m2_ctrMode;
	// 4.开锁参数组合框成员变量
	CComboBox m4_lockType;
	CComboBox m4_lockCount;
	CComboBox m4_cardReaderCount;
	CComboBox m4_slotCard1;
	CComboBox m4_slotCard2;
	CComboBox m4_switchReport;
	// 5.门禁参数组合框成员变量
	CComboBox m5_guardType;
	CComboBox m5_listWorkMode;
	CComboBox m5_preventWay;
	CComboBox m5_blockMode;
	CComboBox m5_leave;
	CComboBox m5_cardID;
	CComboBox m5_cardType;
	// 6.风机参数组合框成员变量
	CComboBox m6_saveEnergy;
	CComboBox m6_airConditionCount;
	CComboBox m6_airConditionType;
	CComboBox m6_startEveryOtherDay;
	CComboBox m6_powerType;
	CComboBox m6_outputChannel;
	CComboBox m6_dataReport;
	CComboBox m6_fanType;
	// 7.告警参数组合框成员变量
	CComboBox m7_alarmSound;
	CComboBox m7_isReport;
	CComboBox m7_alarmType;
	CComboBox m7_alarmComfirm;
	CComboBox m7_saveReport;
	// 8.通信方式组合框成员变量
	CComboBox m8_linkChain;
	CComboBox m8_activeDial;
	CComboBox m8_boundSIM;

	// 从数据库加载配置参数
	bool LoadParamConfig(std::string pzmc);

	afx_msg void OnBnClickedRadio1Yes();
	afx_msg void OnBnClickedRadio1No();
	afx_msg void OnBnClickedRadio2Yes();
	afx_msg void OnBnClickedRadio2No();
	afx_msg void OnBnClickedRadio3Yes();
	afx_msg void OnBnClickedRadio3No();
	afx_msg void OnBnClickedRadio4Yes();
	afx_msg void OnBnClickedRadio4No();
	afx_msg void OnBnClickedRadio5Yes();
	afx_msg void OnBnClickedRadio5No();
	afx_msg void OnBnClickedRadio6Yes();
	afx_msg void OnBnClickedRadio6No();
	afx_msg void OnBnClickedRadio7Yes();
	afx_msg void OnBnClickedRadio7No();
	afx_msg void OnBnClickedRadio8Yes();
	afx_msg void OnBnClickedRadio8No();
};
