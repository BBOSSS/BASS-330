// ParamConfig4.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BASS-330.h"
#include "ParamConfig4.h"
#include "BASS-330Dlg.h"
#include "ProtocolHandle.h"
#include "ProcessBar.h"

// CParamConfig4 �Ի���

IMPLEMENT_DYNAMIC(CParamConfig4, CDialog)

CParamConfig4::CParamConfig4(CWnd* pParent /*=NULL*/)
	: CDialog(CParamConfig4::IDD, pParent)
	, m_isCreatEdit(false)
	, m_isCreatCombo(false)
	, m_ChannelSuccessCount(0)
	, m_ListSuccessCount(0)
	, m_ListCount(0)
	, m_pSetItemAttriThread(NULL)
	, m_ChannelCount(16)
	, m_processBar(NULL)
	, m_pSetListThread(NULL)
	, m_pSetListThread2M(NULL)
{
}

CParamConfig4::~CParamConfig4()
{
	if(m_processBar != NULL)
		delete m_processBar;
}

void CParamConfig4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_AIDI, m_PathList);
	DDX_Control(pDX, IDC_COMBO_PATH_1, m_ComboBox_Channel);
	DDX_Control(pDX, IDC_COMBO_LIST_1, m_ComboBox_List);
	DDX_Control(pDX, IDC_LIST_NAME, m_NameList);
	DDX_Control(pDX, IDC_EXPIRY_DATE1, m_DateTime);
	DDX_Control(pDX, IDC_COMBO_LIST_2, m_ComboBox_WorkList);
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
	ON_BN_CLICKED(IDC_BUTTON_LIST_1, &CParamConfig4::OnBnClickedButtonListExport)
	ON_BN_CLICKED(IDC_BUTTON_LIST_2, &CParamConfig4::OnBnClickedButtonListAddOne)
	ON_BN_CLICKED(IDC_BUTTON_LIST_3, &CParamConfig4::OnBnClickedButtonListDeleteOne)
	ON_BN_CLICKED(IDC_BUTTON_LIST_4, &CParamConfig4::OnBnClickedButtonListDelete)
	ON_BN_CLICKED(IDC_BUTTON_LIST_6, &CParamConfig4::OnBnClickedButtonLisAdd)
	ON_BN_CLICKED(IDC_BUTTON_LIST_5, &CParamConfig4::OnBnClickedButtonListResetCnt)
	ON_CBN_SELCHANGE(IDC_COMBO_LIST_1, &CParamConfig4::OnCbnSelchangeComboList)
	ON_CBN_SELCHANGE(IDC_COMBO_PATH_1, &CParamConfig4::OnCbnSelchangeComboPath)
	ON_BN_CLICKED(IDC_BUTTON_LIST_7, &CParamConfig4::OnBnClickedButtonListConfig)
END_MESSAGE_MAP()


// CParamConfig4 ��Ϣ�������

