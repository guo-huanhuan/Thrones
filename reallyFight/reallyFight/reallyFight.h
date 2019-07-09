// 真的打呀.h : main header file for the 真的打呀 application
//
// Download by http://www.codefans.net
#if !defined(AFX__H__BE1E6F56_ADAE_4754_9454_24FF3D113F9D__INCLUDED_)
#define AFX__H__BE1E6F56_ADAE_4754_9454_24FF3D113F9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyApp:
// See 真的打呀.cpp for the implementation of this class
//

class CMyApp : public CWinApp
{
public:
	CMyApp();
	HCURSOR m_Cur0;//  光标变量
	HCURSOR m_Cur1;//许光标变量
	HCURSOR m_Cur2;//枪光标变量
	HCURSOR m_Cur3;//禁光标变量
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__H__BE1E6F56_ADAE_4754_9454_24FF3D113F9D__INCLUDED_)
