#pragma once
#include "afxwin.h"


// CSymPathDlg �Ի���

class CSymPathDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSymPathDlg)

public:
	CSymPathDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSymPathDlg();

// �Ի�������
	enum { IDD = IDD_SYMBOL_SEARCH_PATHS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CButton m_Reload;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonAddPath();

	CString m_strSymPaths;
	BOOL m_bReload;
};
