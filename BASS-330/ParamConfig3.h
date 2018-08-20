#pragma once
#include "afxwin.h"
#include "TinyFunc.h"
#include "MySQLInterface.h"

// CParamConfig3 对话框

class CParamConfig3 : public CDialog
{
	DECLARE_DYNAMIC(CParamConfig3)

public:
	CParamConfig3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CParamConfig3();

// 对话框数据
	enum { IDD = IDD_DIALOG_PARAM3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStatic123();

	virtual BOOL OnInitDialog();
	// 组合框12 拍照设置
	CComboBox m12_photoCount;
	// 组合框13 智能监控设置
	CComboBox m13_airCondition;
	CComboBox m13_power;
	CComboBox m13_UPS;
	CComboBox m13_oilEngine;
	CComboBox m13_elecMeter;
	CComboBox m13_231Count;
	CComboBox m13_airConditionCount;
	CComboBox m13_saveEnergy;
	//组合框14 三相电设置
	CComboBox m13_cutout;
	CComboBox m14_phaseLoss;
	CComboBox m14_overVolt;
	CComboBox m14_underVolt;
	CComboBox m14_threePhaseType;
	// 组合框15 串口设置
	CComboBox m15_seriesTransmit;
	CComboBox m15_series1Baudrate;
	CComboBox m15_series1Databit;
	CComboBox m15_series1Stopbit;
	CComboBox m15_series1Checkbit;
	CComboBox m15_series2Baudrate;
	CComboBox m15_series2Databit;
	CComboBox m15_series2Stopbit;
	CComboBox m15_series2Checkbit;

	CComboBox m_ComboBox_Param;

	// 从数据库加载配置参数
	bool LoadParamConfig(std::string pzmc);
	// 保存配置参数到数据库
	bool SaveParamConfig();
	// 判断数据库是否有该参数配置
	bool IsExist(std::string target, std::string field, std::string table, MySQLInterface &uMySQL);

	afx_msg void OnBnClickedRadio12Yes();
	afx_msg void OnBnClickedRadio12No();
	afx_msg void OnBnClickedRadio13Yes();
	afx_msg void OnBnClickedRadio13No();
	afx_msg void OnBnClickedRadio14Yes();
	afx_msg void OnBnClickedRadio14No();
	afx_msg void OnBnClickedRadio15Yes();
	afx_msg void OnBnClickedRadio15No();
	afx_msg void OnBnClickedRadio16Yes();
	afx_msg void OnBnClickedRadio16No();
	afx_msg void OnBnClickedRadio17Yes();
	afx_msg void OnBnClickedRadio17No();
	afx_msg void OnBnClickedRadio18Yes();
	afx_msg void OnBnClickedRadio18No();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonExport();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonDelete();
	
};
