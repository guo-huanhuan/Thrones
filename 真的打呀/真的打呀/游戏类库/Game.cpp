/*********************************
[ѧVC����Ϸ]
������������ƣ������� 2004.7
E-mail:  cqtml@163.com
Downlaod by http://www.codefans.net
**********************************/
#include "stdafx.h"
#include "game.h"

JCDZ zjdz[6]={0,5,40,10,120,10,200,10,280,10,360,5};//�˶����ṹ400��
			//0վ,1��,  2��,   3��,   4��    5ʬ
JCDZ zjdw[6]={0,5,40,10,120,10,200,10,280,10,360,5};//�޶����ṹ400��
			//0վ,1��,  2��,   3��,   4��,   5ʬ
unsigned short dw[7][6]={0,1,1,3,4,5,	//0��,����
						 0,1,2,3,4,5,	//1��,
						 0,1,1,3,4,5,	//2��,����
						 0,1,2,3,4,5,	//3¹,
						 0,2,2,2,4,5,	//4��,���ߡ���
						 0,1,1,1,4,5,	//5��,���ܡ���
						 0,1,1,3,4,5	//6ȸ,����
						 };
////////////////////////////////////////////////////////////////////////////
game:: game(){}	//���캯��
game::~game(){}	//��������
//****************************************************************
// init() ��ʼ��,����ͼ�δ�����
//	BkDC0-װ�ر�������
//	BkDC1-�ڴ����ɼ�ʱ��������1��ʱ�����ں�ת����ǰ��ʾ����
//	MemDC-����Ķ���ͼƬ��
//****************************************************************
BOOL game::init()//��ʼ��
{	hScrDC=CreateDC("DISPLAY", NULL, NULL, NULL);	//������Ļ�豸���
	BkDC0 =CreateCompatibleDC(hScrDC);				//������ͼ�豸���
	BkDC1 =CreateCompatibleDC(hScrDC);				//�����ݴ��豸���
	bit0  =CreateCompatibleBitmap(hScrDC,WIDTH,HEIGHT);//�����ݴ�λͼ�ڴ�0
	bit1  =CreateCompatibleBitmap(hScrDC,WIDTH,HEIGHT);//�����ݴ�λͼ�ڴ�1
	SelectObject(BkDC1,bit1);						//�ݴ�λͼ�ڴ�1���ݴ��豸�������
	OldMak=(HBITMAP)SelectObject(BkDC0,bit0);		//�ݴ�λͼ�ڴ�0���ͼ�豸�������
	MemDC =CreateCompatibleDC(hScrDC);				//���������豸���
//==================================================
	BK =CreateCompatibleDC(hScrDC);//�����ݴ��豸���
	bi =CreateCompatibleBitmap(hScrDC,WIDTH,HEIGHT);
	SelectObject(BK,bi);

	bitya=CreateCompatibleBitmap(hScrDC,220,200);
	DeleteDC(hScrDC);								//ɾ����Ļ�豸���
	rBlend.BlendOp = AC_SRC_OVER;	//
	rBlend.BlendFlags = 0;			//
	rBlend.AlphaFormat = 0;			//
	rBlend.SourceConstantAlpha=140;
//==================================================
	GetCurrentDirectory(256,appdir);//ȡ��ǰĿ¼
	dir=appdir;
	if(dir.Right(8)=="���г���")
			dir="ͼƬ/";
	else	
		dir="../���г���/ͼƬ/";	//ͼƬ·��
//==================================================
	sys=getsys();	//ȡ��ǰϵͳ
	scrx=0;scry=0;
	rs=0;			//��������0
	find_p=0;		//������0������1
	stmp=NULL;rtmp=NULL;jtmp=NULL;
	return TRUE;
}
//**************************************************
//  exit() �˳�, ɾ��ͼ�δ�����
//**************************************************
void game::exit()//�˳�
{	DeleteDC(BK);
	DeleteObject(bi);
	DeleteObject(bitya);
	DeleteObject(bit0);	//ɾ���ݴ�λͼ�ڴ�
	DeleteObject(bit1);	//ɾ���ݴ�λͼ�ڴ�
	DeleteDC(BkDC0);	//ɾ����ͼ�豸���
	DeleteDC(BkDC1);	//ɾ���ݴ��豸���
	DeleteDC(MemDC);	//ɾ�������豸���
	DeleteDC(hScrDC);	//ɾ����Ļ�豸���
}
//****************************************************
//	getsys()//ʶ�����ϵͳ
//	ʹ��TransparentBlt()͸����ʾ����Ҫ��
//	��WIN2000��ֱ�ӵ���TransparentBlt()����������Ա�ġ�
//****************************************************
int game::getsys()//ʶ�����ϵͳ
{	OSVERSIONINFO stOSVI ;
	ZeroMemory(&stOSVI , sizeof ( OSVERSIONINFO )) ;
    stOSVI.dwOSVersionInfoSize = sizeof ( OSVERSIONINFO ) ;
    GetVersionEx ( &stOSVI);
	int a=0;
	if (stOSVI.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS &&
		(stOSVI.dwMajorVersion>4||(stOSVI.dwMajorVersion==4
		 && stOSVI.dwMinorVersion>0)))
	a=1;//	rec="Windows98";
	if (VER_PLATFORM_WIN32_NT==stOSVI.dwPlatformId&&stOSVI.dwMajorVersion>=5)
	a=2;//	rec="Windows2000";
	if (VER_PLATFORM_WIN32_NT==stOSVI.dwPlatformId&&stOSVI.dwMajorVersion==4)
	a=3;//	rec="WindowsNT4.0";
	if (VER_PLATFORM_WIN32_NT==stOSVI.dwPlatformId)
	a=4;//	rec="WindowsNT";
	return a;
}
//**********************************************************
//	inscreer(int i)//����ʾ����
//**********************************************************
BOOL game::inscreer(int i)//����ʾ����
{	int xs=man[i].xix-scrx-man[i].w/2;		//x��ǰλ��
	int ys=man[i].xiy-scry-man[i].h;		//y��ǰλ��
	if(xs>(-man[i].w+2)&&xs<WIDTH&&ys>(-man[i].h+10)&&ys<HEIGHT)
			return TRUE;
	else	return FALSE;
}

