// ��Ĵ�ѽ.cpp : Defines the class behaviors for the application.
//// Download by http://www.codefans.net

#include "stdafx.h"
#include "��Ĵ�ѽ.h"
#include "��Ĵ�ѽDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyApp

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
	//{{AFX_MSG_MAP(CMyApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyApp construction

CMyApp::CMyApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMyApp object

CMyApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMyApp initialization

BOOL CMyApp::InitInstance()
{
	AfxEnableControlContainer();
	HANDLE hMutex=CreateMutex(NULL,FALSE,"��Ĵ�ѽ");//��ֹ��ϵͳ��������
	if(hMutex==NULL||ERROR_ALREADY_EXISTS==::GetLastError()) return FALSE;
/////////////////////////////////////////////////////////////
	m_Cur0 = LoadCursor(IDC_CURSOR0);//��  ���
	if (!m_Cur0) return FALSE;
	m_Cur1 = LoadCursor(IDC_CURSOR1);//������
	if (!m_Cur1) return FALSE;
	m_Cur2 = LoadCursor(IDC_CURSOR2);//��ǹ���
	if (!m_Cur2) return FALSE;
	m_Cur3 = LoadCursor(IDC_CURSOR3);//�������
	if (!m_Cur3) return FALSE;

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CMyDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