BOOL CParamConfig4::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��ʼ���Ӵ���ȫ��ָ��4
	pSubDlg4 = this;

	// ((CButton*)(GetDlgItem(IDC_RADIO_16CH)))->SetCheck(TRUE);
	// ((CButton*)(GetDlgItem(IDC_RADIO_CFG_1)))->SetCheck(TRUE);

	// ��ʼ��ͨ���б�ؼ�   
	CRect rect;
    m_PathList.GetClientRect(&rect);    
    m_PathList.SetExtendedStyle(m_PathList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
    // Ϊ�б���ͼ�ؼ����8��   
    m_PathList.InsertColumn(0, _T("ͨ��"),		LVCFMT_CENTER, rect.Width()*3/32, 0);   
    m_PathList.InsertColumn(1, _T("����"),		LVCFMT_CENTER, rect.Width()*5/32, 1);   
    m_PathList.InsertColumn(2, _T("����"),		LVCFMT_CENTER, rect.Width()*5/32, 2);   
	m_PathList.InsertColumn(3, _T("����"),		LVCFMT_CENTER, rect.Width()*3/32, 3);
	m_PathList.InsertColumn(4, _T("��λ"),		LVCFMT_CENTER, rect.Width()*3/32, 4);
	m_PathList.InsertColumn(5, _T("��У"),		LVCFMT_CENTER, rect.Width()*3/32, 5);
	m_PathList.InsertColumn(6, _T("�������"), LVCFMT_CENTER, rect.Width()*5/32, 6);
	m_PathList.InsertColumn(7, _T("�������"), LVCFMT_CENTER, rect.Width()*5/32, 7);
	// ���32��
	for(int i = 0; i < 32; i++)
	{
		CString temp;
		if(i < 9) temp += "0";
		temp += ToString( i+1 );
		m_PathList.InsertItem( i, temp );
	}

	// ��ʼ�������б�ؼ�   
    m_NameList.GetClientRect(&rect);    
    m_NameList.SetExtendedStyle(m_NameList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
    // Ϊ�б���ͼ�ؼ����2��   
    m_NameList.InsertColumn(0, _T("��������"),	LVCFMT_CENTER, rect.Width() / 2, 0);   
    m_NameList.InsertColumn(1, _T("����"),		LVCFMT_CENTER, rect.Width() / 2, 1); 

	m_DateTime.SetFormat(_T("yyyy-MM-dd"));		// ����������ʾ��ʽ

	m_ComboBox_WorkList.AddString("��0�ű�");
	m_ComboBox_WorkList.AddString("��1�ű�");
	m_ComboBox_WorkList.AddString("��2�ű�");
	m_ComboBox_WorkList.AddString("��3�ű�");
	m_ComboBox_WorkList.AddString("��4�ű�");
	m_ComboBox_WorkList.SetCurSel( 0 );

	m_ComboBox_WorkList.EnableWindow( FALSE );
	m_DateTime.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
}

// �б�ؼ��¼�������
void CParamConfig4::OnNMClickListPath(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;

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
					m_comBox.AddString("00-δ��");m_comBox.AddString("01-����");m_comBox.AddString("02-����");m_comBox.AddString("03-ֱ��");
					m_comBox.AddString("04-�¶�");m_comBox.AddString("05-ʪ��");m_comBox.AddString("06-����");m_comBox.AddString("07-ģ��");
					m_comBox.AddString("08-����");m_comBox.AddString("09-����");m_comBox.AddString("10-����");m_comBox.AddString("11-ˮ��");
					m_comBox.AddString("12-�Ž�");m_comBox.AddString("13-�ͻ�");m_comBox.AddString("14-�յ�");m_comBox.AddString("15-����");
					m_comBox.AddString("16-����");m_comBox.AddString("17-����");m_comBox.AddString("18-����");m_comBox.AddString("19-����");
					m_comBox.AddString("20-����");m_comBox.AddString("21-�ϵ�");m_comBox.AddString("22-��");m_comBox.AddString("23-����");
					m_comBox.AddString("24-����");m_comBox.AddString("25-����");m_comBox.AddString("26-����");m_comBox.AddString("27-����");
					m_comBox.AddString("28-����");m_comBox.AddString("29-����");m_comBox.AddString("30-΢��");m_comBox.AddString("31-����");
					m_comBox.AddString("32-����");m_comBox.AddString("33-����");m_comBox.AddString("34-����");m_comBox.AddString("35-������");
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
				m_comBox.AddString("00-δ��");m_comBox.AddString("01-����");m_comBox.AddString("02-����");m_comBox.AddString("03-ֱ��");
				m_comBox.AddString("04-�¶�");m_comBox.AddString("05-ʪ��");m_comBox.AddString("06-����");m_comBox.AddString("07-ģ��");
				m_comBox.AddString("08-����");m_comBox.AddString("09-����");m_comBox.AddString("10-����");m_comBox.AddString("11-ˮ��");
				m_comBox.AddString("12-�Ž�");m_comBox.AddString("13-�ͻ�");m_comBox.AddString("14-�յ�");m_comBox.AddString("15-����");
				m_comBox.AddString("16-����");m_comBox.AddString("17-����");m_comBox.AddString("18-����");m_comBox.AddString("19-����");
				m_comBox.AddString("20-����");m_comBox.AddString("21-�ϵ�");m_comBox.AddString("22-��");m_comBox.AddString("23-����");
				m_comBox.AddString("24-����");m_comBox.AddString("25-����");m_comBox.AddString("26-����");m_comBox.AddString("27-����");
				m_comBox.AddString("28-����");m_comBox.AddString("29-����");m_comBox.AddString("30-΢��");m_comBox.AddString("31-����");
				m_comBox.AddString("32-����");m_comBox.AddString("33-����");m_comBox.AddString("34-����");m_comBox.AddString("35-������");
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
	m_ComboBox_WorkList.EnableWindow( FALSE );
	m_DateTime.EnableWindow(FALSE);
}
// ѡ������2M�汾
void CParamConfig4::OnBnClickedRadio2M()
{
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_27 ) ) )->SetCheck( TRUE );
	( ( CButton* )( pSubDlg7->GetDlgItem( IDC_CHECK_7_26 ) ) )->SetCheck( FALSE );
	m_ComboBox_WorkList.EnableWindow( TRUE );
	m_DateTime.EnableWindow(TRUE);
}

// �ж��Ƿ���� 
bool CParamConfig4::IsExist(std::string target, std::string field, std::string table, MySQLInterface &uMySQL)
{
	using namespace std;
	uMySQL.SetMySQLConInfo(SERVER, USER, PASSWORD, DATABASE, PORT);

	if(uMySQL.Open() == false)
	{
		TRACE("MySQL Connect Faild!\r\n");
		return false;
	}
	vector<vector<string>> data;
	string strsql = "SELECT " + field + " FROM " + table + " WHERE " + field + " = '" + target + "' LIMIT 1";
	if(uMySQL.Select(strsql, data) == false)
		return false;
	if(data.empty())
		return false;
	return true;
}

