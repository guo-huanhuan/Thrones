// Download by http://www.codefans.net
// getmap.cpp : implementation file
//

#include "stdafx.h"
#include "真的打呀.h"
#include "getmap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CString getdir;
extern CString getfile;
/////////////////////////////////////////////////////////////////////////////
// getmap dialog


getmap::getmap(CWnd* pParent /*=NULL*/)
	: CDialog(getmap::IDD, pParent)
{
	//{{AFX_DATA_INIT(getmap)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void getmap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(getmap)
	DDX_Control(pDX, IDC_COMBO1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(getmap, CDialog)
	//{{AFX_MSG_MAP(getmap)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// getmap message handlers

void getmap::OnCancel() 
{	getdir="";
	CDialog::OnCancel();
}
void getmap::OnButton1() 
{	getdir="end";
	CDialog::OnCancel();	
}

void getmap::OnOK() 
{	GetDlgItemText(IDC_COMBO1, getfile);
	CDialog::OnOK();
}

BOOL getmap::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	char appdir[256];
	GetCurrentDirectory(256,appdir);
		 CString cc;
		 cc=appdir;
		 if(cc.Right(8)=="运行程序")
			cc="地图";
		 else	
		 cc="../运行程序/地图";	//图片路径
	getdir.Format("%s",cc);
	findfile0(getdir,"*.dat");//编历文件
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
///////////////////////////////////////////////////////////
//功能:编历文件
//入口:DirName目录名,ext文件名
//出口:p 符合条件的文件个数
///////////////////////////////////////////////////////////
int getmap::findfile0(CString DirName,CString ext)//编历文件
{	WIN32_FIND_DATA	FindFileData;
	HANDLE hFindFile;
	SetCurrentDirectory(DirName);			//设置当前目录
	m_list.ResetContent();					//清除列表框
	hFindFile=FindFirstFile(ext,&FindFileData);
	CString tFile;
	int p=0;
	if (hFindFile!=INVALID_HANDLE_VALUE)
	{	do	{tFile=FindFileData.cFileName;
			 if ((tFile==".")||(tFile=="..")) continue;
			 if (!(FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY))
				{	m_list.AddString(tFile);//将符合条件的文件名加入列表框
					p++;
				}
			}
		while (FindNextFile(hFindFile,&FindFileData));
	}
	FindClose(hFindFile);
	return p;
}

