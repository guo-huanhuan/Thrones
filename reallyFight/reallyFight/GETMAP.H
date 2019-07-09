#if !defined(AFX_GETMAP_H__DFEBE449_F8A5_46F0_AF2D_0BC89BF3D161__INCLUDED_)
#define AFX_GETMAP_H__DFEBE449_F8A5_46F0_AF2D_0BC89BF3D161__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// getmap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// getmap dialog

class getmap : public CDialog
{
// Construction
public:
	getmap(CWnd* pParent = NULL);   // standard constructor
	setmap(CWnd* pParent = NULL);   // standard constructor
	int findfile0(CString DirName,CString ext);//±àÀúÎÄ¼þ
// Dialog Data
	//{{AFX_DATA(getmap)
	enum { IDD = IDD_DIALOG1 };
	CComboBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(getmap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(getmap)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETMAP_H__DFEBE449_F8A5_46F0_AF2D_0BC89BF3D161__INCLUDED_)
