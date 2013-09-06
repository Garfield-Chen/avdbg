// SymPathDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SymPathDlg.h"
#include "afxdialogex.h"


// CSymPathDlg �Ի���

IMPLEMENT_DYNAMIC(CSymPathDlg, CDialogEx)

CSymPathDlg::CSymPathDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSymPathDlg::IDD, pParent)
{

}

CSymPathDlg::~CSymPathDlg()
{
}

void CSymPathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_RELOAD_SYMBOL, m_Reload);
	DDX_Control(pDX, IDC_CHECK_AUTODOWNLOAD, m_AutoDownChk);
	DDX_Control(pDX, IDC_EDIT_AUTODOWN_SYMBOL_PATH, m_AutoDownEdit);
	DDX_Control(pDX, IDC_BUTTON_AUTODOWN_SYMBOL_PATH, m_AutoDownButton);
}


BEGIN_MESSAGE_MAP(CSymPathDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSymPathDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADD_PATH, &CSymPathDlg::OnBnClickedButtonAddPath)
	ON_BN_CLICKED(IDC_BUTTON_AUTODOWN_SYMBOL_PATH, &CSymPathDlg::OnBnClickedButtonAutodownSymbolPath)
	ON_BN_CLICKED(IDC_CHECK_AUTODOWNLOAD, &CSymPathDlg::OnBnClickedCheckAutodownload)
END_MESSAGE_MAP()


// CSymPathDlg ��Ϣ�������


void CSymPathDlg::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDIT_SYMBOL_PATH,m_strSymPaths);
	m_bReload = m_Reload.GetCheck();

	if (m_AutoDownChk.GetCheck())
	{
		CString strAutoPath;
		if (GetDlgItemText(IDC_EDIT_AUTODOWN_SYMBOL_PATH,strAutoPath) == 0)
		{
			MessageBox("�������Զ����ط��ŵı���·����");
			return;
		}

		if (m_strSymPaths.GetLength() != 0 && m_strSymPaths.GetAt(m_strSymPaths.GetLength()-1) != ';')
		{
			m_strSymPaths += ";";
		}

		m_strSymPaths += "SRV*";
		m_strSymPaths += strAutoPath;
		m_strSymPaths += "*http://msdl.microsoft.com/download/symbols";
	}
	CDialogEx::OnOK();
}


void CSymPathDlg::OnBnClickedButtonAddPath()
{
	char szPath[MAX_PATH] = {0};     //���ѡ���Ŀ¼·�� 

	BROWSEINFO bi;   
	bi.hwndOwner = m_hWnd;   
	bi.pidlRoot = NULL;   
	bi.pszDisplayName = szPath;   
	bi.lpszTitle = "��ѡ������ļ����ڵ�Ŀ¼��";
	bi.ulFlags = 0;   
	bi.lpfn = NULL;   
	bi.lParam = 0;   
	bi.iImage = 0;   
	//����ѡ��Ŀ¼�Ի���
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);   

	if(lp && SHGetPathFromIDList(lp, szPath))   
	{
		CString str;
		GetDlgItemText(IDC_EDIT_SYMBOL_PATH,str);
		str += szPath;
		str += ";";
		SetDlgItemText(IDC_EDIT_SYMBOL_PATH,str);
	}
}


void CSymPathDlg::OnBnClickedButtonAutodownSymbolPath()
{
	char szPath[MAX_PATH] = {0};     //���ѡ���Ŀ¼·�� 

	BROWSEINFO bi;   
	bi.hwndOwner = m_hWnd;   
	bi.pidlRoot = NULL;   
	bi.pszDisplayName = szPath;   
	bi.lpszTitle = "��ѡ������ļ����ص���Ŀ¼��";   
	bi.ulFlags = 0;   
	bi.lpfn = NULL;   
	bi.lParam = 0;   
	bi.iImage = 0;   
	//����ѡ��Ŀ¼�Ի���
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if(lp && SHGetPathFromIDList(lp, szPath))   
	{
		SetDlgItemText(IDC_EDIT_AUTODOWN_SYMBOL_PATH,szPath);
	}
}


void CSymPathDlg::OnBnClickedCheckAutodownload()
{
	if (m_AutoDownChk.GetCheck())
	{
		m_AutoDownEdit.EnableWindow();
		m_AutoDownButton.EnableWindow();
		return;
	}

	m_AutoDownEdit.EnableWindow(FALSE);
	m_AutoDownButton.EnableWindow(FALSE);
}


BOOL CSymPathDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_AutoDownEdit.EnableWindow(FALSE);
	m_AutoDownButton.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
