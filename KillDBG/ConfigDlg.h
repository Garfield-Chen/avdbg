#pragma once
#include "afxcmn.h"
#include "FontPropPage.h"
#include "AppConfig.h"


// CConfigDlg �Ի���

class CConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConfigDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	CTabCtrl m_Tab;
	afx_msg void OnBnClickedOk();
	afx_msg void OnTcnSelchangeTabConfig(NMHDR *pNMHDR, LRESULT *pResult);
	CFontPropPage m_FontPage;

public:
	virtual BOOL OnInitDialog();
};
