// 真的打呀Dlg.cpp : implementation file
/*********************************
[学VC编游戏]
编著、程序设计：唐明理 2004.7
E-mail:  cqtml@163.com
**********************************/
#include "stdafx.h"
#include "真的打呀.h"
#include "真的打呀Dlg.h"
#include "getmap.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CString getdir;
CString getfile;
HDC HDC0;
gamepro	m_game;	//定义类调用名---------------
int		tim;	//刷屏时间
CRect lpRect;
/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog
// Download by http://www.codefans.net
CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()//对话框程序的初始入口,[MFC自动产生]
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon	
	// TODO: Add extra initialization here
////////////////////////////////////////////////////////////////////////////////
	m_game.initmap();		//初始化类
	m_game.loaddata();		//调资源包............................
	fidtim=0;				//寻路时间
	down=0;dowx=0;dowy=0;	//左键按键清0
	MoveWindow(0,0,SCRWI,SCRHE);//窗口定位
	CenterWindow();			//居中窗口
//--------------------------------------------------------------------
	CString str="    这是《学VC、编游戏》的第十个示例\r\n";
	str+="在这一章，我们使用了以下知识、技术。\r\n";
	str+="1．对象的新属性：生命值、攻击力。\r\n";
	str+="2．对象生命值的显示。\r\n";
	str+="3．打斗时生命值的改变。\r\n";
	str+="4．在场景中添加物品。\r\n";

	str+="\r\n=======================\r\n";
	str+="   操作方法\r\n\r\n";
	str+="A、在场景内点任意点，指挥主角移动。\r\n";
	str+="B、将鼠标移到场景外，可以移动地图。\r\n";
	str+="C、在微缩地图上点一下，可以快速定位。\r\n";
	str+="D、ESC键，退出游戏。\r\n\r\n";
	str+="你可以指挥主角去打猎了。\r\n";
	GetDlgItem(IDC_EDIT1)->MoveWindow
		( m_game.mapl,m_game.maph+80,m_game.mapw,300,TRUE);
	SetDlgItemText(IDC_EDIT1, str);
//................................................................
	GetDlgItem(IDC_STATIC0)->MoveWindow( 0,8,WIDTH+4,HEIGHT+4,TRUE);
	GetDlgItem(IDC_STATIC1)->MoveWindow
		( m_game.mapl-2,m_game.mapt-2,m_game.mapw+4,m_game.maph+4,TRUE);
	GetDlgItem(IDC_STATIC2)->MoveWindow
		( m_game.mapl,m_game.maph+20,m_game.mapw,30,TRUE);
	GetDlgItem(IDOK)->MoveWindow
		( m_game.mapl,m_game.maph+55,m_game.mapw,25,TRUE);//调地图
	GetDlgItem(IDC_STATIC3)->MoveWindow(2,600-26,260,18,TRUE);		//提示
	GetDlgItem(IDC_STATIC4)->MoveWindow(2+265,600-26,270,18,TRUE);	//时间
	GetDlgItem(IDC_STATIC5)->MoveWindow(2+270*2,600-26,250,18,TRUE);//坐标

	GetDlgItem(IDC_STATIC7)->MoveWindow(3,  552,50,16,TRUE);//生命
	GetDlgItem(IDC_STATIC8)->MoveWindow(600,552,50,16,TRUE);//经验

	GetDlgItem(IDC_STATIC9)-> MoveWindow(250,502,150,16,TRUE);//金钱
	GetDlgItem(IDC_STATIC10)->MoveWindow(250,522,150,16,TRUE);//食物
//在状态栏隐藏对话框==============================
	DWORD dwExStyle=GetExStyle();
	dwExStyle =(~WS_EX_APPWINDOW & dwExStyle) | WS_EX_TOOLWINDOW;
	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,dwExStyle);
//================================================
    SetTimer(3,100,NULL);
////////////////////////////////////////////////////////////////////////////////	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
	else
	{
		CDialog::OnPaint();
	}
	GetWindowRect(&lpRect);
}

HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyDlg::OnCancel() //退出,[类向导中定义生成]
{	KillTimer(1);
	KillTimer(2);
	MCIWndStop(hMCI);
	if( ::MessageBox(GetSafeHwnd(), "退出程序吗?","请您确定!",
					MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2  ) == IDYES )
	{m_game.FreeDDraw();//释放所有的DirectDraw对象。
	 m_game.exit();		//退出类
	 CDialog::OnCancel();
	}
	else 
	{SetTimer(1,TIMER,NULL);
	 SetTimer(2,1000,NULL);
	 MCIWndPlay(hMCI);
	}
}

