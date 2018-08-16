// ParamConfig4.cpp : 实现文件
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig4.h"
#include "BASS-330Dlg.h"

// CParamConfig4 对话框

IMPLEMENT_DYNAMIC(CParamConfig4, CDialog)

CParamConfig4::CParamConfig4(CWnd* pParent /*=NULL*/)
	: CDialog(CParamConfig4::IDD, pParent),
	  m_isCreatEdit(false),
	  m_isCreatCombo(false)
{
}

CParamConfig4::~CParamConfig4()
{
}

void CParamConfig4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_AIDI, m_PathList);
}


BEGIN_MESSAGE_MAP(CParamConfig4, CDialog)
	ON_BN_CLICKED(IDC_RADIO_16CH, &CParamConfig4::OnBnClickedRadio16ch)
	ON_BN_CLICKED(IDC_RADIO_32CH, &CParamConfig4::OnBnClickedRadio32ch)
	ON_BN_CLICKED(IDC_RADIO_CFG_1, &CParamConfig4::OnBnClickedRadioTY)
	ON_BN_CLICKED(IDC_RADIO_CFG_2, &CParamConfig4::OnBnClickedRadio2M)
	ON_BN_CLICKED(IDC_BUTTON_PATH_1, &CParamConfig4::OnBnClickedButtonPathAdd)
	ON_BN_CLICKED(IDC_BUTTON_PATH_2, &CParamConfig4::OnBnClickedButtonPathExport)
	ON_BN_CLICKED(IDC_BUTTON_PATH_3, &CParamConfig4::OnBnClickedButtonPathModify)
	ON_BN_CLICKED(IDC_BUTTON_PATH_4, &CParamConfig4::OnBnClickedButtonPathDelete)
	ON_BN_CLICKED(IDC_BUTTON_PATH_5, &CParamConfig4::OnBnClickedButtonResetCount)
	ON_BN_CLICKED(IDC_BUTTON_PATH_6, &CParamConfig4::OnBnClickedButtonPathConfig)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PATH, &CParamConfig4::OnNMClickListPath)
	ON_EN_KILLFOCUS(IDC_EDIT_CREATEID, &CParamConfig4::OnKillfocusEdit)
	ON_CBN_KILLFOCUS(IDC_COMBOX_CREATEID, &CParamConfig4::OnKillfocusCcomboBox)
END_MESSAGE_MAP()


// CParamConfig4 消息处理程序

