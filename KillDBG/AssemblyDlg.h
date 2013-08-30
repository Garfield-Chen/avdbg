#pragma once
#include "afxwin.h"


// CAssemblyDlg �Ի���

class CAssemblyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAssemblyDlg)

public:
	CAssemblyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAssemblyDlg();

// �Ի�������
	enum { IDD = IDD_ASSEMBLY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
private:
	afx_msg void OnEnChangeEditAsm();
	CComboBox m_cmbOpcode;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

	byte m_OrgOpcode[16];
	byte m_NewOpcode[16];
	int m_NewOpcSize;
	DWORD m_dwAddress;
};
