// ��Ĵ�ѽDlg.cpp : implementation file
/*********************************
[ѧVC����Ϸ]
������������ƣ������� 2004.7
E-mail:  cqtml@163.com
**********************************/
#include "stdafx.h"
#include "��Ĵ�ѽ.h"
#include "��Ĵ�ѽDlg.h"
#include "getmap.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CString getdir;
CString getfile;
HDC HDC0;
gamepro	m_game;	//�����������---------------
int		tim;	//ˢ��ʱ��
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

BOOL CMyDlg::OnInitDialog()//�Ի������ĳ�ʼ���,[MFC�Զ�����]
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon	
	// TODO: Add extra initialization here
////////////////////////////////////////////////////////////////////////////////
	m_game.initmap();		//��ʼ����
	m_game.loaddata();		//����Դ��............................
	fidtim=0;				//Ѱ·ʱ��
	down=0;dowx=0;dowy=0;	//���������0
	MoveWindow(0,0,SCRWI,SCRHE);//���ڶ�λ
	CenterWindow();			//���д���
//--------------------------------------------------------------------
	CString str="    ���ǡ�ѧVC������Ϸ���ĵ�ʮ��ʾ��\r\n";
	str+="����һ�£�����ʹ��������֪ʶ��������\r\n";
	str+="1������������ԣ�����ֵ����������\r\n";
	str+="2����������ֵ����ʾ��\r\n";
	str+="3����ʱ����ֵ�ĸı䡣\r\n";
	str+="4���ڳ����������Ʒ��\r\n";

	str+="\r\n=======================\r\n";
	str+="   ��������\r\n\r\n";
	str+="A���ڳ����ڵ�����㣬ָ�������ƶ���\r\n";
	str+="B��������Ƶ������⣬�����ƶ���ͼ��\r\n";
	str+="C����΢����ͼ�ϵ�һ�£����Կ��ٶ�λ��\r\n";
	str+="D��ESC�����˳���Ϸ��\r\n\r\n";
	str+="�����ָ������ȥ�����ˡ�\r\n";
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
		( m_game.mapl,m_game.maph+55,m_game.mapw,25,TRUE);//����ͼ
	GetDlgItem(IDC_STATIC3)->MoveWindow(2,600-26,260,18,TRUE);		//��ʾ
	GetDlgItem(IDC_STATIC4)->MoveWindow(2+265,600-26,270,18,TRUE);	//ʱ��
	GetDlgItem(IDC_STATIC5)->MoveWindow(2+270*2,600-26,250,18,TRUE);//����

	GetDlgItem(IDC_STATIC7)->MoveWindow(3,  552,50,16,TRUE);//����
	GetDlgItem(IDC_STATIC8)->MoveWindow(600,552,50,16,TRUE);//����

	GetDlgItem(IDC_STATIC9)-> MoveWindow(250,502,150,16,TRUE);//��Ǯ
	GetDlgItem(IDC_STATIC10)->MoveWindow(250,522,150,16,TRUE);//ʳ��
//��״̬�����ضԻ���==============================
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

void CMyDlg::OnCancel() //�˳�,[�����ж�������]
{	KillTimer(1);
	KillTimer(2);
	MCIWndStop(hMCI);
	if( ::MessageBox(GetSafeHwnd(), "�˳�������?","����ȷ��!",
					MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2  ) == IDYES )
	{m_game.FreeDDraw();//�ͷ����е�DirectDraw����
	 m_game.exit();		//�˳���
	 CDialog::OnCancel();
	}
	else 
	{SetTimer(1,TIMER,NULL);
	 SetTimer(2,1000,NULL);
	 MCIWndPlay(hMCI);
	}
}