BOOL CParamConfig4::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 初始化子窗口全局指针4
	pSubDlg4 = this;

	// 选择16通道
	( ( CButton *)GetDlgItem(IDC_RADIO_16CH ) )->SetCheck( TRUE );	
	// 选择通用版本
	( ( CButton *)GetDlgItem(IDC_RADIO_CFG_1) )->SetCheck( TRUE );	
	// 初始化AIDI列表控件   
    // 获取编程语言列表视图控件的位置和大小  
	CRect rect;
    m_PathList.GetClientRect(&rect);   
    // 为列表视图控件添加全行选中和栅格风格   
    m_PathList.SetExtendedStyle(m_PathList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
    // 为列表视图控件添加8列   
    m_PathList.InsertColumn(0, _T("通道"),		LVCFMT_CENTER, rect.Width()  /10, 0);   
    m_PathList.InsertColumn(1, _T("类型"),		LVCFMT_CENTER, rect.Width()*2/10, 1);   
    m_PathList.InsertColumn(2, _T("上限"),		LVCFMT_CENTER, rect.Width()  /10, 2);   
	m_PathList.InsertColumn(3, _T("下限"),		LVCFMT_CENTER, rect.Width()  /10, 3);
	m_PathList.InsertColumn(4, _T("复位"),		LVCFMT_CENTER, rect.Width()  /10, 4);
	m_PathList.InsertColumn(5, _T("调校"),		LVCFMT_CENTER, rect.Width()  /10, 5);
	m_PathList.InsertColumn(6, _T("上限输出"), LVCFMT_CENTER, rect.Width()*3/20, 6);
	m_PathList.InsertColumn(7, _T("下限输出"), LVCFMT_CENTER, rect.Width()*3/20, 7);
	// 添加32行
	for(int i = 0; i < 32; i++)
	{
		CString temp;
		if(i < 9) temp += "0";
		temp += ToString( i+1 );
		m_PathList.InsertItem( i, temp );
		m_PathList.SetItemText(i, 1, "00-无测点");
		for(int j = 2; j < 8; j++)
			m_PathList.SetItemText(i, j, "0");
	}
	m_PathList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 列表控件事件处理函数
void CParamConfig4::OnNMClickListPath(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	TRACE( "row = %d,  col = %d\n", pEditCtrl->iItem, pEditCtrl->iSubItem); 

    if (pEditCtrl->iItem == -1)		//点击到非工作区
    {
        if (m_isCreatEdit == true)//如果之前创建了编辑框就销毁掉
        {
            distroyEdit(&m_PathList, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
            m_isCreatEdit = false;
        }
        if (m_isCreatCombo == true)//如果之前创建了下拉列表框就销毁掉
        {
            distroyCcombobox(&m_PathList, &m_comBox, e_Item, e_SubItem);
            m_isCreatCombo = false;
        }
    }
    else if (pEditCtrl->iSubItem != 1 && pEditCtrl->iSubItem != 6 && pEditCtrl->iSubItem != 0)
    {
        if (m_isCreatCombo == true)
        {
            distroyCcombobox(&m_PathList, &m_comBox, e_Item, e_SubItem);
            m_isCreatCombo = false;
        }
        if (m_isCreatEdit == true)
        {
            if (!(e_Item == pEditCtrl->iItem && e_SubItem == pEditCtrl->iSubItem))//如果点中的单元格不是之前创建好的
            {
                distroyEdit(&m_PathList, &m_Edit, e_Item, e_SubItem);
                m_isCreatEdit = false;
                createEdit(pEditCtrl, &m_Edit, e_Item, e_SubItem, m_isCreatEdit);//创建编辑框
            }
            else//点中的单元格是之前创建好的
            {
                m_Edit.SetFocus();//设置为焦点 
            }
        }
        else
        {
            e_Item = pEditCtrl->iItem;
            e_SubItem = pEditCtrl->iSubItem;
            createEdit(pEditCtrl, &m_Edit, e_Item, e_SubItem, m_isCreatEdit);
        }
    }
    else if (pEditCtrl->iSubItem == 1 || pEditCtrl->iSubItem == 6)	// 下拉表
    {
        if (m_isCreatEdit == true)	// 如果之前创建了编辑框就销毁掉
        {
            distroyEdit(&m_PathList, &m_Edit, e_Item, e_SubItem);
            m_isCreatEdit = false;
        }
        if (m_isCreatCombo == true)
        {
            if (!(e_Item == pEditCtrl->iItem && e_SubItem == pEditCtrl->iSubItem))//如果点中的单元格不是之前创建好的
            {
                distroyCcombobox(&m_PathList, &m_comBox, e_Item, e_SubItem);
                m_isCreatCombo = false;
                createCcombobox(pEditCtrl, &m_comBox, e_Item, e_SubItem, m_isCreatCombo);
				if(pEditCtrl->iSubItem == 1)
				{
					m_comBox.AddString("00-未测");
					m_comBox.AddString("01-三相");
					m_comBox.AddString("02-交流");
					m_comBox.AddString("03-直流");
					m_comBox.AddString("04-温度");
					m_comBox.AddString("05-湿度");
					m_comBox.AddString("06-电流");
					m_comBox.AddString("07-模拟");
					m_comBox.AddString("08-火情");
					m_comBox.AddString("09-烟雾");
					m_comBox.AddString("10-盗情");
					m_comBox.AddString("11-水浸");
					m_comBox.AddString("12-门禁");
					m_comBox.AddString("13-油机");
					m_comBox.AddString("14-空调");
					m_comBox.AddString("15-红外");
					m_comBox.AddString("16-整流");
					m_comBox.AddString("17-数字");
					m_comBox.AddString("18-防盗");
					m_comBox.AddString("19-其他");
					m_comBox.AddString("20-机器");
					m_comBox.AddString("21-断电");
					m_comBox.AddString("22-振动");
					m_comBox.AddString("23-风门");
					m_comBox.AddString("24-进风");
					m_comBox.AddString("25-出风");
					m_comBox.AddString("26-屏蔽");
					m_comBox.AddString("27-电缆");
					m_comBox.AddString("28-锁开");
					m_comBox.AddString("29-锁关");
					m_comBox.AddString("30-微波");
					m_comBox.AddString("31-隔离");
					m_comBox.AddString("32-锁舌");
					m_comBox.AddString("33-地线");
					m_comBox.AddString("34-馈线");
					m_comBox.AddString("35-漫反射");
				}
                if(pEditCtrl->iSubItem == 6)
				{
					for(int i = 0; i <= 16; i++)
					{
						CString temp;
						if(i < 10) temp += "0";
						temp += ToString(i);
						m_comBox.AddString(temp);
					}
				}
                m_comBox.ShowDropDown();//自动下拉
            }
            else//点中的单元格是之前创建好的
            {
                m_comBox.SetFocus();//设置为焦点 
            }
        }
        else
        {
            e_Item = pEditCtrl->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
            e_SubItem = pEditCtrl->iSubItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
            createCcombobox(pEditCtrl, &m_comBox, e_Item, e_SubItem, m_isCreatCombo);//创建编辑框
            if(pEditCtrl->iSubItem == 1)
				{
					m_comBox.AddString("00-未测");
					m_comBox.AddString("01-三相");
					m_comBox.AddString("02-交流");
					m_comBox.AddString("03-直流");
					m_comBox.AddString("04-温度");
					m_comBox.AddString("05-湿度");
					m_comBox.AddString("06-电流");
					m_comBox.AddString("07-模拟");
					m_comBox.AddString("08-火情");
					m_comBox.AddString("09-烟雾");
					m_comBox.AddString("10-盗情");
					m_comBox.AddString("11-水浸");
					m_comBox.AddString("12-门禁");
					m_comBox.AddString("13-油机");
					m_comBox.AddString("14-空调");
					m_comBox.AddString("15-红外");
					m_comBox.AddString("16-整流");
					m_comBox.AddString("17-数字");
					m_comBox.AddString("18-防盗");
					m_comBox.AddString("19-其他");
					m_comBox.AddString("20-机器");
					m_comBox.AddString("21-断电");
					m_comBox.AddString("22-振动");
					m_comBox.AddString("23-风门");
					m_comBox.AddString("24-进风");
					m_comBox.AddString("25-出风");
					m_comBox.AddString("26-屏蔽");
					m_comBox.AddString("27-电缆");
					m_comBox.AddString("28-锁开");
					m_comBox.AddString("29-锁关");
					m_comBox.AddString("30-微波");
					m_comBox.AddString("31-隔离");
					m_comBox.AddString("32-锁舌");
					m_comBox.AddString("33-地线");
					m_comBox.AddString("34-馈线");
					m_comBox.AddString("35-漫反射");
				}
                if(pEditCtrl->iSubItem == 6)
				{
					for(int i = 0; i <= 16; i++)
					{
						CString temp;
						if(i < 10) temp += "0";
						temp += ToString(i);
						m_comBox.AddString(temp);
					}
				}
                m_comBox.ShowDropDown();//自动下拉
        }
    }
	*pResult = 0;
}

void CParamConfig4::createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &isCreat)   
{
    Item = pEditCtrl->iItem;
    SubItem = pEditCtrl->iSubItem;
	isCreat = true;

    createdit->Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN, CRect(0, 0, 0, 0), this, IDC_EDIT_CREATEID);
    createdit->SetFont(this->GetFont(), FALSE);
    createdit->SetParent(&m_PathList); // list control设置为父窗口,生成的Edit才能正确定位

    CRect  EditRect;
    m_PathList.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect);	// 获取单元格的空间位置信息
    EditRect.SetRect(EditRect.left+1, EditRect.top+1, EditRect.left + m_PathList.GetColumnWidth(e_SubItem)-1, EditRect.bottom-1);
    CString strItem = m_PathList.GetItemText(e_Item, e_SubItem);		// 获得相应单元格字符
    createdit->SetWindowText(strItem);	// 将单元格字符显示在编辑框上
    createdit->MoveWindow(&EditRect);	// 将编辑框位置放在相应单元格上
    createdit->ShowWindow(SW_SHOW);		// 显示编辑框在单元格上面
    createdit->SetFocus();				// 设置为焦点 
    createdit->SetSel(-1);				// 设置光标在文本框文字的最后
}