void CMyDlg::OnTimer(UINT nIDEvent) //时钟函数,[类向导中定义生成]
{////////////////////////////////////////////////////////////////////////////////////
	if(nIDEvent==1)//动画刷屏
	{tim=timeGetTime();			//开始时间
	 CClientDC dc(this);
	 m_game.mlmap();			//地图块移动拼接
	 int i;
	 for(i=0;i<m_game.rs;i++) 
		{m_game.Alphasetobj(i,0);	//对象显示
		}
	 for(i=0;i<m_game.rs;i++) 
		{m_game.Alphasetobj(i,1);	//对象显示
		 m_game.lookit(i);	//角色碰撞
		}
	 m_game.Bk1ToPr(dc.m_hDC,lpRect);//主缓存页面到主页面
	 if(m_game.rs>0)	m_game.smlmap(dc.m_hDC);//数据调入后,显示小地图
	 tim=timeGetTime()-tim;		//显示时间=结束时间-开始时间
	}
	if(nIDEvent==2)//显示信息
	{char cc[255],c1[255];
	 int q=m_game.mann;
	 if(m_game.man[q].smz<-5) //人倒，开始计时。
	 {KillTimer(1);KillTimer(2);
	  MCIWndStop(hMCI);
	  AfxMessageBox("你牺牲了! 游戏结束。");
	  OnOK();
	 }
	 setsmz(m_game.man[q].smz,0);
	 setsmz(m_game.mansmz[1],1);
	 sprintf(cc,"金钱:%d",m_game.mansmz[2]);
	 SetDlgItemText(IDC_STATIC9,cc);
	 sprintf(cc,"食物:%d",m_game.mansmz[3]);
	 SetDlgItemText(IDC_STATIC10,cc);

	 sprintf(cc,"地图[X:%4d Y:%4d] 人[x:%4d y:%4d]",
		m_game.scrx,m_game.scry,m_game.man[q].xix,m_game.man[q].xiy);
	 SetDlgItemText(IDC_STATIC5, cc);
	 sprintf(cc,"[显示区对象数:%3d] [%3dms/屏] [CPU占用%3d％]",m_game.mans,tim,tim*100/TIMER);
	 SetDlgItemText(IDC_STATIC4, cc);
	 switch(fidtim)
	 {case -1:	{strcpy(c1,"障碍点");	break;}
	  case -2:	{strcpy(c1,"起始点");	break;}
	  case -3:	{strcpy(c1,"无路");		break;}
	  case -4:	{strcpy(c1,"搜索忙");	break;}
	  case -5:	{strcpy(c1,"太远了");	break;}
	  case -10:	{strcpy(c1,"左上边界");	break;}
	  case -20:	{strcpy(c1,"右下边界");	break;}
	  default:	{sprintf(c1,"搜索:%dms",fidtim);}
	 }
	 sprintf(cc,"地图%dX%d 障碍%dX%d %s,%d",
		        WIDTH*m_game.SCRP0,HEIGHT*m_game.SCRP0,
				WIDTH*m_game.SCRP0/GX,HEIGHT*m_game.SCRP0/GY,c1,m_game.man[q].pk);
	 SetDlgItemText(IDC_STATIC3, cc);
	 m_game.randxy();//随机产生兽的移动目标
	 if(MCIWndGetPosition(hMCI) >=MCIWndGetLength(hMCI)) MCIWndPlay(hMCI);
	 
	}
	if(nIDEvent==3)//启动延时
		{KillTimer(3);
		 OnOK();//调地图
		}
	CDialog::OnTimer(nIDEvent);
}
void CMyDlg::setsmz(int h,int a)
{	CClientDC dc(this);
	int x,y,s=m_game.mansmz[0];
	char cc[255];
	CBrush Brush(RGB(120,120,130));
	dc.SelectObject(Brush);
	if(a==0)
		{x=3;y=500;
		 dc.PatBlt(x,y,40,50,PATCOPY);
		 CBrush Brush(RGB(200,0,0));
		 dc.SelectObject(Brush);
		 dc.PatBlt(x,y+51-h*50/s,40,h*50/s,PATCOPY);
		 sprintf(cc,"生命:%d",h);
		 SetDlgItemText(IDC_STATIC7,cc);
		}
	if(a==1)
		{x=600;y=500;
		 dc.PatBlt(x,y,40,50,PATCOPY);
		 CBrush Brush(RGB(0,0,200));
		 dc.SelectObject(Brush);
		 dc.PatBlt(x,y+50-h*50/20,40,h*50/20,PATCOPY);
		 sprintf(cc,"经验:%d",h);
		 SetDlgItemText(IDC_STATIC8,cc);
		}
}
void CMyDlg::OnLButtonDown(UINT nFlags, CPoint point)//取针对主角的目标位置,[类向导中定义生成]
{/////////////////////////////////////////////////////////////////////////////////////
	int x0=point.x,y0=point.y;
	if(y0<10)//拖动窗口
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	CClientDC dc(this);
	fidtim=m_game.leftdown(dc.m_hDC,x0,y0);//按左键
	SetCursor(m_Cur);					//显示光标
 /////////////////////////////////////////////////////////////////////////////////////
	CDialog::OnLButtonDown(nFlags, point);
}
BOOL CMyDlg::PreTranslateMessage(MSG* pMsg) 
{	CRect lpRect0;
	GetWindowRect(&lpRect0);
	int x0=pMsg->pt.x-lpRect0.left;
	int y0=pMsg->pt.y-lpRect0.top;
	CClientDC dc(this);
	if(m_game.rs>0)	m_game.movesmap(x0,y0);	//数据调入后,移动地图
	return CDialog::PreTranslateMessage(pMsg);
}
void CMyDlg::OnLButtonUp(UINT nFlags, CPoint point)//地图编辑用 
{	down=0;dowx=0;dowy=0;	//左键按键清0
	SetCursor(m_Cur);
	CDialog::OnLButtonUp(nFlags, point);
}
void CMyDlg::OnMouseMove(UINT nFlags, CPoint point)//地图编辑用 
{	int x=point.x-2-dowx;
	int y=point.y-10-dowy;
	int x0=(x+m_game.scrx)/GX,y0=(y+m_game.scry)/GY;

	CMyApp* pApp = (CMyApp*)AfxGetApp();										
	if(x>0&&x<WIDTH&&y>0&&y<HEIGHT)
	{if(m_game.m_fid.map[x0][y0]=='1'||					//目标点是障碍点
	   (x0<1||y0<1)||									//左上边界
	   ((x0+1)>=WIDTH*m_game.SCRP0/GX||(y0+1)>=HEIGHT*m_game.SCRP0/GY)	//右下边界
	  )
		  m_Cur=pApp->m_Cur3;							//禁
	 else m_Cur=pApp->m_Cur1;							//许
	}
	else  m_Cur=pApp->m_Cur0;							//普通光标
	SetCursor(m_Cur);

	CDialog::OnMouseMove(nFlags, point);
}

