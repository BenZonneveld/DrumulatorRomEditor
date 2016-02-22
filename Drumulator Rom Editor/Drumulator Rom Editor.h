// Drumulator Rom Editor.h : main header file for the Drumulator Rom Editor application
//
#pragma once


#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

// CDrumulatorRomEditorApp:
// See Drumulator Rom Editor.cpp for the implementation of this class
//

class CDrumulatorRomEditorApp : public CWinApp
{
public:
	CDrumulatorRomEditorApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnViewAssignsounds();
};

extern CDrumulatorRomEditorApp theApp;
