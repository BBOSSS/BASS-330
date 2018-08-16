// ParamConfig4.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig4.h"
#include "BASS-330Dlg.h"

// CParamConfig4 �Ի���

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


// CParamConfig4 ��Ϣ�������

BOOL CParamConfig4::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// ��ʼ���Ӵ���ȫ��ָ��4
	pSubDlg4 = this;

	// ѡ��16ͨ��
	( ( CButton *)GetDlgItem(IDC_RADIO_16CH ) )->SetCheck( TRUE );	
	// ѡ��ͨ�ð汾
	( ( CButton *)GetDlgItem(IDC_RADIO_CFG_1) )->SetCheck( TRUE );	
	// ��ʼ��AIDI�б�ؼ�   
    // ��ȡ��������б���ͼ�ؼ���λ�úʹ�С  
	CRect rect;
    m_PathList.GetClientRect(&rect);   
    // Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
    m_PathList.SetExtendedStyle(m_PathList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
    // Ϊ�б���ͼ�ؼ����8��   
    m_PathList.InsertColumn(0, _T("ͨ��"),		LVCFMT_CENTER, rect.Width()  /10, 0);   
    m_PathList.InsertColumn(1, _T("����"),		LVCFMT_CENTER, rect.Width()*2/10, 1);   
    m_PathList.InsertColumn(2, _T("����"),		LVCFMT_CENTER, rect.Width()  /10, 2);   
	m_PathList.InsertColumn(3, _T("����"),		LVCFMT_CENTER, rect.Width()  /10, 3);
	m_PathList.InsertColumn(4, _T("��λ"),		LVCFMT_CENTER, rect.Width()  /10, 4);
	m_PathList.InsertColumn(5, _T("��У"),		LVCFMT_CENTER, rect.Width()  /10, 5);
	m_PathList.InsertColumn(6, _T("�������"), LVCFMT_CENTER, rect.Width()*3/20, 6);
	m_PathList.InsertColumn(7, _T("�������"), LVCFMT_CENTER, rect.Width()*3/20, 7);
	// ���32��
	for(int i = 0; i < 32; i++)
	{
		CString temp;
		if(i < 9) temp += "0";
		temp += ToString( i+1 );
		m_PathList.InsertItem( i, temp );
		m_PathList.SetItemText(i, 1, "00-�޲��");
		for(int j = 2; j < 8; j++)
			m_PathList.SetItemText(i, j, "0");
	}
	m_PathList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

// �б�ؼ��¼�������
void CParamConfig4::OnNMClickListPath(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	TRACE( "row = %d,  col = %d\n", pEditCtrl->iItem, pEditCtrl->iSubItem); 

    if (pEditCtrl->iItem == -1)		//������ǹ�����
    {
        if (m_isCreatEdit == true)//���֮ǰ�����˱༭������ٵ�
        {
            distroyEdit(&m_PathList, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
            m_isCreatEdit = false;
        }
        if (m_isCreatCombo == true)//���֮ǰ�����������б������ٵ�
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
            if (!(e_Item == pEditCtrl->iItem && e_SubItem == pEditCtrl->iSubItem))//������еĵ�Ԫ����֮ǰ�����õ�
            {
                distroyEdit(&m_PathList, &m_Edit, e_Item, e_SubItem);
                m_isCreatEdit = false;
                createEdit(pEditCtrl, &m_Edit, e_Item, e_SubItem, m_isCreatEdit);//�����༭��
            }
            else//���еĵ�Ԫ����֮ǰ�����õ�
            {
                m_Edit.SetFocus();//����Ϊ���� 
            }
        }
        else
        {
            e_Item = pEditCtrl->iItem;
            e_SubItem = pEditCtrl->iSubItem;
            createEdit(pEditCtrl, &m_Edit, e_Item, e_SubItem, m_isCreatEdit);
        }
    }
    else if (pEditCtrl->iSubItem == 1 || pEditCtrl->iSubItem == 6)	// ������
    {
        if (m_isCreatEdit == true)	// ���֮ǰ�����˱༭������ٵ�
        {
            distroyEdit(&m_PathList, &m_Edit, e_Item, e_SubItem);
            m_isCreatEdit = false;
        }
        if (m_isCreatCombo == true)
        {
            if (!(e_Item == pEditCtrl->iItem && e_SubItem == pEditCtrl->iSubItem))//������еĵ�Ԫ����֮ǰ�����õ�
            {
                distroyCcombobox(&m_PathList, &m_comBox, e_Item, e_SubItem);
                m_isCreatCombo = false;
                createCcombobox(pEditCtrl, &m_comBox, e_Item, e_SubItem, m_isCreatCombo);
				if(pEditCtrl->iSubItem == 1)
				{
					m_comBox.AddString("00-δ��");
					m_comBox.AddString("01-����");
					m_comBox.AddString("02-����");
					m_comBox.AddString("03-ֱ��");
					m_comBox.AddString("04-�¶�");
					m_comBox.AddString("05-ʪ��");
					m_comBox.AddString("06-����");
					m_comBox.AddString("07-ģ��");
					m_comBox.AddString("08-����");
					m_comBox.AddString("09-����");
					m_comBox.AddString("10-����");
					m_comBox.AddString("11-ˮ��");
					m_comBox.AddString("12-�Ž�");
					m_comBox.AddString("13-�ͻ�");
					m_comBox.AddString("14-�յ�");
					m_comBox.AddString("15-����");
					m_comBox.AddString("16-����");
					m_comBox.AddString("17-����");
					m_comBox.AddString("18-����");
					m_comBox.AddString("19-����");
					m_comBox.AddString("20-����");
					m_comBox.AddString("21-�ϵ�");
					m_comBox.AddString("22-��");
					m_comBox.AddString("23-����");
					m_comBox.AddString("24-����");
					m_comBox.AddString("25-����");
					m_comBox.AddString("26-����");
					m_comBox.AddString("27-����");
					m_comBox.AddString("28-����");
					m_comBox.AddString("29-����");
					m_comBox.AddString("30-΢��");
					m_comBox.AddString("31-����");
					m_comBox.AddString("32-����");
					m_comBox.AddString("33-����");
					m_comBox.AddString("34-����");
					m_comBox.AddString("35-������");
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
                m_comBox.ShowDropDown();//�Զ�����
            }
            else//���еĵ�Ԫ����֮ǰ�����õ�
            {
                m_comBox.SetFocus();//����Ϊ���� 
            }
        }
        else
        {
            e_Item = pEditCtrl->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
            e_SubItem = pEditCtrl->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
            createCcombobox(pEditCtrl, &m_comBox, e_Item, e_SubItem, m_isCreatCombo);//�����༭��
            if(pEditCtrl->iSubItem == 1)
				{
					m_comBox.AddString("00-δ��");
					m_comBox.AddString("01-����");
					m_comBox.AddString("02-����");
					m_comBox.AddString("03-ֱ��");
					m_comBox.AddString("04-�¶�");
					m_comBox.AddString("05-ʪ��");
					m_comBox.AddString("06-����");
					m_comBox.AddString("07-ģ��");
					m_comBox.AddString("08-����");
					m_comBox.AddString("09-����");
					m_comBox.AddString("10-����");
					m_comBox.AddString("11-ˮ��");
					m_comBox.AddString("12-�Ž�");
					m_comBox.AddString("13-�ͻ�");
					m_comBox.AddString("14-�յ�");
					m_comBox.AddString("15-����");
					m_comBox.AddString("16-����");
					m_comBox.AddString("17-����");
					m_comBox.AddString("18-����");
					m_comBox.AddString("19-����");
					m_comBox.AddString("20-����");
					m_comBox.AddString("21-�ϵ�");
					m_comBox.AddString("22-��");
					m_comBox.AddString("23-����");
					m_comBox.AddString("24-����");
					m_comBox.AddString("25-����");
					m_comBox.AddString("26-����");
					m_comBox.AddString("27-����");
					m_comBox.AddString("28-����");
					m_comBox.AddString("29-����");
					m_comBox.AddString("30-΢��");
					m_comBox.AddString("31-����");
					m_comBox.AddString("32-����");
					m_comBox.AddString("33-����");
					m_comBox.AddString("34-����");
					m_comBox.AddString("35-������");
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
                m_comBox.ShowDropDown();//�Զ�����
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
    createdit->SetParent(&m_PathList); // list control����Ϊ������,���ɵ�Edit������ȷ��λ

    CRect  EditRect;
    m_PathList.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect);	// ��ȡ��Ԫ��Ŀռ�λ����Ϣ
    EditRect.SetRect(EditRect.left+1, EditRect.top+1, EditRect.left + m_PathList.GetColumnWidth(e_SubItem)-1, EditRect.bottom-1);
    CString strItem = m_PathList.GetItemText(e_Item, e_SubItem);		// �����Ӧ��Ԫ���ַ�
    createdit->SetWindowText(strItem);	// ����Ԫ���ַ���ʾ�ڱ༭����
    createdit->MoveWindow(&EditRect);	// ���༭��λ�÷�����Ӧ��Ԫ����
    createdit->ShowWindow(SW_SHOW);		// ��ʾ�༭���ڵ�Ԫ������
    createdit->SetFocus();				// ����Ϊ���� 
    createdit->SetSel(-1);				// ���ù�����ı������ֵ����
}

void CParamConfig4::distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem)
{
    CString meditdata;
    distroyedit->GetWindowText(meditdata);
    list->SetItemText(Item, SubItem, meditdata);	// �����Ӧ��Ԫ���ַ�
    distroyedit->DestroyWindow();					// ���ٶ���
}

void CParamConfig4::createCcombobox(NM_LISTVIEW  *pEditCtrl, CComboBox *createccombo, int &Item, int &SubItem, bool &isCreat) 
{
    Item = pEditCtrl->iItem;
    SubItem = pEditCtrl->iSubItem;
    isCreat = true;

    createccombo->Create(WS_CHILD | WS_VISIBLE |  CBS_DROPDOWN | CBS_OEMCONVERT, CRect(0, 0, 0, 0), this, IDC_COMBOX_CREATEID);
    createccombo->SetFont(this->GetFont(), FALSE);
    createccombo->SetParent(&m_PathList); // list control����Ϊ������,���ɵ�Ccombobox������ȷ��λ

    CRect  EditRect;
    m_PathList.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect); // ��ȡ��Ԫ��Ŀռ�λ����Ϣ
    EditRect.SetRect(EditRect.left + 1, EditRect.top + 1, EditRect.left + m_PathList.GetColumnWidth(e_SubItem) - 1, EditRect.bottom - 1);

    CString strItem = m_PathList.GetItemText(e_Item, e_SubItem);		// �����Ӧ��Ԫ���ַ�
    createccombo->SetWindowText(strItem);					
    createccombo->MoveWindow(&EditRect);				
    createccombo->ShowWindow(SW_SHOW);								
}

void CParamConfig4::distroyCcombobox(CListCtrl *list, CComboBox* distroyccombo, int &Item, int &SubItem)
{
    CString meditdata;
    distroyccombo->GetWindowText(meditdata);
    list->SetItemText(Item, SubItem, meditdata);	// ������Ӧ��Ԫ���ַ�
    distroyccombo->DestroyWindow();					// ���ٶ���
}

void CParamConfig4::OnKillfocusEdit()
{
    if (m_isCreatEdit == true)//���֮ǰ�����˱༭������ٵ�
    {
        distroyEdit(&m_PathList, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
        m_isCreatEdit = false;
    }
    if (m_isCreatCombo == true)//���֮ǰ�����������б������ٵ�
    {
        distroyCcombobox(&m_PathList, &m_comBox, e_Item, e_SubItem);
        m_isCreatCombo = false;
    }
}

void CParamConfig4::OnKillfocusCcomboBox()
{
    if (m_isCreatEdit == true)//���֮ǰ�����˱༭������ٵ�
    {
        distroyEdit(&m_PathList, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
        m_isCreatEdit = false;
    }
    if (m_isCreatCombo == true)//���֮ǰ�����������б������ٵ�
    {
        distroyCcombobox(&m_PathList, &m_comBox, e_Item, e_SubItem);
        m_isCreatCombo = false;
    }
}
// ��Enter��
void CParamConfig4::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	OnKillfocusEdit();
	OnKillfocusCcomboBox();
	// CDialog::OnOK();
}

// ѡ������16ͨ��
void CParamConfig4::OnBnClickedRadio16ch()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_24 ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_25 ) ) )->SetCheck( FALSE );
}
// ѡ������32ͨ��
void CParamConfig4::OnBnClickedRadio32ch()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_25 ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_24 ) ) )->SetCheck( FALSE );
}
// ѡ������ͨ�ð汾
void CParamConfig4::OnBnClickedRadioTY()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_26 ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_27 ) ) )->SetCheck( FALSE );
}
// ѡ������2M�汾
void CParamConfig4::OnBnClickedRadio2M()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_27 ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_26 ) ) )->SetCheck( FALSE );
}

