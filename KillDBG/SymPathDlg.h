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
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CEdit m_editSymPath;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonAddPath();

	CString m_strSymPaths;
};
