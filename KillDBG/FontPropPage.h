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

	static int CALLBACK FontCallback( CONST LOGFONT* pFont, CONST TEXTMETRIC *, DWORD, LPARAM lParam);
	void FontCallback(const LOGFONT* pFont);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_FontList;
};
