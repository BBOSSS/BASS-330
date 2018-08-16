
// BASS-330Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "ParamConfig1.h"
#include "ParamConfig2.h"
#include "ParamConfig3.h"
#include "ParamConfig4.h"
#include "ParamConfig5.h"
#include "ParamConfig6.h"
#include "ParamConfig7.h"

#include "Resource.h"

#include "RingBuffer.h"
#include "SerialPort.h"

#include "GlobalVariables.h"

//#include "IniFile.h"

#define RECV_SIZE		10*1024			// 接收缓冲区大小

// CBASS330Dlg 对话框
class CBASS330Dlg : public CDialog
{
// 构造
public:
	CBASS330Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BASS330_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;				// 标签页控件

	CParamConfig1 m_param1;		// 参数1标签页子对话框
	CParamConfig2 m_param2;		// 参数2标签页子对话框
	CParamConfig3 m_param3;		// 参数3标签页子对话框
	CParamConfig4 m_param4;		// 通道与名单配置标签页子对话框
	CParamConfig5 m_param5;		// GPRS通信标签页子对话框
	CParamConfig6 m_param6;		// 采集与输出信息标签页子对话框
	CParamConfig7 m_param7;		// 操作页面标签页子对话框

	CRect m_AllRect;			// 主区域 + 串口调试区域
	CRect m_MainRect;			// 主区域

	RingBuffer m_RecvBuf;			// 串口接收缓冲区
	HANDLE	m_hSemaphore;			// 串口数据包同步信号量
	int m_bRecvPacketTail;

	CSerialPort m_CSerl;			// CSerialPort类
	BOOL m_bIsOpenSerl;				// 串口打开标识
	CComboBox m_comboSeries;		// 串口号下拉控件
	CEdit m_EdSerlRecv;				// 串口接收窗口Ctr
	CEdit m_EdSerlSend;				// 串口发送窗口Ctr

	INT32 FInitSerial();			// 初始化串口
	INT32 FSerialOpen();			// 打开串口
	INT32 FSerialClose();			// 关闭串口
	
	VOID FSerialSend(UINT8 *pSendData, UINT16 usLen);	// 串口发送函数
	afx_msg LONG FSerialRecv(WPARAM ch, LPARAM port);	// 串口接收函数

	CWinThread *m_pDeviceInitThread;	// 设备初始化线程
	static UINT DeviceInitThread(LPVOID pParam);

	CWinThread *m_pClearRecordThread;	// 清除门禁记录线程
	static UINT ClearRecordThread(LPVOID pParam);

	CWinThread *m_pClearListThread;		// 清除黑白名单线程
	static UINT ClearListThread(LPVOID pParam);

	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);	// 切换标签页时处理函数
	afx_msg void OnStnClickedStaticDebug();								// 串口调试窗口的收缩
	afx_msg void OnClose();								// 关闭程序时释放资源
	afx_msg void OnBnClickedCancel();					// 关闭程序时释放资源
	
	afx_msg void OnBnClickedButtonOpenOrClose();		// 串口打开或关闭按钮
	afx_msg void OnBnClickedButtonClear();				// 清空接收框
	afx_msg void OnBnClickedButtonTx();					// 确认发送
	afx_msg void OnBnClickedButtonInit();				// 设备初始化按钮
	afx_msg void OnBnClickedButtonClearRecord();
	afx_msg void OnBnClickedButtonClearlist();
	afx_msg void OnBnClickedButtonClearList2M();
};