// ��������ͨ�������ݿ�
bool CParamConfig4::SaveChannelConfig()
{
	using namespace std;

	MySQLInterface uMySQL;
	uMySQL.SetMySQLConInfo(SERVER, USER, PASSWORD, DATABASE, PORT);

	if(uMySQL.Open() == false)
	{
		TRACE("MySQL Connect Faild!\r\n");
		return false;
	}
	for(int i = 0; i < 32; i++)
	{
		CString strsql = "INSERT INTO channelconfig";
		strsql += "(PeiZhiMC, TongDao, LeiXing, ShangXian, XiaXian, FuWei, TiaoJiaoZhi, ShangXianSC, XiaXianSC)";
		strsql += "VALUES( '";
		CString TempStr;
		GetDlgItemText(IDC_COMBO_PATH_1, TempStr);	strsql += (TempStr + "', '");
		TempStr = m_PathList.GetItemText(i, 0);		strsql += (TempStr + "', '");
		TempStr = m_PathList.GetItemText(i, 1);		strsql += (TempStr + "', '");
		TempStr = m_PathList.GetItemText(i, 2);		strsql += (TempStr + "', '");
		TempStr = m_PathList.GetItemText(i, 3);		strsql += (TempStr + "', '");
		TempStr = m_PathList.GetItemText(i, 4);		strsql += (TempStr + "', '");
		TempStr = m_PathList.GetItemText(i, 5);		strsql += (TempStr + "', '");
		TempStr = m_PathList.GetItemText(i, 6);		strsql += (TempStr + "', '");
		TempStr = m_PathList.GetItemText(i, 7);		strsql += (TempStr + "' );");
		std::string QueryStr(strsql.GetBuffer());
		if(uMySQL.Query(QueryStr) == false)
		{
			uMySQL.Close();
			return false;
		}
	}
	uMySQL.Close();
	return true;
}

// �����ݿ��������ͨ��
bool CParamConfig4::LoadChannelConfig(std::string peizhimc)
{
	using namespace std;

	MySQLInterface uMySQL;
	uMySQL.SetMySQLConInfo(SERVER, USER, PASSWORD, DATABASE, PORT);

	if(uMySQL.Open() == false)
	{
		TRACE("MySQL Connect Faild!\r\n");
		return false;
	}
	vector<vector<string>> data;
	string strsql = "SELECT TongDao, LeiXing, ShangXian, XiaXian, FuWei, TiaoJiaoZhi, ShangXianSC, XiaXianSC ";
	strsql += "FROM channelconfig WHERE PeiZhiMC = '" + peizhimc + "' ORDER BY TongDao;";

	if(uMySQL.Select(strsql, data) == false)
	{
		uMySQL.Close();
		return false;
	}
	CString TempStr;
	for(unsigned int i = 0; i < data.size(); i++)
	{
		TempStr = data[i][0].c_str();
		m_PathList.SetItemText(i, 0, TempStr);
		TempStr = data[i][1].c_str();
		m_PathList.SetItemText(i, 1, TempStr);
		TempStr = data[i][2].c_str();
		m_PathList.SetItemText(i, 2, TempStr);
		TempStr = data[i][3].c_str();
		m_PathList.SetItemText(i, 3, TempStr);
		TempStr = data[i][4].c_str();
		m_PathList.SetItemText(i, 4, TempStr);
		TempStr = data[i][5].c_str();
		m_PathList.SetItemText(i, 5, TempStr);
		TempStr = data[i][6].c_str();
		m_PathList.SetItemText(i, 6, TempStr);
		TempStr = data[i][7].c_str();
		m_PathList.SetItemText(i, 7, TempStr);
	}

	uMySQL.Close();
	return true;
}

// ͨ������ѡ�� ������ť
void CParamConfig4::OnBnClickedButtonPathAdd()
{
	MySQLInterface uMySQL;
	CString TempStr;
	m_ComboBox_Channel.GetWindowText(TempStr);
	std::string str(TempStr.GetBuffer());
	if(IsExist(str, "PeiZhiMC", "channelconfig", uMySQL))
    {
		MessageBox("ָ����ͨ�������ļ��Ѵ��ڣ���ֱ���޸ģ�", "��ʾ", MB_ICONWARNING);
		uMySQL.Close();
        return;
    }
	uMySQL.Close();

    if( SaveChannelConfig() == false )	
    {
		AfxMessageBox("ͨ���������ʧ�ܣ�");
        return ;
    }
    m_ComboBox_Channel.AddString(TempStr);
	pSubDlg7->m_ComboBox_Channel.AddString(TempStr);
	pSubDlg7->m_ComboBox_Channel.SetWindowText(TempStr);
	MessageBox("ͨ�����������ɹ���", "��ʾ", MB_ICONINFORMATION);
}
// ͨ������ѡ�� ������ť
void CParamConfig4::OnBnClickedButtonPathExport()
{
	MySQLInterface uMySQL;
	CString TempStr;
	m_ComboBox_Channel.GetWindowText(TempStr);
	std::string str(TempStr.GetBuffer());
	if(!IsExist(str, "PeiZhiMC", "channelconfig", uMySQL))
    {
		MessageBox("ָ����ͨ�������ļ������ڣ�������ѡ��", "��ʾ", MB_ICONWARNING);
		uMySQL.Close();
        return;
    }
	uMySQL.Close();
	if(LoadChannelConfig(str) == false) 
	{
		AfxMessageBox("����ʧ�ܣ�");
		return;
	}
	pSubDlg7->m_ComboBox_Channel.SetWindowText(TempStr);
	MessageBox("�����ɹ���", "��ʾ", MB_ICONINFORMATION);
}
// ͨ������ѡ�� �޸İ�ť
void CParamConfig4::OnBnClickedButtonPathModify()
{
	MySQLInterface uMySQL;
	CString TempStr;
	m_ComboBox_Channel.GetWindowText(TempStr);
	std::string str(TempStr.GetBuffer());
	if(!IsExist(str, "PeiZhiMC", "channelconfig", uMySQL))
    {
		MessageBox("ָ���������ļ������ڣ���������", "��ʾ", MB_ICONWARNING);
		uMySQL.Close();
        return;
    }
	if( IDCANCEL == MessageBox("ȷ���޸�ͨ��������", "�޸�ȷ��", MB_OKCANCEL | MB_ICONQUESTION) )
	{
		uMySQL.Close();
        return;
	}
    std::string strsql = "DELETE FROM channelconfig WHERE PeiZhiMC = '" + str + "'";
	if(uMySQL.Query(strsql) == false)
	{
		AfxMessageBox("�޸�ʧ�ܣ�");
		uMySQL.Close();
		return;
	}
	uMySQL.Close();
    if( SaveChannelConfig() == false )
    {
		MessageBox("�޸�ʧ�ܣ�", "��ʾ", MB_ICONWARNING);
        return ;
    }
	pSubDlg7->m_ComboBox_Channel.SetWindowText(TempStr);
	MessageBox("�޸ĳɹ���", "��ʾ", MB_ICONINFORMATION);
}
// ͨ������ѡ�� ɾ����ť
void CParamConfig4::OnBnClickedButtonPathDelete()
{
	MySQLInterface uMySQL;
	CString TempStr;
	m_ComboBox_Channel.GetWindowText(TempStr);
	std::string str(TempStr.GetBuffer());
	if(!IsExist(str, "PeiZhiMC", "channelconfig", uMySQL))
    {
		MessageBox("ָ���������ļ����������ݿ��У�", "��ʾ", MB_ICONWARNING);
		uMySQL.Close();
        return;
    }
	if(IDCANCEL == MessageBox("ȷ��ɾ����ѡ�������ļ���", "ɾ��ȷ��", MB_OKCANCEL | MB_ICONQUESTION))
	{
		uMySQL.Close();
        return;
	}
	std::string strsql = "DELETE FROM channelconfig WHERE PeiZhiMC = '" + str + "'";
	if(uMySQL.Query(strsql) == false)
	{
		AfxMessageBox("ɾ��ʧ�ܣ�");
		uMySQL.Close();
		return;
	}
    MessageBox("ɾ���ɹ���", "��ʾ", MB_ICONINFORMATION);
	uMySQL.Close();
    pSubDlg7->InitChannelComboBox();
}
// ͨ������ �ɹ��������㰴ť
void CParamConfig4::OnBnClickedButtonResetCount()
{
	m_ChannelSuccessCount = 0;
	SetDlgItemText(IDC_EDIT_PATH_1, ToString(m_ChannelSuccessCount));
}

