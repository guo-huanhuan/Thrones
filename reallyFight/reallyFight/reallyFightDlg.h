// ��Ĵ�ѽDlg.h : header file
//

#if !defined(AFX_DLG_H__A0A7CBCB_22CD_42DA_A224_3027B74C3B05__INCLUDED_)
#define AFX_DLG_H__A0A7CBCB_22CD_42DA_A224_3027B74C3B05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

#include "DX��Ϸ���/game_Ѱ·.h"
class CMyDlg : public CDialog
{
// Construction
public:
	CMyDlg(CWnd* pParent = NULL);	// standard constructor
/////////////////////////////////////////////////////////////
	gamepro	m_game;	//�����������---------------
	int		tim;	//ˢ��ʱ��
	CRect lpRect;
	int		down,dowx,dowy;//�������־������
	int		fidtim;	//Ѱ·ʱ��
	int		no;		//����ѡ���
	HCURSOR m_Cur;	//��ǰ���
	HWND	hMCI;
	void setsmz(int h,int a);
/////////////////////////////////////////////////////////////
// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	afx_msg void OnMove(int x, int y);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__A0A7CBCB_22CD_42DA_A224_3027B74C3B05__INCLUDED_)