//**********************************************************
//  sort() ����(ð�ݷ�)
//  ��rs���������ж�Yλ�ý�������;��������ʾʱ�ֳ�ǰ��λ�á�
//**********************************************************
void game::sort()//����(ð�ݷ�)
{	MAN man0;
	for(int a=0;a<rs-1;a++)
	 for(int b=a+1;b<rs;b++)
		if(man[a].xiy>man[b].xiy)//ǰ�����ں���
			{man0=man[a];		 //��������
			 man[a]=man[b];
			 man[b]=man0;
			}					 //����������ǰλ��YС����ǰ��							
	mans=0;						 //��ʾ����������0
}
//**************************************************
//  getobjwh(int q) ȡ����ĳߴ�
//  ȡ���q����ĳߴ�(��man[q].w��man[q].h)��
//**************************************************
void game::getobjwh(int q)//ȡ����ĳߴ�
{	CString cc;
	if(man[q].lb==0)	{cc="��";}
	if(man[q].lb==1)	{cc="��";}	
	if(man[q].lb==2) 	{cc="��";}
	if(getpic(cc,man[q].p)==FALSE) return;
	man[q].w=w; man[q].h=h;			//����ĳߴ�
}
//**********************************************************************
//  TransparentBlt2 (......)͸����ʾ
//  ���ݹؼ�ɫ����hdc1�е�ͼ����hdc0��
//  �Զ�������ģ��������͸��ͼ�Ρ�
//	ע:TransparentBlt(......)��һ��WIN API���������ܺ��������ͬ��
//	��WIN2000���Ժ��ϵͳ�Ͽ��á���WIN98�������ص���Դй©�����������á�
//  ʹ��TransparentBlt(......)ǰ��������:
//  #include <wingdi.h>
//  #pragma comment (lib,"msimg32.lib")
//**********************************************************************
void game::TransparentBlt2(HDC hdc0,			//Ŀ��DC
				int nX0,int nY0,int nW0,int nH0,//Ŀ��������,Ŀ���߿�
				HDC hdc1,						//ԴDC
				int nX1,int nY1,int nW1,int nH1,//Դ�������,Դ��߿�
				UINT Tcol)						//͸��ɫ,COLORREF����
					 