void CParamConfig4::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
    CString meditdata;
    distroyedit->GetWindowText(meditdata);
    list->SetItemText(Item, SubItem, meditdata);	// 获得相应单元格字符
    distroyedit->DestroyWindow();					// 销毁对象
}

void CParamConfig4::createCcombobox(NM_LISTVIEW  *pEditCtrl, CComboBox *createccombo, int &Item, int &SubItem, bool &isCreat) 
{
    Item = pEditCtrl->iItem;
    SubItem = pEditCtrl->iSubItem;
    isCreat = true;

    createccombo->Create(WS_CHILD | WS_VISIBLE |  CBS_DROPDOWN | CBS_OEMCONVERT, CRect(0, 0, 0, 0), this, IDC_COMBOX_CREATEID);
    createccombo->SetFont(this->GetFont(), FALSE);
    createccombo->SetParent(&m_PathList); // list control设置为父窗口,生成的Ccombobox才能正确定位

    CRect  EditRect;
    m_PathList.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect); // 获取单元格的空间位置信息
    EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_PathList.GetColumnWidth(e_SubItem) - 1, EditRect.bottom - 1);

    CString strItem = m_PathList.GetItemText(e_Item, e_SubItem);		// 获得相应单元格字符
    createccombo->SetWindowText(strItem);					
    createccombo->MoveWindow(&EditRect);				
    createccombo->ShowWindow(SW_SHOW);								
}

