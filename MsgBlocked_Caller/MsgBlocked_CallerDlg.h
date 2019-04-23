
// MsgBlocked_CallerDlg.h : header file
//

#pragma once


// CMsgBlockedCallerDlg dialog
class CMsgBlockedCallerDlg : public CDialogEx
{
// Construction
public:
	CMsgBlockedCallerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MSGBLOCKED_CALLER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