void CMyDlg::OnTimer(UINT nIDEvent) //ʱ�Ӻ���,[�����ж�������]
{////////////////////////////////////////////////////////////////////////////////////
	if(nIDEvent==1)//����ˢ��
	{tim=timeGetTime();			//��ʼʱ��
	 CClientDC dc(this);
	 m_game.mlmap();			//��ͼ���ƶ�ƴ��
	 int i;
	 for(i=0;i<m_game.rs;i++) 
		{m_game.Alphasetobj(i,0);	//������ʾ
		}
	 for(i=0;i<m_game.rs;i++) 
		{m_game.Alphasetobj(i,1);	//������ʾ
		 m_game.lookit(i);	//��ɫ��ײ
		}
	 m_game.Bk1ToPr(dc.m_hDC,lpRect);//������ҳ�浽��ҳ��
	 if(m_game.rs>0)	m_game.smlmap(dc.m_hDC);//���ݵ����,��ʾС��ͼ
	 tim=timeGetTime()-tim;		//��ʾʱ��=����ʱ��-��ʼʱ��
	}
	if(nIDEvent==2)//��ʾ��Ϣ
	{char cc[255],c1[255];
	 int q=m_game.mann;
	 if(m_game.man[q].smz<-5) //�˵�����ʼ��ʱ��
	 {KillTimer(1);KillTimer(2);
	  MCIWndStop(hMCI);
	  AfxMessageBox("��������! ��Ϸ������");
	  OnOK();
	 }
	 setsmz(m_game.man[q].smz,0);
	 setsmz(m_game.mansmz[1],1);
	 sprintf(cc,"��Ǯ:%d",m_game.mansmz[2]);
	 SetDlgItemText(IDC_STATIC9,cc);
	 sprintf(cc,"ʳ��:%d",m_game.mansmz[3]);
	 SetDlgItemText(IDC_STATIC10,cc);

	 sprintf(cc,"��ͼ[X:%4d Y:%4d] ��[x:%4d y:%4d]",
		m_game.scrx,m_game.scry,m_game.man[q].xix,m_game.man[q].xiy);
	 SetDlgItemText(IDC_STATIC5, cc);
	 sprintf(cc,"[��ʾ��������:%3d] [%3dms/��] [CPUռ��%3d��]",m_game.mans,tim,tim*100/TIMER);
	 SetDlgItemText(IDC_STATIC4, cc);
	 switch(fidtim)
	 {case -1:	{strcpy(c1,"�ϰ���");	break;}
	  case -2:	{strcpy(c1,"��ʼ��");	break;}
	  case -3:	{strcpy(c1,"��·");		break;}
	  case -4:	{strcpy(c1,"����æ");	break;}
	  case -5:	{strcpy(c1,"̫Զ��");	break;}
	  case -10:	{strcpy(c1,"���ϱ߽�");	break;}
	  case -20:	{strcpy(c1,"���±߽�");	break;}
	  default:	{sprintf(c1,"����:%dms",fidtim);}
	 }
	 sprintf(cc,"��ͼ%dX%d �ϰ�%dX%d %s,%d",
		        WIDTH*m_game.SCRP0,HEIGHT*m_game.SCRP0,
				WIDTH*m_game.SCRP0/GX,HEIGHT*m_game.SCRP0/GY,c1,m_game.man[q].pk);
	 SetDlgItemText(IDC_STATIC3, cc);
	 m_game.randxy();//��������޵��ƶ�Ŀ��
	 if(MCIWndGetPosition(hMCI) >=MCIWndGetLength(hMCI)) MCIWndPlay(hMCI);
	 
	}
	if(nIDEvent==3)//������ʱ
		{KillTimer(3);
		 OnOK();//����ͼ
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
		 sprintf(cc,"����:%d",h);
		 SetDlgItemText(IDC_STATIC7,cc);
		}
	if(a==1)
		{x=600;y=500;
		 dc.PatBlt(x,y,40,50,PATCOPY);
		 CBrush Brush(RGB(0,0,200));
		 dc.SelectObject(Brush);
		 dc.PatBlt(x,y+50-h*50/20,40,h*50/20,PATCOPY);
		 sprintf(cc,"����:%d",h);
		 SetDlgItemText(IDC_STATIC8,cc);
		}
}
void CMyDlg::OnLButtonDown(UINT nFlags, CPoint point)//ȡ������ǵ�Ŀ��λ��,[�����ж�������]
{/////////////////////////////////////////////////////////////////////////////////////
	int x0=point.x,y0=point.y;
	if(y0<10)//�϶�����
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	CClientDC dc(this);
	fidtim=m_game.leftdown(dc.m_hDC,x0,y0);//�����
	SetCursor(m_Cur);					//��ʾ���
 /////////////////////////////////////////////////////////////////////////////////////
	CDialog::OnLButtonDown(nFlags, point);
}
BOOL CMyDlg::PreTranslateMessage(MSG* pMsg) 
{	CRect lpRect0;
	GetWindowRect(&lpRect0);
	int x0=pMsg->pt.x-lpRect0.left;
	int y0=pMsg->pt.y-lpRect0.top;
	CClientDC dc(this);
	if(m_game.rs>0)	m_game.movesmap(x0,y0);	//���ݵ����,�ƶ���ͼ
	return CDialog::PreTranslateMessage(pMsg);
}
void CMyDlg::OnLButtonUp(UINT nFlags, CPoint point)//��ͼ�༭�� 
{	down=0;dowx=0;dowy=0;	//���������0
	SetCursor(m_Cur);
	CDialog::OnLButtonUp(nFlags, point);
}
void CMyDlg::OnMouseMove(UINT nFlags, CPoint point)//��ͼ�༭�� 
{	int x=point.x-2-dowx;
	int y=point.y-10-dowy;
	int x0=(x+m_game.scrx)/GX,y0=(y+m_game.scry)/GY;

	CMyApp* pApp = (CMyApp*)AfxGetApp();										
	if(x>0&&x<WIDTH&&y>0&&y<HEIGHT)
	{if(m_game.m_fid.map[x0][y0]=='1'||					//Ŀ������ϰ���
	   (x0<1||y0<1)||									//���ϱ߽�
	   ((x0+1)>=WIDTH*m_game.SCRP0/GX||(y0+1)>=HEIGHT*m_game.SCRP0/GY)	//���±߽�
	  )
		  m_Cur=pApp->m_Cur3;							//��
	 else m_Cur=pApp->m_Cur1;							//��
	}
	else  m_Cur=pApp->m_Cur0;							//��ͨ���
	SetCursor(m_Cur);

	CDialog::OnMouseMove(nFlags, point);
}

