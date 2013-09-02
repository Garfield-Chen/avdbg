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
}


BEGIN_MESSAGE_MAP(CSymPathDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSymPathDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADD_PATH, &CSymPathDlg::OnBnClickedButtonAddPath)
END_MESSAGE_MAP()


// CSymPathDlg ��Ϣ�������


void CSymPathDlg::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDIT_SYMBOL_PATH,m_strSymPaths);
	m_bReload = m_Reload.GetCheck();
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
