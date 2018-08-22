// ProcessBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ProcessBar.h"

// CProcessBar �Ի���

IMPLEMENT_DYNAMIC(CProcessBar, CDialog)

CProcessBar::CProcessBar(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessBar::IDD, pParent)
	, m_maxRange(100)
{

}

CProcessBar::~CProcessBar()
{
}

void CProcessBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_Bar);
}


BEGIN_MESSAGE_MAP(CProcessBar, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CProcessBar ��Ϣ�������

BOOL CProcessBar::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CenterWindow();					// ʹ�����ĶԻ��������������м�

	m_Bar.SetRange(0, m_maxRange);
    m_Bar.SetStep (1);
    m_Bar.SetPos  (0);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CProcessBar::OnCancel()
{
	m_Bar.SetPos  (0);
	CDialog::OnCancel();
}

void CProcessBar::UpdateBar(int step)
{
	m_Bar.SetPos(step);
	if(step == m_maxRange)  OnCancel();
}

void CProcessBar::OnClose()
{
	m_Bar.SetPos  (0);
	CDialog::OnClose();
}
