#pragma once
#include "afxcmn.h"
#include "TinyFunc.h"
#include "afxwin.h"

// CParamConfig4 �Ի���
#define  IDC_EDIT_CREATEID		3000
#define	 IDC_COMBOX_CREATEID	3001

class CParamConfig4 : public CDialog
{
	DECLARE_DYNAMIC(CParamConfig4)

public:
	CParamConfig4(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CParamConfig4();

// �Ի�������
	enum { IDD = IDD_DIALOG_PARAM4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CListCtrl m_PathList;

	int e_Item;				// �ձ༭����  
	int e_SubItem;			// �ձ༭����  

	CEdit m_Edit;			// ���ɵ�Ԫ�༭�����
	bool m_isCreatEdit;		// ��־�༭���Ѿ�������
	void createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &isCreat);		// ������Ԫ��༭����
	void distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);							// ���ٵ�Ԫ��༭�����

	CComboBox m_comBox;			// ������Ԫ�������б����
	bool m_isCreatCombo;		// ��־�����б���Ѿ�������
	void createCcombobox(NM_LISTVIEW  *pEditCtrl, CComboBox *createccombo, int &Item, int &SubItem, bool &isCreat); // ������Ԫ�������б����
	void distroyCcombobox(CListCtrl *list, CComboBox* distroyccombo, int &Item, int &SubItem);						// ���ٵ�Ԫ�������б��

	afx_msg void OnKillfocusEdit();		//��̬���ɱ༭��ʧȥ������Ӧ����
	afx_msg void OnKillfocusCcomboBox();//��̬���������б��ʧȥ������Ӧ����

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedRadio16ch();
	afx_msg void OnBnClickedRadio32ch();
	afx_msg void OnBnClickedRadioTY();
	afx_msg void OnBnClickedRadio2M();
	afx_msg void OnBnClickedButtonPathAdd();
	afx_msg void OnBnClickedButtonPathExport();
	afx_msg void OnBnClickedButtonPathModify();
	afx_msg void OnBnClickedButtonPathDelete();
	afx_msg void OnBnClickedButtonResetCount();
	afx_msg void OnBnClickedButtonPathConfig();
	afx_msg void OnNMClickListPath(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	virtual void OnOK();
public:
	CComboBox m_ComboBox_Channel;
	CComboBox m_ComboBox_List;
};

