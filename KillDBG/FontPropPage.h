#pragma once
#include "afxwin.h"


// CFontPropPage �Ի���

class CFontPropPage : public CDialogEx
{
	DECLARE_DYNAMIC(CFontPropPage)

public:
	CFontPropPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFontPropPage();

// �Ի�������
	enum { IDD = IDD_FORMVIEW_FONT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonChoosememviewFont();

	LOGFONT m_AsmViewFont;
	LOGFONT m_MemViewFont;

	afx_msg void OnBnClickedButtonChooseDasmFont();
};
