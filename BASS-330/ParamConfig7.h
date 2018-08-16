#pragma once

#include "GlobalVariables.h"
#include "TinyFunc.h"
#include "afxwin.h"

#define		SYSTEM_TIME_TIMER	 10

#define		cBLACK		RGB(0,    0,   0)
#define		cRED		RGB(255,  0,   0)
#define		cGREEN		RGB(0,  128,   0)
#define		cBULE		RGB(0,    0, 255)

// CParamConfig7 �Ի���

class CParamConfig7 : public CDialog
{
	DECLARE_DYNAMIC(CParamConfig7)

public:
	CParamConfig7(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CParamConfig7();

// �Ի�������
	enum { IDD = IDD_DIALOG_PARAM7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();

	CFont m_Font;
	CEdit m_Edit_Time_Passwod;
	CEdit m_Edit_AIDI;

	CRITICAL_SECTION  m_TimeLock;	// ��ʱ����
	void StopAllTimer();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	COLORREF m_ResColor;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CWinThread *m_pGetSystimeAndPasswordThread;	// ��ȡϵͳʱ��ͳ��������߳�
	static UINT GetSystimeAndPasswordThread(LPVOID pParam);

	CWinThread *m_pTestDoThread;				// AIDI�ɼ�,����ͼ̵��������߳�
	static UINT TestDoThread(LPVOID pParam);

	afx_msg void OnBnClickedCheck_7_1( );
	afx_msg void OnBnClickedCheck_7_2( );
	afx_msg void OnBnClickedCheck_7_3( );
	afx_msg void OnBnClickedCheck_7_4( );
	afx_msg void OnBnClickedCheck_7_5( );
	afx_msg void OnBnClickedCheck_7_6( );
	afx_msg void OnBnClickedCheck_7_7( );
	afx_msg void OnBnClickedCheck_7_8( );
	afx_msg void OnBnClickedCheck_7_9( );
	afx_msg void OnBnClickedCheck_7_10();
	afx_msg void OnBnClickedCheck_7_11();
	afx_msg void OnBnClickedCheck_7_12();
	afx_msg void OnBnClickedCheck_7_13();
	afx_msg void OnBnClickedCheck_7_14();
	afx_msg void OnBnClickedCheck_7_15();
	afx_msg void OnBnClickedCheck_7_16();
	afx_msg void OnBnClickedCheck_7_17();
	afx_msg void OnBnClickedCheck_7_18();
	afx_msg void OnBnClickedCheck_7_19();
	afx_msg void OnBnClickedCheck_7_20();
	afx_msg void OnBnClickedCheck_7_21();
	afx_msg void OnBnClickedCheck_7_22();
	afx_msg void OnBnClickedCheck_7_23();

	afx_msg void OnBnClickedRadio_7_1();	// ȫѡ
	afx_msg void OnBnClickedRadio_7_2();	// ȫ��ѡ

	afx_msg void OnBnClickedButton_Get_Systime_And_SuperPassword();	
	afx_msg void OnBnClickedButton_Test();
};