void CParamConfig4::distroyCcombobox(CListCtrl *list, CComboBox* distroyccombo, int &Item, int &SubItem)
{
    CString meditdata;
    distroyccombo->GetWindowText(meditdata);
    list->SetItemText(Item, SubItem, meditdata);	// 更新相应单元格字符
    distroyccombo->DestroyWindow();					// 销毁对象
}

void CParamConfig4::OnKillfocusEdit()
{
    if (m_isCreatEdit == true)//如果之前创建了编辑框就销毁掉
    {
        distroyEdit(&m_PathList, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
        m_isCreatEdit = false;
    }
    if (m_isCreatCombo == true)//如果之前创建了下拉列表框就销毁掉
    {
        distroyCcombobox(&m_PathList, &m_comBox, e_Item, e_SubItem);
        m_isCreatCombo = false;
    }
}

void CParamConfig4::OnKillfocusCcomboBox()
{
    if (m_isCreatEdit == true)//如果之前创建了编辑框就销毁掉
    {
        distroyEdit(&m_PathList, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
        m_isCreatEdit = false;
    }
    if (m_isCreatCombo == true)//如果之前创建了下拉列表框就销毁掉
    {
        distroyCcombobox(&m_PathList, &m_comBox, e_Item, e_SubItem);
        m_isCreatCombo = false;
    }
}
// 按Enter键
void CParamConfig4::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	OnKillfocusEdit();
	OnKillfocusCcomboBox();
	// CDialog::OnOK();
}

// 选择配置16通道
void CParamConfig4::OnBnClickedRadio16ch()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_24 ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_25 ) ) )->SetCheck( FALSE );
}
// 选择配置32通道
void CParamConfig4::OnBnClickedRadio32ch()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_25 ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_24 ) ) )->SetCheck( FALSE );
}
// 选择配置通用版本
void CParamConfig4::OnBnClickedRadioTY()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_26 ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_27 ) ) )->SetCheck( FALSE );
}
// 选择配置2M版本
void CParamConfig4::OnBnClickedRadio2M()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_27 ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_26 ) ) )->SetCheck( FALSE );
}