{	if(sys>1)//��win98���ϵ�ϵͳ��ֱ�ӵ�API����TransparentBlt()
	{TransparentBlt(hdc0,nX0,nY0,nW0,nH0,hdc1,nX1,nY1,nW1,nH1,Tcol);
	 return;
	}
	HBITMAP hBMP   =CreateCompatibleBitmap(hdc0,nW0, nH0);	//����λͼ�ڴ�
	HBITMAP mBMP   =CreateBitmap(nW0,nH0,1,1,NULL);			//������ɫ����λͼ
	HDC		hDC    =CreateCompatibleDC(hdc0);				//�����豸���
	HDC		mDC    =CreateCompatibleDC(hdc0);				//�����豸���
	HBITMAP oldBMP =(HBITMAP)SelectObject(hDC, hBMP);
	HBITMAP oldmBMP=(HBITMAP)SelectObject(mDC, mBMP);
	// ��ԴDC�е�λͼ��������ʱDC��
	if (nW0==nW1&&nH0==nH1)
		BitBlt(hDC,0,0,nW0,nH0,hdc1,nX1,nY1,SRCCOPY);
	else
		StretchBlt(hDC,0,0,nW0,nH0,hdc1,nX1,nY1,nW1,nH1,SRCCOPY);
	SetBkColor(hDC, Tcol);// ����͸��ɫ
	BitBlt(mDC,0,0,nW0,nH0,hDC,0,0,SRCCOPY);//����͸������Ϊ��ɫ,��������Ϊ��ɫ������λͼ

	SetBkColor(hDC, RGB(0,0,0));			//����͸������Ϊ��ɫ,�������򱣳ֲ����λͼ
	SetTextColor(hDC, RGB(255,255,255));	//��ɫ
	BitBlt(hDC,0,0,nW0,nH0,mDC,0,0,SRCAND);
	SetBkColor(hdc0,RGB(255,255,255));		//͸�����ֱ�����Ļ����,�������ֱ�ɺ�ɫ
	SetTextColor(hdc0,RGB(0,0,0));			//��ɫ

	BitBlt(hdc0,nX0,nY0,nW0,nH0,mDC,0,0,SRCAND);  //"��"����,��hdc0������ģ
	BitBlt(hdc0,nX0,nY0,nW0,nH0,hDC,0,0,SRCPAINT);//"��"����,��������͸��Ч��	
	SelectObject(hDC,oldBMP);
	SelectObject(mDC,oldmBMP);
	DeleteDC(hDC);
	DeleteDC(mDC);
	DeleteObject(hBMP);
	DeleteObject(mBMP);
}
//**************************************************
//  setman(int q) ���û�����ֵ
//  �ɸ����Ķ��󡢷�λ�����������ͼ�ε�λ�ú�������
//**************************************************
void game::setman(int q)//���û�����ֵ
{	int a=400;
	if(man[q].lb==0)//��
	{man[q].m0=man[q].js*a+zjdz[man[q].zs].qi
			  +man[q].fw*zjdz[man[q].zs].bc;//λ�ó�ֵ
	 man[q].m1=zjdz[man[q].zs].bc+man[q].m0;//λ����ֵ
	 man[q].p=man[q].m0;					//��������
	}
	if(man[q].lb==1)//��
	{man[q].m0=man[q].js*a+zjdw[man[q].zs].qi
			  +man[q].fw*zjdw[man[q].zs].bc;//λ�ó�ֵ
	 man[q].m1=zjdw[man[q].zs].bc+man[q].m0;//λ����ֵ
	 man[q].p=man[q].m0;					//��������
	}
	man[q].zd=0;
}
//**************************************************
//  manmove(int i)	�������ƶ�
//  �ɵ�ǰ��Ŀ��λ�õĲ���㵱ǰλ����ͬ��λ�ĸı䡣
//**************************************************
void game::manmove(int i)//�������ƶ�
{	if(man[i].lb==2)	return;		//�Ǿ��ﷵ��

	if(find_p==1&&man[i].pk<1)  return;//������·������,û��Ѱ·ʱ��Ҫ��䡣

	int stx,sty,qx,qy;
	switch(man[i].zs) 
		{case 2: {stx=9;sty=6;break;}//�ܲ���
	     case 1: {stx=4;sty=2;break;}//�߲���
		 default:{stx=2;sty=1;break;}
		}
	qx=man[i].x0-man[i].xix;		//x��ǰ��Ŀ��λ�ò�
	qy=man[i].y0-man[i].xiy;		//y��ǰ��Ŀ��λ�ò�
	if (qx==0&&qy==0) 
	{if(find_p==1)	find_a(i);		//û��Ѱ·ʱ��Ҫ��䡣
	 return ;		//���ﷵ��
	}
	int qxa=abs(qx);				//xλ�ò����ֵ
	int qya=abs(qy);				//yλ�ò����ֵ
	if(qxa<stx)  stx=qxa;			//λ�ò�㲽��������Ϊ��
	if(qya<sty)  sty=qya;			//
	if(qx!=0) man[i].xix+=qxa/qx*stx;//��ǰλ�üӲ���
	if(qy!=0) man[i].xiy+=qya/qy*sty;//[qya/qy]��λ����ֵ
}
//**************************************************
//  bianfw(int q)//��λת��
//  �ɵ�ǰ��Ŀ��λ�õĲ����ͼ�εķ���ȡ��
//**************************************************
void game::bianfw(int q)//��λת��
{	int qx=man[q].x0-man[q].xix;		//x��ǰ��Ŀ��λ�ò�
	int qy=man[q].y0-man[q].xiy;		//y��ǰ��Ŀ��λ�ò�

	if(qx==0&&qy==0) 
		{if(man[q].zd==0) man[q].zs=0;	//Ϊ0,����Ϊվ,��λ����
		 goto aa;
		}	
	if(man[q].zd==0)					//û��
	{int a=rand()%2+1;					//��������ߡ���
	 if(man[q].lb==0) man[q].zs=1;		//������Ϊ��
	 if(man[q].lb==1) man[q].zs=dw[man[q].js][a];//����
	}
	if(qx<0&&qy>0)		{man[q].fw=1;goto aa;}//ȡ������
	if(qx<0&&qy<0)		{man[q].fw=3;goto aa;}//ȡ������
	if(qx>0&&qy<0)		{man[q].fw=5;goto aa;}//ȡ������
	if(qx>0&&qy>0)		{man[q].fw=7;goto aa;}//ȡ������
	if      (qy>0)		{man[q].fw=0;goto aa;}//ȡ����
	if(qx<0)			{man[q].fw=2;goto aa;}//ȡ����
	if      (qy<0)		{man[q].fw=4;goto aa;}//ȡ����
	if(qx>0)			{man[q].fw=6;goto aa;}//ȡ����
aa:	setman(q);								  //���û�����ֵ
	if(man[q].zs==0) 
		man[q].p=man[q].p+rand()%3;			  //���⶯��һ��
}
//**************************************************
//	loadmap(CString name)//�����ʼ��
//	������ƺõĶ��󳡾�(.dat)
//	�����ļ�(.dat)�ĸ�ʽ��
//	��1�У�Ϊ����ͼ��
//	��2�У�������,����һ����һ������
//	���,���,��ɫ,����ͼ�κ�,x,yλ��6������	
//**************************************************
void game::loadmap(CString name)//����ͼ
{ FILE *f;
  SetCurrentDirectory(appdir);	 //�õ�ǰĿ¼
  f=fopen(name,"r");
  if(f==NULL) 
	{AfxMessageBox(name+"û�е�ͼ�ļ�!!!");
     return;
	}
  fscanf(f,"%s\n",mapbak);		  //��ͼ����
  fscanf(f,"%d\n",&rs);			  //������
  if(rs>SU_LIANG)				  //�����������趨ֵ����
		{fclose(f);
		 SetCurrentDirectory(appdir);//�õ�ǰĿ¼
		 return;
		}		  
  int i;
  for (i=0;i<rs;i++)
	{fscanf(f,"%d,",&man[i].jisu);//���
	 fscanf(f,"%d,",&man[i].lb);  //���:  [0��1��2��]
	 fscanf(f,"%d,",&man[i].js);  //��ɫ:��[0��1Ů]
								  //��ɫ:��[0��1��2¹3��4ȸ5��6��]
	 fscanf(f,"%d,",&man[i].p);	  //����ͼ�κ�
	 fscanf(f,"%d,",&man[i].xix); //��ǰλ��x
	 fscanf(f,"%d,",&man[i].xiy); //��ǰλ��y
	 man[i].x0=man[i].xix;		  //Ŀ��λ��x
	 man[i].y0=man[i].xiy;		  //Ŀ��λ��y
	 man[i].fw=1;				  //��λ:  [0��1����2��3����4��5����6��7����]
	 man[i].zs=0;				  //����:��[0վ1��2��3��4��]
								  //����:��[0վ1��2��3��4��5ʬ]
	 man[i].pk =-1;				  //·����
	 man[i].fid=-1;				  //·������
	 man[i].zd=0;
	 if(man[i].lb!=2) 
		 setman(man[i].jisu);	  //���û�����ֵ
	 getobjwh(i);				  //ȡ����ĳߴ�
	}
  fclose(f);
  SetCurrentDirectory(appdir);	 //�õ�ǰĿ¼
}
//**************************************************
//  getpic(CString cc,int p) ��ͼƬ�����λͼ
//  ��p�õ�������ͼ���ļ�����
//  ��ָ��Ŀ¼�е���ͼ�ε����λͼbit
//**************************************************
BOOL game::getpic(CString cc,int p)//��ͼƬ�����λͼ[3��]
{	char name[256];
	if(stmp==NULL)		//û��ѹ����Դ
		{SetCurrentDirectory(appdir);			 //�õ�ǰĿ¼
//��ccָ����ͼ��
		 sprintf(name,"%s%s/c%05d.bmp",dir,cc,p);//���ɽ�����ͼ���ļ���
		 if(!loadbmp(name)) return FALSE;		 //��BMPͼƬ
		 SelectObject(MemDC,bitmap);
//��ccָ����ͼ�ε�ƫ��ֵ��
		 sprintf(name,"%s%s/c%05d.txt",dir,cc,p);
		 FILE *f;
		 f=fopen(name,"r");
		 if(f!=NULL)
			{if(cc=="��") fscanf(f,"%d,%d",&rbufx[p],&rbufy[p]);//�˵�ƫ����
			 if(cc=="��") fscanf(f,"%d,%d",&sbufx[p],&sbufy[p]);//�޵�ƫ����
			 fclose(f);
			}
		 return TRUE;
		}
	else 
	{if(getpic0(cc,p)) return TRUE;//��ѹ��ͼƬ��
	 else return FALSE;
	}
}
//**************************************************
//  loadbmp(CString cc)//��BMPͼƬ
//  ��ccָ����ͼ��;ȡ�õ�ͼ�����豸���λͼbit��
//  ͼ�εĿ��ߴ���ȫ�ֱ���w,h��
//**************************************************
BOOL game::loadbmp(CString cc)//��BMPͼƬ[2��]
{	DeleteObject(bitmap);				//ɾ���ϴε�λͼ�ڴ档
	bitmap=(HBITMAP)LoadImage			//����ccָ����ͼ��
				(AfxGetInstanceHandle(),//
				 cc,IMAGE_BITMAP,		//�ļ���,λͼ��ʽ				 			
				 0,0,					//ͼ�ο�,��
				 LR_LOADFROMFILE|LR_CREATEDIBSECTION//��ʽ
				);
	if(bitmap==NULL) return FALSE;		//��ͼʧ��
	DIBSECTION ds;						//
	BITMAPINFOHEADER &bm = ds.dsBmih;	//
	GetObject(bitmap,sizeof(ds),&ds);	//ȡλͼ����Ϣ->bminfo
	w = bm.biWidth;						//�õ�λͼ���ֵ 
	h = bm.biHeight;					//�õ�λͼ�߶�ֵ
	return TRUE;
}
/////////////////////////////////////////////////////////////////
void game::find_a(int i)//û��Ѱ·ʱ��Ҫ��
{//�����Զ�������Ӧִ�еĴ���
	if(man[i].fid<man[i].pk)	//��������·����ȡĿ���
			{man[i].x0=man[i].ph[man[i].fid].x*GX+man[i].w/2;
			 man[i].y0=man[i].ph[man[i].fid].y*GY+man[i].h/2;
			 man[i].fid++;
			 if(man[i].x0<GX) man[i].x0=GX;
			 if(man[i].y0<GX) man[i].y0=GY;
			 bianfw(i);				//��λת��
			}
	else						//����·��ȡ��
			{man[i].x0=man[i].fx;
			 man[i].y0=man[i].fy;
			}
}
//**************************************************
//  setobj(int q) ������ʾ
//	������man[q].lbָ���ģ���ͬ��man[q].pͼƬ����ƫ��ֵ��
//  ������q�ڸ��Եĵ�ǰλ��x,y����͸����ʽTransparentBlt2��ʾ��
//	֮������ƶ���λת���Ĺ��ܡ�
//  Ϊ��ֹ��˸�����ж�������ʾ���ݴ���BkDC1��һ����ɺ��ٷ�ת�������ϡ�
//**************************************************
void game::setobj(int q)//������ʾ
{	CString cc;
	int x=man[q].xix-scrx-man[q].w/2;		//x��ǰλ��
	int y=man[q].xiy-scry-man[q].h;			//y��ǰλ��
	if(inscreer(q))//����ʾ����
	{if(man[q].lb==0) {cc="��";}
	 if(man[q].lb==1) {cc="��";}
	 if(man[q].lb==2) {cc="��";}
	 if(getpic(cc,man[q].p)==FALSE) return;
	 if(man[q].lb!=2)//����ɫ��ƫ��λ��
     {int x0=0,y0=0;
	  if(man[q].lb==0) {x0=rbufx[man[q].p];y0=rbufy[man[q].p];}
	  if(man[q].lb==1) {x0=sbufx[man[q].p];y0=sbufy[man[q].p];}
	  if(man[q].fw>4) x0=w-x0;//�Ƕ������������Ϸ�λ
	  x=man[q].xix-scrx-x0;
	  y=man[q].xiy-scry-y0;
	 }
	 TransparentBlt2(BkDC1,x,y,w,h,MemDC,0,0,w,h,RGB(255,255,255));//͸����ʾ
	 mans++;
	}
///////////////////////////////////////////////////////////////////////
	if(man[q].lb==2) return;
	else	manmove(q);				  //�������ƶ�
	man[q].p++;						  //��һ����
	if(man[q].p>=man[q].m1)	{bianfw(q);}//���������,���з�λת��
}
//**************************************************
//  setobj(int q) ������ʾ
//	������man[q].lbָ���ģ���ͬ��man[q].pͼƬ����ƫ��ֵ��
//  ������q�ڸ��Եĵ�ǰλ��x,y����͸����ʽTransparentBlt2��ʾ��
//	֮������ƶ���λת���Ĺ��ܡ�
//  Ϊ��ֹ��˸�����ж�������ʾ���ݴ���BkDC1��һ����ɺ��ٷ�ת�������ϡ�
//**************************************************
void game::Alphasetobj(int q,int a)//������ʾ
{	if(a==1&&man[q].lb==2) return;
	CString cc;
	int x=man[q].xix-scrx-man[q].w/2;		//x��ǰλ��
	int y=man[q].xiy-scry-man[q].h;			//y��ǰλ��
	if(inscreer(q))//����ʾ����
	{if(man[q].lb==0) {cc="��";}
	 if(man[q].lb==1) {cc="��";}
	 if(man[q].lb==2) {cc="��";}
	 if(getpic(cc,man[q].p)==FALSE) return;

	 if(man[q].lb!=2)						//����ɫ��ƫ��λ��
     {int x0=0,y0=0;
	  if(man[q].lb==0) {x0=rbufx[man[q].p];y0=rbufy[man[q].p];}
	  if(man[q].lb==1) {x0=sbufx[man[q].p];y0=sbufy[man[q].p];}
	  if(man[q].fw>4) x0=w-x0;//�Ƕ������������Ϸ�λ
	  x=man[q].xix-scrx-x0;
	  y=man[q].xiy-scry-y0;
	 }
///////////////////////////////////////////////////////////////////////////////
	 if(a==0)
		{TransparentBlt2(BkDC1,x,y,w,h,MemDC,0,0,w,h,RGB(255,255,255));//͸����ʾ
		 return;
		}
	 else	Alpha(x,y);
///////////////////////////////////////////////////////////////////////////////
	 mans++;
	}
///////////////////////////////////////////////////////////////////////
	if(man[q].lb==2) return;
	else	manmove(q);				  //�������ƶ�
	man[q].p++;						  //��һ����
	if(man[q].p>=man[q].m1)	{bianfw(q);}//���������,���з�λת��
}
void game::Alpha(int x,int y)//
{	BitBlt(BK,0,0,w,h,BkDC1,x,y,SRCCOPY);
	TransparentBlt2(BkDC1,x,y,w,h,MemDC,0,0,w,h,RGB(255,255,255));//͸����ʾ
	AlphaBlend(BkDC1,x,y,w,h,BK,0,0,w,h,rBlend);//��͸������
}
//****************************************************************
//  BOOL getpic0(CString cc,int p) ��ѹ��ͼƬ
//  ��ccָ����ѹ������ȡ��p��ͼ�κ�ͼ�εĳߴ�w��h��ȡ�õ�ͼ����MemDC�С�
//****************************************************************
BOOL game::getpic0(CString cc,int p)//��ѹ��ͼƬ
{	int len;
	if(p<0) return FALSE;
	BYTE *tmp;
	if(cc=="��")
	{if(p>RBUF-1) return FALSE;
	 len=rbufadd[p+1]-rbufadd[p];	//ȡ���ݿ鳤��
	 tmp=(BYTE *)new BYTE[len];
	 Memcpy0(tmp,rtmp+rbufadd[p],len);
	}
	if(cc=="��")
	{if(p>SBUF-1) return FALSE;
	 len=sbufadd[p+1]-sbufadd[p];	//ȡ���ݿ鳤��
	 tmp=(BYTE *)new BYTE[len];
	 Memcpy0(tmp,stmp+sbufadd[p],len);
	}
	if(cc=="��")
	{if(p>JBUF-6) return FALSE;
	 len=jbufadd[p+1]-jbufadd[p];	//ȡ���ݿ鳤��
	 tmp=(BYTE *)new BYTE[len];
	 Memcpy0(tmp,jtmp+jbufadd[p],len);
	}
	LPBITMAPINFOHEADER bm=(BITMAPINFOHEADER *)tmp;//ͼ������ת��
	bm->biSize = sizeof(BITMAPINFOHEADER);
	w=bm->biWidth;	//ͼ�θ�
	h=bm->biHeight;	//ͼ�ο�
//----------------------------------------------------------------------
	OldMak=(HBITMAP)SelectObject(MemDC,bitya);
	StretchDIBits(MemDC,0,0,w,h,0,0,w,h,
				  tmp+256*sizeof(RGBQUAD)+bm->biSize,
				  (BITMAPINFO* )bm,DIB_RGB_COLORS,SRCCOPY);

	delete[] tmp;
	return TRUE;
}
void game::Memcpy0(unsigned char *mu,unsigned char *yu,int z)
{memcpy(mu,yu,z);
	return;
 int z0=z/32;
 int z1=z-z0*32;
	   _asm
	   {//pand mm0,mm4	  ;//packed and  
		mov	esi,yu  
		mov	edi,mu 
		mov	ecx,z0
 Mcont:
		movq	mm0,qword ptr [esi]
		movq	qword ptr [edi],mm0
		movq	mm0,qword ptr [esi][8]
		movq	qword ptr [edi][8],mm0
		movq	mm0,qword ptr [esi][16]
		movq	qword ptr [edi][16],mm0
		movq	mm0,qword ptr [esi][24]
		movq	qword ptr [edi][24],mm0
		add		esi,8*4
		add		edi,8*4
		loop	Mcont
		mov		ecx,z1;
		repe	movsb;
		emms			;//empty MMX state
	   }
}