// ͬ��ͨ����Ͽ�
void CParamConfig4::OnCbnSelchangeComboPath()
{
	CString TempStr;
	int nSel = m_ComboBox_Channel.GetCurSel();    
    m_ComboBox_Channel.GetLBText(nSel, TempStr);
	pSubDlg7->m_ComboBox_Channel.SetWindowText(TempStr);
}

// ͨ�����ð�ť
void CParamConfig4::OnBnClickedButtonPathConfig()
{
	if( !pMainDlg->m_bIsOpenSerl )
	{
		MessageBox("���ȴ򿪴��ڣ�", "��ʾ", MB_ICONWARNING);
		return;
	}
	if( m_PathList.GetItemText(0, 1).IsEmpty() )
	{
		MessageBox("�뵼��ͨ�������ļ���", "��ʾ", MB_ICONWARNING);
		return;
	}
	int CHECK_16CH = ( ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_16CH ) ) )->GetCheck( );
	int CHECK_32CH = ( ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_32CH ) ) )->GetCheck( );
	if( FALSE ==  CHECK_16CH && FALSE == CHECK_32CH )
	{
		AfxMessageBox("����ѡ������ͨ������");
		return;
	}
	if(IDCANCEL == MessageBox("�����µ�ͨ����Ϣ��ԭ�е�ͨ����Ϣ�������ȷ����", "��ʾ", MB_OKCANCEL | MB_ICONQUESTION))
        return;

	( ( CButton* )( GetDlgItem( IDC_BUTTON_PATH_6 ) ) )->EnableWindow( FALSE );

	if( TRUE == CHECK_16CH )		m_ChannelCount = 16;
	else if( TRUE == CHECK_32CH )	m_ChannelCount = 32;

	if(m_pSetItemAttriThread)
    {
        ::TerminateThread(m_pSetItemAttriThread->m_hThread, 0);
        m_pSetItemAttriThread = NULL;
    }
	m_pSetItemAttriThread = AfxBeginThread(SetItemAttriThread, this);

	 if (NULL == m_processBar)   
    {    
        m_processBar = new CProcessBar();   
        m_processBar->Create(IDD_DIALOG_BAR, this);  
    }
	m_processBar->m_Bar.SetRange(0, m_ChannelCount);
	m_processBar->m_maxRange = m_ChannelCount;
    m_processBar->ShowWindow(SW_SHOW); 
}

