#pragma once
#include "afxcmn.h"
#include "TinyFunc.h"
#include "afxwin.h"

// CParamConfig4 对话框
#define  IDC_EDIT_CREATEID		3000
#define	 IDC_COMBOX_CREATEID	3001

class CParamConfig4 : public CDialog
{
	DECLARE_DYNAMIC(CParamConfig4)

public:
	CParamConfig4(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CParamConfig4();

// 对话框数据
	enum { IDD = IDD_DIALOG_PARAM4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CListCtrl m_PathList;

	int e_Item;				// 刚编辑的行  
	int e_SubItem;			// 刚编辑的列  

	CEdit m_Edit;			// 生成单元编辑框对象
	bool m_isCreatEdit;		// 标志编辑框已经被创建
	void createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &isCreat);		// 创建单元格编辑框函数
	void distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);							// 销毁单元格编辑框对象

	CComboBox m_comBox;			// 生产单元格下拉列表对象
	bool m_isCreatCombo;		// 标志下拉列表框已经被创建
	void createCcombobox(NM_LISTVIEW  *pEditCtrl, CComboBox *createccombo, int &Item, int &SubItem, bool &isCreat); // 创建单元格下拉列表框函数
	void distroyCcombobox(CListCtrl *list, CComboBox* distroyccombo, int &Item, int &SubItem);						// 销毁单元格下拉列表框

	afx_msg void OnKillfocusEdit();		//动态生成编辑框失去焦点响应函数
	afx_msg void OnKillfocusCcomboBox();//动态生成下拉列表框失去焦点响应函数

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

