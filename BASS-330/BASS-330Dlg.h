
// BASS-330Dlg.h : ͷ�ļ�
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

#define RECV_SIZE		10*1024			// ���ջ�������С

// CBASS330Dlg �Ի���
class CBASS330Dlg : public CDialog
{
// ����
public:
	CBASS330Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BASS330_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;				// ��ǩҳ�ؼ�

	CParamConfig1 m_param1;		// ����1��ǩҳ�ӶԻ���
	CParamConfig2 m_param2;		// ����2��ǩҳ�ӶԻ���
	CParamConfig3 m_param3;		// ����3��ǩҳ�ӶԻ���
	CParamConfig4 m_param4;		// ͨ�����������ñ�ǩҳ�ӶԻ���
	CParamConfig5 m_param5;		// GPRSͨ�ű�ǩҳ�ӶԻ���
	CParamConfig6 m_param6;		// �ɼ��������Ϣ��ǩҳ�ӶԻ���
	CParamConfig7 m_param7;		// ����ҳ���ǩҳ�ӶԻ���

	CRect m_AllRect;			// ������ + ���ڵ�������
	CRect m_MainRect;			// ������

	RingBuffer m_RecvBuf;			// ���ڽ��ջ�����
	HANDLE	m_hSemaphore;			// �������ݰ�ͬ���ź���
	int m_bRecvPacketTail;

	CSerialPort m_CSerl;			// CSerialPort��
	BOOL m_bIsOpenSerl;				// ���ڴ򿪱�ʶ
	CComboBox m_comboSeries;		// ���ں������ؼ�
	CEdit m_EdSerlRecv;				// ���ڽ��մ���Ctr
	CEdit m_EdSerlSend;				// ���ڷ��ʹ���Ctr

	INT32 FInitSerial();			// ��ʼ������
	INT32 FSerialOpen();			// �򿪴���
	INT32 FSerialClose();			// �رմ���
	
	VOID FSerialSend(UINT8 *pSendData, UINT16 usLen);	// ���ڷ��ͺ���
	afx_msg LONG FSerialRecv(WPARAM ch, LPARAM port);	// ���ڽ��պ���

	CWinThread *m_pDeviceInitThread;	// �豸��ʼ���߳�
	static UINT DeviceInitThread(LPVOID pParam);

	CWinThread *m_pClearRecordThread;	// ����Ž���¼�߳�
	static UINT ClearRecordThread(LPVOID pParam);

	CWinThread *m_pClearListThread;		// ����ڰ������߳�
	static UINT ClearListThread(LPVOID pParam);

	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);	// �л���ǩҳʱ������
	afx_msg void OnStnClickedStaticDebug();								// ���ڵ��Դ��ڵ�����
	afx_msg void OnClose();								// �رճ���ʱ�ͷ���Դ
	afx_msg void OnBnClickedCancel();					// �رճ���ʱ�ͷ���Դ
	
	afx_msg void OnBnClickedButtonOpenOrClose();		// ���ڴ򿪻�رհ�ť
	afx_msg void OnBnClickedButtonClear();				// ��ս��տ�
	afx_msg void OnBnClickedButtonTx();					// ȷ�Ϸ���
	afx_msg void OnBnClickedButtonInit();				// �豸��ʼ����ť
	afx_msg void OnBnClickedButtonClearRecord();
	afx_msg void OnBnClickedButtonClearlist();
	afx_msg void OnBnClickedButtonClearList2M();
};