// ����ͨ�������߳�
UINT CParamConfig4::SetItemAttriThread(LPVOID pParam)
{
	unsigned int ChannelCnt = pSubDlg4->m_ChannelCount;
	CButton* pButton = ( CButton* )( pSubDlg4->GetDlgItem( IDC_BUTTON_PATH_6 ));

	for(unsigned int i = 0; i < ChannelCnt; i++)
	{
		ItemAttri itemvalue;
		itemvalue.No = ToInt( pSubDlg4->m_PathList.GetItemText(i, 0) );	// ͨ����
		CString typeStr = pSubDlg4->m_PathList.GetItemText(i, 1);
		itemvalue.Type = ToInt( typeStr.Left(2) );						// ���ͺ�

		if(typeStr == "08-����" || typeStr == "09-����" || typeStr == "10-����" || typeStr == "11-ˮ��" || \
		   typeStr == "12-�Ž�" || typeStr == "13-�ͻ�" || typeStr == "14-�յ�" || typeStr == "15-����" || \
		   typeStr == "16-����" || typeStr == "17-����" || typeStr == "18-����" || typeStr == "19-����" || \
		   typeStr == "20-�ϵ�" || typeStr == "21-��" || typeStr == "22-����" || typeStr == "22-����" || \
		   typeStr == "23-����" || typeStr == "23-����" || typeStr == "24-����" || typeStr == "24-����" || \
		   typeStr == "25-����" || typeStr == "25-΢��" || typeStr == "26-����" || typeStr == "26-����" || \
		   typeStr == "27-����" || typeStr == "28-����" || typeStr == "29-������" || typeStr == "18-����" )
		{     
			CString upStr = pSubDlg4->m_PathList.GetItemText(i, 2);
			itemvalue.Uplimit = ToInt( upStr.Left(2) );								// ����
			itemvalue.Dnout	  = ToInt( pSubDlg4->m_PathList.GetItemText(i, 6) );	// �������
		}
		else
		{
			CString upStr = pSubDlg4->m_PathList.GetItemText(i, 2);
			itemvalue.Uplimit = ToInt( upStr );										// ����
			itemvalue.Dnout	  = ToInt( pSubDlg4->m_PathList.GetItemText(i, 7) );	// �������
		}
		itemvalue.Dnlimit = ToInt( pSubDlg4->m_PathList.GetItemText(i, 3) );		// ����
        itemvalue.Tol	  =	ToInt( pSubDlg4->m_PathList.GetItemText(i, 4) );		// ����
        itemvalue.Adj	  = ToInt( pSubDlg4->m_PathList.GetItemText(i, 5) );		// ��У
        itemvalue.Upout	  = ToInt( pSubDlg4->m_PathList.GetItemText(i, 6) );		// �������

		CProtocolHandle ComProto;
		BYTE RecvBuffer[PACKET_SIZE] = {0};
		BYTE SendData[PACKET_SIZE]   = {0};

		ComProto.PacketItemAttriData(itemvalue, SendData);
		int length = ComProto.Package(0x11, SendData, 20);
		pMainDlg->is2MPacket = false;
		pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// ��������

		WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// �ȴ����ڽ������һ֡����
		if(pMainDlg->m_bRecvPacketTail == false)						// ����־λ ����3��û�յ���β
		{
			TRACE("Receive overtime!\n");
			pButton->EnableWindow( TRUE );
			AfxMessageBox("����ͨ������ʧ�ܣ�");
			return FALSE;
		}
		int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
		RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));

		if(FALSE == ComProto.isVaildPacket(0x11, RecvBuffer, RecvBufLen))
		{
			TRACE("Not vaild packet!\n");
			pButton->EnableWindow( TRUE );
			AfxMessageBox("����ͨ������ʧ�ܣ�");
			return FALSE;
		}
		pSubDlg4->m_processBar->UpdateBar(i+1);
		pSubDlg4->m_ChannelSuccessCount++;
		pSubDlg4->SetDlgItemText(IDC_EDIT_PATH_1, ToString(pSubDlg4->m_ChannelSuccessCount));
	}
	Sleep(300);
	pButton->EnableWindow( TRUE );
	pSubDlg4->MessageBox("����ͨ�����Գɹ���", "��ʾ", MB_ICONINFORMATION);
	return TRUE;
}

// �����ݿ������������
bool CParamConfig4::LoadListConfig(std::string pzmc)
{
	using namespace std;

	MySQLInterface uMySQL;
	uMySQL.SetMySQLConInfo(SERVER, USER, PASSWORD, DATABASE, PORT);

	if(uMySQL.Open() == false)
	{
		TRACE("MySQL Connect Faild!\r\n");
		return false;
	}
	vector<vector<string>> data;
	string strsql = "SELECT PZMingCheng, Cardno ";
	strsql += "FROM listconfig WHERE PZMingCheng = '" + pzmc + "' ;";

	if(uMySQL.Select(strsql, data) == false)
	{
		uMySQL.Close();
		return false;
	}
	m_ListCount = data.size();
	CString TempStr;
	m_NameList.DeleteAllItems();
	for(unsigned int i = 0; i < m_ListCount; i++)
	{
		m_NameList.InsertItem(i, "");
		TempStr = data[i][0].c_str();
		m_NameList.SetItemText(i, 0, TempStr);
		TempStr = data[i][1].c_str();
		m_NameList.SetItemText(i, 1, TempStr);
	}
	SetDlgItemText(IDC_EDIT_LIST_2, ToString(m_ListCount));
	uMySQL.Close();
	return true;
}

// ������������
void CParamConfig4::OnBnClickedButtonListExport()
{
	MySQLInterface uMySQL;
	CString TempStr;
	m_ComboBox_List.GetWindowText(TempStr);
	std::string str(TempStr.GetBuffer());
	if(!IsExist(str, "PZMingCheng", "listconfig", uMySQL))
    {
		MessageBox("ָ����ͨ�������ļ������ڣ�������ѡ��", "��ʾ", MB_ICONWARNING);
		uMySQL.Close();
        return;
    }
	uMySQL.Close();
	if(LoadListConfig(str) == false) 
	{
		AfxMessageBox("����ʧ�ܣ�");
		return;
	}
	pSubDlg7->m_ComboBox_List.SetWindowText(TempStr);
	MessageBox("�����ɹ���", "��ʾ", MB_ICONINFORMATION);
}

