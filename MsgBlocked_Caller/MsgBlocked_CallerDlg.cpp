
// MsgBlocked_CallerDlg.cpp : implementation file
//
#include "stdafx.h"

#include "afxdialogex.h"

#include "MsgBlocked_Caller.h"

#include "MsgBlocked_CallerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMsgBlockedCallerDlg dialog

CMsgBlockedCallerDlg::CMsgBlockedCallerDlg(CWnd *pParent /*=nullptr*/)
	: CDialogEx(IDD_MSGBLOCKED_CALLER_DIALOG, pParent){
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMsgBlockedCallerDlg::DoDataExchange(CDataExchange *pDX){
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMsgBlockedCallerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXECUTE,
				  &CMsgBlockedCallerDlg::OnBnClickedButtonExecute)
	ON_BN_CLICKED(IDC_BUTTON_EXECUTE_1, &CMsgBlockedCallerDlg::OnBnClickedButtonExecute1)
END_MESSAGE_MAP()

// CMsgBlockedCallerDlg message handlers

BOOL CMsgBlockedCallerDlg::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);  // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

	// TODO: Add extra initialization here

	return TRUE; // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMsgBlockedCallerDlg::OnPaint(){
	if(IsIconic()){
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()),
					0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user
// drags
//  the minimized window.
HCURSOR CMsgBlockedCallerDlg::OnQueryDragIcon(){
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD ExcuteProcess(TCHAR *command, UINT cmdShow, int timeout, int method, bool isblock = false){
	PROCESS_INFORMATION process_info;
	STARTUPINFO si;
	BOOL ret = FALSE;
	DWORD flags = CREATE_NO_WINDOW;

	SECURITY_ATTRIBUTES sa = {sizeof(sa), NULL, TRUE};
	SECURITY_ATTRIBUTES *psa = NULL;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	psa = &sa;

	ZeroMemory(&process_info, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags |= STARTF_USESTDHANDLES;
	si.wShowWindow = cmdShow;
	si.hStdInput = NULL;
	si.hStdError = NULL;
	si.hStdOutput = NULL;

	ret = CreateProcess(NULL, command, NULL, NULL, TRUE, flags, NULL, NULL, &si,
						&process_info);

	if(method == 0){
		WaitForSingleObject(process_info.hProcess,
							-1 == timeout ? INFINITE : timeout);
	}
	else{
		while(TRUE){
			MSG msg;
			DWORD result = MsgWaitForMultipleObjects(1, &process_info.hProcess,
													 FALSE, -1 == timeout ? INFINITE : timeout, QS_ALLINPUT);

			if(result == (WAIT_OBJECT_0))
				break;
			else if(result == (WAIT_TIMEOUT))
				break;
			else{
				PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
				if(!isblock)
					DispatchMessage(&msg);
			}
		}

	}

	CloseHandle(process_info.hProcess);
	CloseHandle(process_info.hThread);

	return ret;
}

void CMsgBlockedCallerDlg::OnBnClickedButtonExecute(){
	ExcuteProcess("MsgBlocked_Host.exe", SW_NORMAL, -1, 0);
}


void CMsgBlockedCallerDlg::OnBnClickedButtonExecute1(){
	ExcuteProcess("MsgBlocked_Host.exe", SW_NORMAL, -1, 1, true);
}