// ͨ������ѡ�� ������ť
void CParamConfig4::OnBnClickedButtonPathAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( /*IfExistsPathConfig(ComboBox2->Text)*/ FALSE) // TODO: ʵ�ֺ���IfExistsPathConfig
    {
		MessageBox("ָ����ͨ�������ļ��Ѵ��ڣ���ֱ���޸ģ�", "��ʾ", MB_ICONWARNING);
        return;

    }
    if( /*AddPathConfigToBase() == FALSE*/ TRUE)		 // TODO: ʵ�ֺ���AddPathConfigToBase
    {
		MessageBox("ͨ�������ļ�����ʧ�ܣ�", "��ʾ", MB_ICONWARNING);
        return ;
    }
    /*InitialPathCfgCombox();*/				 // TODO: ʵ�ֺ���InitialPathCfgCombox
	MessageBox("ͨ�������ļ������ɹ���", "��ʾ", MB_ICONWARNING);
}
// ͨ������ѡ�� ������ť
void CParamConfig4::OnBnClickedButtonPathExport()
{
	MessageBox("TODO: ʵ�ֵ�����ť����", "��ʾ", MB_ICONWARNING);
	/*InitialPathCfgCombox();*/	
	/*AnsiString strSql = *** */				 // TODO: ʵ��Sql���
												 // TODO: ����Sql���������ݿ����
												 // TODO: ���ò���
}
// ͨ������ѡ�� �޸İ�ť
void CParamConfig4::OnBnClickedButtonPathModify()
{
	if( /*!(IfExistsPathConfig(ComboBox1->Text))*/ TRUE)
    {
		MessageBox("ָ���������ļ������ڣ���������", "��ʾ", MB_ICONWARNING);
        return;
    }
    /*InitialPathCfgCombox();*/
	if( IDCANCEL == MessageBox("ȷ���޸�ͨ��������", "�޸�ȷ��", MB_OKCANCEL | MB_ICONQUESTION) )
        return;
    if( /*DelPathConfigFromBase(ComboBox1->Text) == false*/ FALSE)
    {
		MessageBox("�޸�ʧ�ܣ�", "��ʾ", MB_ICONWARNING);
        return ;
    }
    if( /*AddPathConfigToBase() == false*/ TRUE)
    {
		MessageBox("�޸�ʧ�ܣ�", "��ʾ", MB_ICONWARNING);
        return ;
    }
	MessageBox("�޸ĳɹ���", "��ʾ", MB_ICONWARNING);
}
// ͨ������ѡ�� ɾ����ť
void CParamConfig4::OnBnClickedButtonPathDelete()
{
	if(IDCANCEL == MessageBox("ȷ��ɾ����ѡ��ͨ�������ļ���", "ɾ��ȷ��", MB_OKCANCEL | MB_ICONQUESTION))
        return;
    if( /*DelPathConfigFromBase(ComboBox1->Text) == false*/ TRUE)
    {
        MessageBox("ɾ��ʧ�ܣ�", "��ʾ", MB_ICONWARNING);
        return ;
    }
    MessageBox("ɾ���ɹ���", "��ʾ", MB_ICONWARNING);
    /*InitialPathCfgCombox();*/
}
// ͨ������ �ɹ��������㰴ť
void CParamConfig4::OnBnClickedButtonResetCount()
{
	/*PathCount = 0*/ //����ȫ�ֱ�������Ϊ0
	( ( CEdit* )( GetDlgItem( IDC_EDIT_PATH_1 ) ) )->SetWindowText( "0" );
}
// ͨ�����ð�ť
void CParamConfig4::OnBnClickedButtonPathConfig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( !pMainDlg->m_bIsOpenSerl )
	{
		MessageBox("���ȴ򿪴��ڣ�", "��ʾ", MB_ICONWARNING);
		return;
	}
	if( m_PathList.GetItemText(3, 1) == "" )
	{
		MessageBox("�뵼��ͨ�������ļ���", "��ʾ", MB_ICONWARNING);
		return;
	}
	if( /*�Ƿ����������ݿ�*/ TRUE )
	{
		if( /*!(IfExistsPathConfig(ComboBox1->Text))*/ FALSE)
		{
			MessageBox("ָ����ͨ�������ļ������ڣ�", "��ʾ", MB_ICONWARNING);
			return;
		}
	}
	if(IDCANCEL == MessageBox("�����µ�ͨ����Ϣ��ԭ�е�ͨ����Ϣ�������ȷ����", "��ʾ", MB_OKCANCEL | MB_ICONQUESTION))
        return;

	/*ͨ�����ô���*/
	( ( CButton* )( GetDlgItem( IDC_BUTTON_PATH_6 ) ) )->EnableWindow( FALSE );
	/*StartPathConfig()*/ //��һ���߳̿�ʼͨ������
}