// �ж������Ƿ����
bool CParamConfig4::IsExistName(CString pzmc, CString cardno, MySQLInterface &uMySQL)
{
	using namespace std;
	uMySQL.SetMySQLConInfo(SERVER, USER, PASSWORD, DATABASE, PORT);

	string str1(pzmc.GetBuffer());
	string str2(cardno.GetBuffer());

	string strsql = "SELECT PZMingCheng, Cardno FROM listconfig ";
	strsql += "WHERE PZMingCheng = '" + str1 + "' ";
	strsql += "AND Cardno = '" + str2 + "' ;";

	if(uMySQL.Open() == false)
	{
		TRACE("MySQL Connect Faild!\r\n");
		return false;
	}
	vector<vector<string>> data;
	if(!uMySQL.Select(strsql, data)) return false;
	if(data.empty())  return false;

	return true;
}

// ����һ������
void CParamConfig4::OnBnClickedButtonListAddOne()
{
	CString PZMC, CARDNO;
	m_ComboBox_List.GetWindowText(PZMC);
	GetDlgItemText(IDC_EDIT_LIST_1, CARDNO);
	if(PZMC.IsEmpty() || CARDNO.IsEmpty())
	{
		AfxMessageBox("�����������Ų���Ϊ�գ�");
		return;
	}
	MySQLInterface uMySQL;
	if(IsExistName(PZMC, CARDNO, uMySQL))
	{
		AfxMessageBox("ָ�������������Ѵ��ڣ�");
		uMySQL.Close();
		return;
	}
	CString strsql = "INSERT INTO listconfig";
	strsql += "(PZMingCheng, Cardno) VALUES('";
	strsql += PZMC + "', '";
	strsql += CARDNO + "')";

	std::string QueryStr(strsql.GetBuffer());
	if(uMySQL.Query(QueryStr) == false)
	{
		AfxMessageBox("����һ������ʧ�ܣ�");
		uMySQL.Close();
		return;
	}
	uMySQL.Close();
	std::string pzmc(PZMC.GetBuffer());
	LoadListConfig(pzmc);
}

// ɾ��һ������
void CParamConfig4::OnBnClickedButtonListDeleteOne()
{
	CString PZMC, CARDNO;
	m_ComboBox_List.GetWindowText(PZMC);
	GetDlgItemText(IDC_EDIT_LIST_1, CARDNO);

	MySQLInterface uMySQL;
	if(!IsExistName(PZMC, CARDNO, uMySQL))
	{
		AfxMessageBox("ָ�����������������ڣ�");
		uMySQL.Close();
		return;
	}

	CString strsql = "DELETE FROM listconfig ";
	strsql += "WHERE PZMingCheng = '" + PZMC + "' ";
	strsql += "AND Cardno = '" + CARDNO + "' ;";

	std::string QueryStr(strsql.GetBuffer());
	if(uMySQL.Query(QueryStr) == false)
	{
		AfxMessageBox("ɾ��һ������ʧ�ܣ�");
		uMySQL.Close();
		return;
	}
	uMySQL.Close();
	std::string pzmc(PZMC.GetBuffer());
	LoadListConfig(pzmc);
	MessageBox("ɾ��һ�������ɹ���", "��ʾ", MB_ICONINFORMATION);
}

void CParamConfig4::OnBnClickedButtonListDelete()
{
	MySQLInterface uMySQL;
	CString TempStr;
	m_ComboBox_List.GetWindowText(TempStr);
	std::string str(TempStr.GetBuffer());
	if(!IsExist(str, "PZMingCheng", "listconfig", uMySQL))
    {
		MessageBox("ָ�����������������ڣ�", "��ʾ", MB_ICONWARNING);
		uMySQL.Close();
        return;
    }
	if(IDCANCEL == MessageBox("ȷ��ɾ����ѡ������������", "ɾ��ȷ��", MB_OKCANCEL | MB_ICONQUESTION))
	{
		uMySQL.Close();
        return;
	}
	std::string strsql = "DELETE FROM listconfig WHERE PZMingCheng = '" + str + "';";
	if(uMySQL.Query(strsql) == false)
	{
		AfxMessageBox("ɾ��ʧ�ܣ�");
		uMySQL.Close();
		return;
	}
	uMySQL.Close();
    pSubDlg7->InitListComboBox();
	SetDlgItemText(IDC_EDIT_LIST_1, "");
	CString PZMC;
	m_ComboBox_List.GetWindowText(PZMC);
	std::string pzmc(PZMC.GetBuffer());
	LoadListConfig(pzmc);
	MessageBox("ɾ���ɹ���", "��ʾ", MB_ICONINFORMATION);
}

void CParamConfig4::OnBnClickedButtonLisAdd()
{
	OnBnClickedButtonListAddOne();
}

// �������óɹ���������
void CParamConfig4::OnBnClickedButtonListResetCnt()
{
	m_ListSuccessCount = 0;
	SetDlgItemText(IDC_EDIT_LIST_3, ToString(m_ListSuccessCount));
}
// ͬ��������Ͽ�
void CParamConfig4::OnCbnSelchangeComboList()
{
	CString TempStr;
	int nSel = m_ComboBox_List.GetCurSel();    
    m_ComboBox_List.GetLBText(nSel, TempStr);
	pSubDlg7->m_ComboBox_List.SetWindowText(TempStr);
}