void CMyDlg::OnMove(int x, int y) 
{	CDialog::OnMove(x, y);	
	GetWindowRect(&lpRect);	
}

void CMyDlg::OnOK() 
{//�����ļ��Ի���------------------------------------------------------
	KillTimer(1);KillTimer(2);
	if(hMCI!=NULL)
	{MCIWndClose(hMCI);  // close an open movie 
	 MCIWndDestroy(hMCI);
	 hMCI=NULL;
	}
	getmap Dlg;Dlg.DoModal();//��ʾģ̬�Ի���
	if(getdir=="end")		//ѡ������˳�
	{m_game.FreeDDraw();	//�ͷ����е�DirectDraw����
	 m_game.exit();			//�˳���
	 CDialog::OnCancel();
	 return;
	}
	if(getdir!="")			//���Ƿ���
	{CString name;
	 name.Format("%s/%s",getdir,getfile);
//----------------------------------------------------------------
	 fidtim=0;				//Ѱ·ʱ��
	 down=0;dowx=0;dowy=0;	//���������0
	 m_game.movemap=0;		//��ͼ�ƶ���
	 m_game.fls=0;			//��˸��־
	 m_game.rs=0;
	 m_game.edi=0;			//�Ǳ༭̬
	 m_game.scrx=0;m_game.scry=0;
	 m_game.find_p=0;		//������0������1
	 m_game.da=0;
//----------------------------------------------------------------
	 m_game.loadmap(name);			//�����ͼ
	 m_game.loadza (name);			//�����ϰ���
	 m_game.Insert();	//�����Ʒ
	 m_game.getsmap();				//����С��ͼ
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