void CMyDlg::OnMove(int x, int y) 
{	CDialog::OnMove(x, y);	
	GetWindowRect(&lpRect);	
}

void CMyDlg::OnOK() 
{//调入文件对话框------------------------------------------------------
	KillTimer(1);KillTimer(2);
	if(hMCI!=NULL)
	{MCIWndClose(hMCI);  // close an open movie 
	 MCIWndDestroy(hMCI);
	 hMCI=NULL;
	}
	getmap Dlg;Dlg.DoModal();//显示模态对话框
	if(getdir=="end")		//选择的是退出
	{m_game.FreeDDraw();	//释放所有的DirectDraw对象。
	 m_game.exit();			//退出类
	 CDialog::OnCancel();
	 return;
	}
	if(getdir!="")			//不是放弃
	{CString name;
	 name.Format("%s/%s",getdir,getfile);
//----------------------------------------------------------------
	 fidtim=0;				//寻路时间
	 down=0;dowx=0;dowy=0;	//左键按键清0
	 m_game.movemap=0;		//地图移动否？
	 m_game.fls=0;			//闪烁标志
	 m_game.rs=0;
	 m_game.edi=0;			//非编辑态
	 m_game.scrx=0;m_game.scry=0;
	 m_game.find_p=0;		//无搜索0有搜索1
	 m_game.da=0;
//----------------------------------------------------------------
	 m_game.loadmap(name);			//调入地图
	 m_game.loadza (name);			//调入障碍表
	 m_game.Insert();	//添加物品
	 m_game.getsmap();				//生成小地图
/////////////////////////////////////////////////////////////
	 name.Format("%s/Music1.mid",getdir);
	 hMCI = MCIWndCreate(NULL, NULL,WS_POPUP|//WS_VISIBLE|
								MCIWNDF_NOPLAYBAR|MCIWNDF_NOMENU,
								name);
	 MCIWndPlay(hMCI);
	}
	SetTimer(1,TIMER,NULL);
	SetTimer(2,300,NULL);
//	CDialog::OnOK();
}