// ��ʼ�������ð�ť
void CParamConfig4::OnBnClickedButtonListConfig()
{
	if( !pMainDlg->m_bIsOpenSerl )
	{
		MessageBox("���ȴ򿪴��ڣ�", "��ʾ", MB_ICONWARNING);
		return;
	}
	if( m_NameList.GetItemText(0, 1).IsEmpty() )
	{
		MessageBox("�뵼�����������ļ���", "��ʾ", MB_ICONWARNING);
		return;
	}
	int CHECK_TY = ( ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_CFG_1 ) ) )->GetCheck( );
	int CHECK_2M = ( ( CButton* )( pSubDlg4->GetDlgItem( IDC_RADIO_CFG_2 ) ) )->GetCheck( );
	if( FALSE ==  CHECK_TY && FALSE == CHECK_2M )
	{
		AfxMessageBox("����ѡ���������ð汾��");
		return;
	}
	if(IDCANCEL == MessageBox("�����µĿ���Ϣ��ԭ�еĿ����ݽ������ȷ����", "��ʾ", MB_OKCANCEL | MB_ICONQUESTION))
        return;

	( ( CButton* )( GetDlgItem( IDC_BUTTON_LIST_7 ) ) )->EnableWindow( FALSE );

	if( CHECK_TY == TRUE)			// ����ͨ�ð汾���������߳�
	{
		if(m_pSetListThread)
		{
			::TerminateThread(m_pSetListThread->m_hThread, 0);
			m_pSetListThread = NULL;
		}
		m_pSetListThread = AfxBeginThread(SetListThread, this);
	}
	else if( CHECK_2M == TRUE)		// ����2M�汾���������߳�
	{
		if(m_pSetListThread2M)
		{
			::TerminateThread(m_pSetListThread2M->m_hThread, 0);
			m_pSetListThread2M = NULL;
		}
		m_pSetListThread2M = AfxBeginThread(SetListThread2M, this);
	}
	if (NULL == m_processBar)   
    {    
        m_processBar = new CProcessBar();   
        m_processBar->Create(IDD_DIALOG_BAR, this);  
    }
	// ���ý�������ʾ
	m_processBar->m_Bar.SetRange(0, m_ListCount);
	m_processBar->m_maxRange = m_ListCount;
    m_processBar->ShowWindow(SW_SHOW); 
}

// ��ʼͨ�����������߳�
UINT CParamConfig4::SetListThread(LPVOID pParam)
{
	CButton* pButton = ( CButton* )( pSubDlg4->GetDlgItem( IDC_BUTTON_LIST_7 ));
	// ���������
	CProtocolHandle ComProto;
	BYTE RecvBuffer[PACKET_SIZE] = {0};
	BYTE SendData[PACKET_SIZE]   = {0};
	int length = ComProto.Package(0x38, NULL, 0);
	pMainDlg->is2MPacket = false;
	pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// ��������
	WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// �ȴ����ڽ������һ֡����
	if(pMainDlg->m_bRecvPacketTail == false)						// ����־λ ����3��û�յ���β
	{
		pButton->EnableWindow( TRUE );
		AfxMessageBox("��������ʧ�ܣ�");
		return FALSE;
	}
	int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
	RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));
	if(FALSE == ComProto.isVaildPacket(0x38, RecvBuffer, RecvBufLen))
	{
		pButton->EnableWindow( TRUE );
		AfxMessageBox("��������ʧ�ܣ�");
		return FALSE;
	}

	// ����������
	unsigned int cnt = pSubDlg4->m_ListCount;
	for(unsigned int i = 0; i < cnt; i++)
	{
		ComProto.Clear();
		memset(RecvBuffer, 0, PACKET_SIZE);
		memset(SendData,   0, PACKET_SIZE);

		CString CardnoStr = pSubDlg4->m_NameList.GetItemText(i, 1);
		// ע��������±��ǵ���
		SendData[3] = ((AscToHex(CardnoStr[0]) << 4) + AscToHex(CardnoStr[1]));
		SendData[2] = ((AscToHex(CardnoStr[2]) << 4) + AscToHex(CardnoStr[3]));
		SendData[1] = ((AscToHex(CardnoStr[4]) << 4) + AscToHex(CardnoStr[5]));
		SendData[0] = ((AscToHex(CardnoStr[6]) << 4) + AscToHex(CardnoStr[7]));
		TRACE("%02X %02X %02X %02X\n", SendData[3], SendData[2], SendData[1], SendData[0]);

		int length = ComProto.Package(0x36, SendData, 4);
		pMainDlg->is2MPacket = false;
		pMainDlg->FSerialSend(ComProto.SendPacket, ComProto.SendLen);	// ��������
		WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// �ȴ����ڽ������һ֡����
		if(pMainDlg->m_bRecvPacketTail == false)						// ����־λ ����3��û�յ���β
		{
			pButton->EnableWindow( TRUE );
			AfxMessageBox("��������ʧ�ܣ�");
			return FALSE;
		}
		RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
		RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));
		if(FALSE == ComProto.isVaildPacket(0x36, RecvBuffer, RecvBufLen))
		{
			pButton->EnableWindow( TRUE );
			AfxMessageBox("��������ʧ�ܣ�");
			return FALSE;
		}
		pSubDlg4->m_processBar->UpdateBar(i+1);
		pSubDlg4->m_ListSuccessCount++;
		pSubDlg4->SetDlgItemText(IDC_EDIT_LIST_3, ToString(pSubDlg4->m_ListSuccessCount));
	}
	Sleep(300);
	pButton->EnableWindow( TRUE );
	pSubDlg4->MessageBox("���������ɹ���", "��ʾ", MB_ICONINFORMATION);
	return TRUE;
}

