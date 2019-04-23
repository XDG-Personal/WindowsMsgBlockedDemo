
// MsgBlocked_Caller.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMsgBlockedCallerApp:
// See MsgBlocked_Caller.cpp for the implementation of this class
//

class CMsgBlockedCallerApp : public CWinApp
{
public:
	CMsgBlockedCallerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMsgBlockedCallerApp theApp;
