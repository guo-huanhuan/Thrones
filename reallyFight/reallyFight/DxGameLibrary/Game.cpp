/*********************************
[ѧVC����Ϸ]
������������ƣ������� 2004.7
E-mail:  cqtml@163.com
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
unsigned short smz[2][7]={60,50,30,20,40,10,15,//����ֵ
						  10 ,8 ,6 ,3 ,5 ,1 ,2 };//������
					 //��[0��1��2��3¹4��5ȸ6��]
////////////////////////////////////////////////////////////////////////////
game:: game(){}	//���캯��
game::~game(){}	//��������
//****************************************************************
//  A��	init() ��ʼ��,����ͼ�δ�����
//		BkDC0-װ�ر�������
//		BkDC1-�ڴ����ɼ�ʱ��������1��ʱ�����ں�ת����ǰ��ʾ����
//		MemDC-����Ķ���ͼƬ��
//****************************************************************
BOOL game::init()//��ʼ��
{	if(!InitDDraw()) //��ʼ��DirectDraw������
		return FALSE;
	hScrDC=CreateDC("DISPLAY", NULL, NULL, NULL);	//������Ļ�豸���
	MemDC =CreateCompatibleDC(hScrDC);				//���������豸���
	hBMP0   =CreateCompatibleBitmap(hScrDC,100,100);	//����λͼ�ڴ�
	hBMP1   =CreateCompatibleBitmap(hScrDC,100,100);	//����λͼ�ڴ�
	hDC0    =CreateCompatibleDC(hScrDC);
	hDC1    =CreateCompatibleDC(hScrDC);
	SelectObject(hDC0, hBMP0);
	SelectObject(hDC1, hBMP1);	
/////////////////////////////////////////////////////////////////////////
	GetCurrentDirectory(256,appdir);
	Font.CreateFont(-4,0,0,0,400,0,0,0,134,0,0,0,0,LPCTSTR("impact"));

	mansmz[0]=200;mansmz[1]=5;mansmz[2]=10;mansmz[3]=20;mansmz[4]=0;
	da=0;
	dir=appdir;
	if(dir.Right(8)=="���г���")
			dir="ͼƬ/";
	else	
		dir="../���г���/ͼƬ/";	//ͼƬ·��
	sys=getsys();				//ȡ��ǰϵͳ
	rs=0;						//��������0
	edi=0;						//�Ǳ༭̬
	scrx=0;scry=0;
	stmp=NULL;rtmp=NULL;jtmp=NULL;
	find_p=0;		//������0������1
	SCRP0=5;		//Ĭ�ϵ�ͼ������ʾ��5��

	rBlend.BlendOp = AC_SRC_OVER;	//
	rBlend.BlendFlags = 0;			//
	rBlend.AlphaFormat = 0;			//
	rBlend.SourceConstantAlpha=140;
	return TRUE;
}
//**************************************************
//  exit() �˳�, ɾ��ͼ�δ�����
//**************************************************
void game::exit()//�˳�
{	if(stmp!=NULL) delete[] stmp;//ɾ������Դ��
	if(rtmp!=NULL) delete[] rtmp;//ɾ������Դ��
	if(jtmp!=NULL) delete[] jtmp;//ɾ������Դ��
	DeleteDC(hDC0);
	DeleteDC(hDC1);
	DeleteObject(hBMP0);
	DeleteObject(hBMP1);
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
//**************************************************
//  setobj(int q) ������ʾ
//	������man[q].lbָ���ģ���ͬ��man[q].pͼƬ����ƫ��ֵ��
//  ������q�ڸ��Եĵ�ǰλ��x,y����͸����ʽTransparentBlt2��ʾ��
//	֮������ƶ���λת���Ĺ��ܡ�
//  Ϊ��ֹ��˸�����ж�������ʾ���ݴ���BkDC1��һ����ɺ��ٷ�ת�������ϡ�
//**************************************************
void game::Alphasetobj(int q,int a)//������ʾ
{	if(a==1&&man[q].lb==2) return;
	if(man[q].zs>5)			//����ֵ
		{Delete(q);return;}	//ɾ�����󷵻�
	CString cc;
	int x=man[q].xix-scrx-man[q].w/2;	//x��ǰλ��
	int y=man[q].xiy-scry-man[q].h;		//y��ǰλ��
	if(inscreer(q))//����ʾ����
	{if(getpic(q,0)==FALSE) return;		//��ͼ�Σ�������
	 if(man[q].lb<2)//����ɫ��ƫ��λ��
		 {int x0=0,y0=0;
		  if(man[q].lb==0) {x0=rbufx[man[q].p];y0=rbufy[man[q].p];}
		  if(man[q].lb==1) {x0=sbufx[man[q].p];y0=sbufy[man[q].p];}
		  if(man[q].fw>4) x0=w-x0;//�Ƕ������������Ϸ�λ
		  x=man[q].xix-scrx-x0;
		  y=man[q].xiy-scry-y0;
		 }
	 rect.left=0,rect.top=0,rect.right=w,rect.bottom=h;
	 if(a==0)//DX
		{if(DXSBack1->BltFast(x+SCRW,y+SCRH,DXSgonh,&rect,
		    DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY)!=DD_OK) return;//�ڻ�����1��͸����ʾ
		 return;
		}
	 else	Alpha(x,y);
	 mans++;
	}
///////////////////////////////////////////////////////////////////////
	if(man[q].lb>=2) return;
	else	manmove(q);				  //�������ƶ�
//����ֵ==================================================================
	if(man[q].zd==1) setxtx(q,x,y);	  //���ڴ�ʱ������ʾ����ֵ����
	if(man[q].zs>4)//����ֵ
		{man[q].smz=man[q].smz-1;	  //��������smz����ʬ����ʧ����
		 if(man[q].smz<-200) {man[q].smz=0;man[q].p++;}
		}		
	else 
//========================================================================	
		man[q].p++;						  //��һ����
	if(man[q].p>=man[q].m1)	{bianfw(q);}//���������,���з�λת��

}
void game::Alpha(int x,int y)//DX
{	HDC hdc;
	if ( DXSBack1->GetDC(&hdc) != DD_OK) return;
	BitBlt(hDC0,0,0,w,h,hdc,x+SCRW,y+SCRH,SRCCOPY);
	BitBlt(hDC1,0,0,w,h,hdc,x+SCRW,y+SCRH,SRCCOPY);
	DXSBack1->ReleaseDC(hdc);
	if ( DXSgonh->GetDC(&hdc) != DD_OK) return;
	TransparentBlt2(hDC1,0,0,w,h,hdc,0,0,w,h,RGB(255,255,255));//͸����ʾ	  
	AlphaBlend(hDC1,0,0,w,h,hDC0,0,0,w,h,rBlend);//��͸������
	BitBlt(hdc,0,0,w,h,hDC1,0,0,SRCCOPY);
	DXSgonh->ReleaseDC(hdc);
	if(DXSBack1->BltFast
		(x+SCRW,y+SCRH,DXSgonh,&rect,DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY)!=DD_OK) return;//�ڻ�����1��͸����ʾ
}
///////////////////////////////////////////
//setxtx(int q,int x,int y)��ʾ����ֵ����
//	��[x,y]λ����ʾ��ǰ����q������ֵ�͹�����
//	����ֵ����ɫ��ʾ�����ࡢ�ȡ��ơ��̡������ࡢ�ϡ��ӵ͵��߱�ʾ��
//	���������Ǳ�ʾ����Խ�๥����Խ�ߡ�
///////////////////////////////////////////
void game::setxtx(int q,int x,int y)//��ʾ����ֵ����
{	 if(man[q].lb==0) return;
	 CString cc;
	 COLORREF col;
	 if(smz[1][man[q].js]>8) {cc="������";goto aa;}//������
	 if(smz[1][man[q].js]>6) {cc="�����  ";goto aa;}
	 if(smz[1][man[q].js]>4) {cc="����    ";goto aa;}
	 if(smz[1][man[q].js]>2) {cc="���      ";goto aa;}
							  cc="��        ";
aa:	 if(man[q].smz>=60) {col=RGB(0x0,0x00,0xff);goto bb;}//����ֵ
	 if(man[q].smz>=50) {col=RGB(0x0,0x88,0xff);goto bb;}
	 if(man[q].smz>=40) {col=RGB(0x0,0xff,0xff);goto bb;}
	 if(man[q].smz>=30) {col=RGB(0x0,0xff,0x88);goto bb;}
	 if(man[q].smz>=20) {col=RGB(0xff,0xff,0x0);goto bb;}
	 if(man[q].smz>=10) {col=RGB(0xff,0x88,0x0);goto bb;}
						 col=RGB(0xff,0x0,0x0);
bb:	 HDC hdc; //�豸�������	 
	 if (DXSBack1->GetDC(&hdc) != DD_OK) return;//��DXSBack1��
	 CDC* dc = CDC::FromHandle (hdc);
	 CFont *pOldFont;
	 pOldFont=dc->SelectObject(&Font);	//��������Ϊ4��impact��
	 dc->SetBkColor(col);				//�ֵ�ɫ
	 dc->SetTextColor(RGB(0x0,0x0,0x0));//��ɫ
	 dc->TextOut(x+SCRW+w/2,y+SCRH-10,cc,lstrlen(cc));//д�������ִ�
	 dc->SelectObject(pOldFont);		//�ָ�ԭ��������
	 CDC::DeleteTempMap( );
	 DXSBack1->ReleaseDC(hdc);//�ر�DXSBack1��
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
//**************************************************
//  BOOL getpic(CString cc,int p,int a) ����ͨͼƬ
//  A����ccָ����ѹ��ͼ�ΰ��е�p��ͼ�κ�ͼ�εĳߴ�w��h
//	B��a=0ʱȡ�õ�ͼ���ڶ��󻺴�ҳ��DXSgonh�С�
//	C��a=1ʱȡ�õ�ͼ����MemDC�С�
//**************************************************
//BOOL game::getpic(CString cc,int p,int a)//��ͼƬ
BOOL game::getpic(int q,int a)//��ͼƬ
{	int len;
	int p=man[q].p;
	if(p<0) return FALSE;
	BYTE *tmp;
	if(man[q].lb==0)//if(cc=="��")
	{if(p>RBUF-1) return FALSE;
	 len=rbufadd[p+1]-rbufadd[p];	//ȡ���ݿ鳤��
	 tmp=(BYTE *)new BYTE[len];
	 Memcpy0(tmp,rtmp+rbufadd[p],len);
	}
	if(man[q].lb==1)//if(cc=="��")
	{if(p>SBUF-1) return FALSE;
	 len=sbufadd[p+1]-sbufadd[p];	//ȡ���ݿ鳤��
	 tmp=(BYTE *)new BYTE[len];
	 Memcpy0(tmp,stmp+sbufadd[p],len);
	}
	if(man[q].lb==2)//if(cc=="��")
	{if(p>JBUF-6) return FALSE;
	 len=jbufadd[p+1]-jbufadd[p];	//ȡ���ݿ鳤��
	 tmp=(BYTE *)new BYTE[len];
	 Memcpy0(tmp,jtmp+jbufadd[p],len);
	}
	if(man[q].lb==3)//if(cc=="��")
	{if(p>WBUF-1) return FALSE;
	 len=wbufadd[p+1]-wbufadd[p];	//ȡ���ݿ鳤��
	 tmp=(BYTE *)new BYTE[len];
	 Memcpy0(tmp,wtmp+wbufadd[p],len);
	}
	LPBITMAPINFOHEADER bm=(BITMAPINFOHEADER *)tmp;//ͼ������ת��
	bm->biSize = sizeof(BITMAPINFOHEADER);
	w=bm->biWidth;	//ͼ�θ�
	h=bm->biHeight;	//ͼ�ο�
	if(a==0)
//DX----------------------------------------------------------------------
	{HDC hdc;//��ͼ��װ�붯��������DXSgonh
	 if ( DXSgonh->GetDC(&hdc) != DD_OK) return FALSE;//
	 StretchDIBits(hdc,0,0,w,h,0,0,w,h,tmp+256*sizeof(RGBQUAD)+bm->biSize,
				   (BITMAPINFO* )bm,DIB_RGB_COLORS,SRCCOPY);
	 DXSgonh->ReleaseDC(hdc);
//-----------------------------------------------------------------------
	}
	else
	{StretchDIBits(MemDC,0,0,w,h,0,0,w,h,tmp+256*sizeof(RGBQUAD)+bm->biSize,
	 			   (BITMAPINFO* )bm,DIB_RGB_COLORS,SRCCOPY);
	}
	delete[] tmp;
	return TRUE;
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
{	if(man[q].zs>3)		{man[q].zs++;goto aa;}	//����ֵ
	if(man[q].smz>-1&&man[q].smz<1) {man[q].zs=4;}//����ֵ
aa:	int a=400;
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
{	if(man[i].lb>=2)	return;		//�Ǿ��ﷵ��
	if(man[i].smz<1)	return;		//����ֵ
	if(find_p==1)					//find_p;������0������1
		{if(man[i].pk<1) return;}	//������·������,
	int stx,sty,qx,qy;
	switch(man[i].zs) 
		{case 2: {stx=9;sty=6;break;}//�ܲ���
	     case 1: {stx=4;sty=2;break;}//�߲���
		 default:{stx=2;sty=1;break;}
		}
	qx=man[i].x0-man[i].xix;		//x��ǰ��Ŀ��λ�ò�
	qy=man[i].y0-man[i].xiy;		//y��ǰ��Ŀ��λ�ò�
	if (qx==0&&qy==0)
	{if(find_p==1)					//find_p;������0������1
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
		 //-----------------------------
		}
	 return ;						//���ﷵ��
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
{	if(man[q].zs>3)	{setman(q);return;} //����ֵ
	int qx=man[q].x0-man[q].xix;		//x��ǰ��Ŀ��λ�ò�
	int qy=man[q].y0-man[q].xiy;		//y��ǰ��Ŀ��λ�ò�
	if(qx==0&&qy==0) 
		{if(man[q].zd==0) man[q].zs=0;	//Ϊ0,����Ϊվ,��λ����
		 goto aa;
		}	
	if(man[q].zd==0)					//û��
	{int a=rand()%2+1;					//��������ߡ���
	 if(man[q].lb==0) man[q].zs=1;		//��Ϊ��
	 if(man[q].lb==1) man[q].zs=dw[man[q].js][a];
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
//	loadmap(CString name)//����ͼ
//	������ƺõĶ��󳡾�(.dat)
//	�����ļ�(.dat)�ĸ�ʽ��
//	��1�У�Ϊ����ͼ��
//	��2�У�������,����һ����һ������
//	���,���,��ɫ,����ͼ�κ�,x,yλ��6������	
//**************************************************
void game::loadmap(CString name)//����ͼ
{ FILE *f;
  SetCurrentDirectory(appdir);//�õ�ǰĿ¼
  f=fopen(name,"r");
  if(f==NULL) {AfxMessageBox("û�е�ͼ�ļ�!!!");return;}
  fscanf(f,"%s\n",mapbak);		  //��ͼ����
  fscanf(f,"%d\n",&rs);			  //������
  if(rs>SU_LIANG)
		{fclose(f);return;}		  //�����������趨ֵ����
  int i;
  for (i=0;i<rs;i++)
	{fscanf(f,"%d,",&man[i].jisu);//���
	 fscanf(f,"%d,",&man[i].lb);  //���:  [0��1��2��3��]
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
	 if(man[i].lb==0)	man[i].smz=mansmz[0];//������ֵ
	 if(man[i].lb==1)	man[i].smz=smz[0][man[i].js];//������ֵ
	 if(man[i].lb<2) 
		 setman(man[i].jisu);	  //���û�����ֵ
	 if(getpic(i,0)==FALSE) continue;
	 man[i].w=w; man[i].h=h;	  //����ĳߴ�
	}
  fclose(f);
  SetCurrentDirectory(appdir);	  //�õ�ǰĿ¼
//  Insert();	//�����Ʒ
}
//**************************************************
// Insert() //�����Ʒ
// ��man[]��˳�������Ʒ������������rs��һ��
//**************************************************
void game::Insert() //�����Ʒ
{ srand( (unsigned)time( NULL ) );
  int a=rand()%(SCRP0*SCRP0*10)+5;				//���������Ʒ��
  for (int i=0;i<a;i++)
	{if(rs>SU_LIANG-2) return;//AfxMessageBox("����������!");
	 int i=rs;
	 man[i].jisu=i+1;				//���
	 man[i].lb=3;					//���:0��1��2��3��
	 man[i].p=rand()%4;				//����ͼ�κ�
	 man[i].xix=man[i].x0=rand()%(WIDTH*SCRP0);	//��ǰλ��x
	 man[i].xiy=man[i].y0=rand()%(HEIGHT*SCRP0);	//��ǰλ��y
//-----------------------------------------------------------
	 if(getpic(i,0)==FALSE) return;
	 man[i].w=w; man[i].h=h;	  //����ĳߴ�
	 rs++;//��������1
	}
}
//**************************************************
// Delete() //ɾ��
//	ɾ��ѡ �е�gno�Ŷ���
//**************************************************
void game::Delete(int q) //ɾ��
{	if(q==0||rs<2)	return;
	int n=man[q].jisu;
	for(int i=0;i<rs;i++)
	  if(man[i].jisu==n)
		{for (int j=i;j<rs-1;j++)	man[j]=man[j+1];//ɾ��gno
		 rs--;
		 return;
		}
}
//������DirectX�����////////////////////////////////////
BOOL game::InitDDraw(void)//���ܣ���ʼ��DirectDraw������
{   ddrval=DirectDrawCreate( NULL, &DXW, NULL );
	if(ddrval!= DD_OK ) return FALSE;//����DirectCraw����ʧ�ܷ���  
    ddrval=DXW->SetCooperativeLevel(GetActiveWindow(),DDSCL_NORMAL);
	if(ddrval!= DD_OK)  return FALSE;// ȡ�ô���ģʽʧ�ܷ���
    
	ddrval=DXW->SetDisplayMode(800,600,16);
	if(ddrval!= DD_OK) return FALSE;//������ʾģʽʧ�ܷ���
//========================================================================
    ddsd.dwSize = sizeof( ddsd );// ��������ҳ�� 
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps =DDSCAPS_PRIMARYSURFACE;
	ddsd.dwBackBufferCount=1;
    ddrval = DXW->CreateSurface( &ddsd, &DXSPrimary, NULL );
    if( ddrval != DD_OK )   return FALSE;//��������ҳ��ʧ�ܷ��� 
//=========================================================================
	Surface(WIDTH,HEIGHT);//����������ͼ����ҳ��0
	ddrval=DXW->CreateSurface(&ddsd,&DXSBack0, NULL);
	if (ddrval!=DD_OK) return FALSE;
//=========================================================================
	Surface(WIDTH,HEIGHT);//������ͼ�ƶ�����ҳ��1
	ddrval=DXW->CreateSurface(&ddsd,&DXSBack00, NULL);
	if (ddrval!=DD_OK) return FALSE;
//=========================================================================
	Surface(SCRWI0,SCRHE0);//����������ҳ��1//840=100+640+100,780 =150+480+150
	ddrval=DXW->CreateSurface(&ddsd,&DXSBack1, NULL);
	if (ddrval!=DD_OK) return FALSE;
//=========================================================================
	Surface(210,200);//�������󻺴�
	ddrval=DXW->CreateSurface(&ddsd,&DXSgonh, NULL);
	if (ddrval!=DD_OK) return FALSE;
	col.dwColorSpaceLowValue=RGB(255,255,255);//255,255,255
	col.dwColorSpaceHighValue=RGB(255,255,255);//͸���ؼ�ɫ100,100,100
	DXSgonh->SetColorKey(DDCKEY_SRCBLT,&col); //�ؼ�ɫ
	return TRUE;
}
void game::Surface(int w,int h)//���建��ҳ��Ĵ�С
{	ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize  = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
	ddsd.dwWidth = w;	//
	ddsd.dwHeight=h;	//
//	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_VIDEOMEMORY;
	//������ʾ�ڴ�Ϊ������
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN|DDSCAPS_SYSTEMMEMORY;
	//����ϵͳ�ڴ�Ϊ������
}
void game::Bk1ToPr(HDC scrhdc,CRect lpRect)//��ҳ1��ǰҳDX
{/////////////////////////////////////////////////////////////
/*	HDC hdc;
    if ( DXSBack1->GetDC(&hdc) != DD_OK) return;
	BitBlt(scrhdc,2,10,WIDTH,HEIGHT,hdc,SCRW,SCRH,SRCCOPY);
	DXSBack1->ReleaseDC(hdc);*/
	//��̨����1�ϵ�Դ����
	rect.left=SCRW,rect.top=SCRH,rect.right=WIDTH+SCRW,rect.bottom=HEIGHT+SCRH;
	if( DXSPrimary->BltFast
		(lpRect.left+5,lpRect.top+13,DXSBack1,&rect,DDBLTFAST_WAIT)!=DD_OK) 
	return ;
/////////////////////////////////////////////////////////////
} 

void game::FreeDDraw( void )//���ܣ��ͷ����е�DirectDraw����
{  if( DXW != NULL )
    {
	 if( DXSPrimary != NULL )	//����ҳ��
        { DXSPrimary->Release();DXSPrimary = NULL;}
	 if( DXSBack0 != NULL )
        { DXSBack0->Release();DXSBack0 = NULL;}
	 if( DXSBack00 != NULL )	//��ͼ�ƶ�����ҳ��0
        { DXSBack00->Release();DXSBack00=NULL;}
	 if( DXSBack1 != NULL )	//��ͼ�ƶ�����ҳ��1
        { DXSBack1->Release();DXSBack1 = NULL;}
	 if( DXSgonh != NULL )	//���󻺴�
        { DXSgonh->Release(); DXSgonh = NULL; }
        DXW->Release(); DXW = NULL;
    }	
}

void game::Memcpy0(unsigned char *mu,unsigned char *yu,int z)
{//memcpy(mu,yu,z);
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
