#pragma once


// CFollowAddressDlg �Ի���

class CFollowAddressDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFollowAddressDlg)

public:
	CFollowAddressDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFollowAddressDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_FLOADDR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	DWORD m_dwAddr;
	virtual BOOL OnInitDialog();
};
