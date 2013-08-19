// FollowAddressDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FollowAddressDlg.h"
#include "afxdialogex.h"


// CFollowAddressDlg �Ի���

IMPLEMENT_DYNAMIC(CFollowAddressDlg, CDialogEx)

CFollowAddressDlg::CFollowAddressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFollowAddressDlg::IDD, pParent)
{

}

CFollowAddressDlg::~CFollowAddressDlg()
{
}

void CFollowAddressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFollowAddressDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFollowAddressDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFollowAddressDlg ��Ϣ�������


void CFollowAddressDlg::OnBnClickedOk()
{
	char szAddr[10];
	GetDlgItemText(IDC_EDIT_ADDR,szAddr,9);
	sscanf(szAddr,"%08x",&m_dwAddr);
	CDialogEx::OnOK();
}


BOOL CFollowAddressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_EDIT_ADDR)->SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