// ��ʼ2M���������߳�
UINT CParamConfig4::SetListThread2M(LPVOID pParam)
{
	CButton* pButton = ( CButton* )( pSubDlg4->GetDlgItem( IDC_BUTTON_LIST_7 ));
	// ���������
	BYTE SendData[PACKET_SIZE] = {0xF1, 0xE4, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00};
	BYTE RecvBuffer[PACKET_SIZE] = {0};
	BYTE Packet[PACKET_SIZE] = {0};
	CProtocolHandle ComProto;
	int length = ComProto.Package2M(0x21, 0x01, 0x80, 0x49, SendData, 8, Packet);
	pMainDlg->is2MPacket = true;
	pMainDlg->FSerialSend(Packet, length);							// ��������

	WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// �ȴ����ڽ������һ֡����
	if(pMainDlg->m_bRecvPacketTail == false)						// ����־λ ����3��û�յ���β
	{
		pButton->EnableWindow( TRUE );
		AfxMessageBox("2M�ڰ���������ʧ�ܣ�");
		return FALSE;
	}
	int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
	RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));
	if(false == ComProto.isVaildAck2M(RecvBuffer, RecvBufLen))
	{
		pButton->EnableWindow( TRUE );
		AfxMessageBox("2M�ڰ���������ʧ�ܣ�");
		return FALSE;
	}
	// ����������
	unsigned int cnt = pSubDlg4->m_ListCount;
	CString DateStr;   pSubDlg4->m_DateTime.GetWindowText(DateStr);
	unsigned int sel = pSubDlg4->m_ComboBox_WorkList.GetCurSel();
	for(unsigned int i = 0; i < cnt; i++)
	{
		ComProto.Clear();
		memset(RecvBuffer, 0, PACKET_SIZE);
		memset(SendData,   0, PACKET_SIZE);
		memset(Packet,     0, PACKET_SIZE);

		CString CardnoStr = pSubDlg4->m_NameList.GetItemText(i, 1);

		SendData[0] = 0xF1;  SendData[1] = 0xE3;  SendData[2] = 0x00; 
		SendData[3] = ((AscToHex(CardnoStr[0]) << 4) + AscToHex(CardnoStr[1]));
		SendData[4] = ((AscToHex(CardnoStr[2]) << 4) + AscToHex(CardnoStr[3]));
		SendData[5] = ((AscToHex(CardnoStr[4]) << 4) + AscToHex(CardnoStr[5]));
		SendData[6] = ((AscToHex(CardnoStr[6]) << 4) + AscToHex(CardnoStr[7]));
		SendData[7] = 0x00;  SendData[8] = 0x00;  SendData[9] = 0x00; 
		SendData[10] = 0x01;  SendData[11] = 0x12;  SendData[12] = 0x34; 
		SendData[13] = ((AscToHex(DateStr[0]) << 4) + AscToHex(DateStr[1]));
		SendData[14] = ((AscToHex(DateStr[2]) << 4) + AscToHex(DateStr[3]));
		SendData[15] = ((AscToHex(DateStr[6]) << 4) + AscToHex(DateStr[7]));
		SendData[16] = ((AscToHex(DateStr[9]) << 4) + AscToHex(DateStr[10]));
		if(sel == 0)	 SendData[17] = 0x00;
		else if(sel == 1)SendData[17] = 0x01;
		else if(sel == 2)SendData[17] = 0x02;
		else if(sel == 3)SendData[17] = 0x03;
		else if(sel == 4)SendData[17] = 0x04;

		int length = ComProto.Package2M(0x21, 0x01, 0x80, 0x49, SendData, 18, Packet);
		pMainDlg->FSerialSend(Packet, length);	
		WaitForSingleObject(pMainDlg->m_hSemaphore, 3000);				// �ȴ����ڽ������һ֡����
		if(pMainDlg->m_bRecvPacketTail == false)						// ����־λ ����3��û�յ���β
		{
			pButton->EnableWindow( TRUE );
			AfxMessageBox("2M�ڰ���������ʧ�ܣ�");
			return FALSE;
		}
		int RecvBufLen = RingBufferLen(&(pMainDlg->m_RecvBuf));
		RingBufferRead(RecvBuffer, RecvBufLen, &(pMainDlg->m_RecvBuf));
		if(false == ComProto.isVaildAck2M(RecvBuffer, RecvBufLen))
		{
			pButton->EnableWindow( TRUE );
			AfxMessageBox("2M�ڰ���������ʧ�ܣ�");
			return FALSE;
		}
		pSubDlg4->m_processBar->UpdateBar(i+1);
		pSubDlg4->m_ListSuccessCount++;
		pSubDlg4->SetDlgItemText(IDC_EDIT_LIST_3, ToString(pSubDlg4->m_ListSuccessCount));
	}
	Sleep(300);
	pButton->EnableWindow( TRUE );
	pSubDlg4->MessageBox("���������ɹ���", "��ʾ", MB_ICONINFORMATION);
	return TRUE;
}