// 通道配置选择 新增按钮
void CParamConfig4::OnBnClickedButtonPathAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	if( /*IfExistsPathConfig(ComboBox2->Text)*/ FALSE) // TODO: 实现函数IfExistsPathConfig
    {
		MessageBox("指定的通道配置文件已存在，请直接修改！", "提示", MB_ICONWARNING);
        return;

    }
    if( /*AddPathConfigToBase() == FALSE*/ TRUE)		 // TODO: 实现函数AddPathConfigToBase
    {
		MessageBox("通道配置文件新增失败！", "提示", MB_ICONWARNING);
        return ;
    }
    /*InitialPathCfgCombox();*/				 // TODO: 实现函数InitialPathCfgCombox
	MessageBox("通道配置文件新增成功！", "提示", MB_ICONWARNING);
}
// 通道配置选择 导出按钮
void CParamConfig4::OnBnClickedButtonPathExport()
{
	MessageBox("TODO: 实现导出按钮功能", "提示", MB_ICONWARNING);
	/*InitialPathCfgCombox();*/	
	/*AnsiString strSql = *** */				 // TODO: 实现Sql语句
												 // TODO: 根据Sql语句进行数据库操作
												 // TODO: 配置参数
}
// 通道配置选择 修改按钮
void CParamConfig4::OnBnClickedButtonPathModify()
{
	if( /*!(IfExistsPathConfig(ComboBox1->Text))*/ TRUE)
    {
		MessageBox("指定的配置文件不存在，请新增！", "提示", MB_ICONWARNING);
        return;
    }
    /*InitialPathCfgCombox();*/
	if( IDCANCEL == MessageBox("确定修改通道参数吗？", "修改确认", MB_OKCANCEL | MB_ICONQUESTION) )
        return;
    if( /*DelPathConfigFromBase(ComboBox1->Text) == false*/ FALSE)
    {
		MessageBox("修改失败！", "提示", MB_ICONWARNING);
        return ;
    }
    if( /*AddPathConfigToBase() == false*/ TRUE)
    {
		MessageBox("修改失败！", "提示", MB_ICONWARNING);
        return ;
    }
	MessageBox("修改成功！", "提示", MB_ICONWARNING);
}
// 通道配置选择 删除按钮
void CParamConfig4::OnBnClickedButtonPathDelete()
{
	if(IDCANCEL == MessageBox("确定删除所选的通道配置文件？", "删除确认", MB_OKCANCEL | MB_ICONQUESTION))
        return;
    if( /*DelPathConfigFromBase(ComboBox1->Text) == false*/ TRUE)
    {
        MessageBox("删除失败！", "提示", MB_ICONWARNING);
        return ;
    }
    MessageBox("删除成功！", "提示", MB_ICONWARNING);
    /*InitialPathCfgCombox();*/
}
// 通道配置 成功次数清零按钮
void CParamConfig4::OnBnClickedButtonResetCount()
{
	/*PathCount = 0*/ //设置全局变量次数为0
	( ( CEdit* )( GetDlgItem( IDC_EDIT_PATH_1 ) ) )->SetWindowText( "0" );
}
// 通道配置按钮
void CParamConfig4::OnBnClickedButtonPathConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	if( !pMainDlg->m_bIsOpenSerl )
	{
		MessageBox("请先打开串口！", "提示", MB_ICONWARNING);
		return;
	}
	if( m_PathList.GetItemText(3, 1) == "" )
	{
		MessageBox("请导出通道配置文件！", "提示", MB_ICONWARNING);
		return;
	}
	if( /*是否已连接数据库*/ TRUE )
	{
		if( /*!(IfExistsPathConfig(ComboBox1->Text))*/ FALSE)
		{
			MessageBox("指定的通道配置文件不存在！", "提示", MB_ICONWARNING);
			return;
		}
	}
	if(IDCANCEL == MessageBox("加载新的通道信息，原有的通道信息将清除，确认吗？", "提示", MB_OKCANCEL | MB_ICONQUESTION))
        return;

	/*通道配置处理*/
	( ( CButton* )( GetDlgItem( IDC_BUTTON_PATH_6 ) ) )->EnableWindow( FALSE );
	/*StartPathConfig()*/ //开一个线程开始通道配置
}



