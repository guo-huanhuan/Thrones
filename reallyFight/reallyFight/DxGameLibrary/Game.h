#include "��������.h"

//����ṹ----------------------------------------------------------------------
typedef struct 
 {	short int x;
	short int y;
 } PATHN;//��������·��
typedef struct 
 {	short int qi;		//�������
	short int bc;		//��������
 } JCDZ;	//�˻��޵Ķ����ṹ
typedef struct
{	short int jisu;		//���
	short int xix,xiy;	//��ɫ����
	short int x0,y0;	//Ŀ��λ��
	short int w,h;		//����ߴ�
	short int lb;		//���:  [0��1��2��]
	short int p;		//����
	//�����ˡ�����ʹ��
	short int m0,m1;	//λ�ó�ֵ����ֵ
	short int zs;		//����:��[0վ1��2��3��4��]
						//����:��[0վ1��2��3��4��5ʬ]
	short int js;		//��ɫ:��[0��1Ů]
						//��ɫ:��[0��1��2¹3��4ȸ5��6��]
	short int fw;		//��λ:	 [0��1����2��3����4��5����6��7����]
	short int zd;		//��ǰ״̬[0,1��]
	short int smz;		//����ֵ
	//��������ʹ��
	PATHN	  ph[250];	//������·��
	short int pk;		//·����
	short int fid;		//·������
	short int fx,fy;	//����Ŀ���
} MAN;		//����ṹ
//������-------------------------------------------------------------------------
class game 
{public: game();	//���캯��
 virtual~game();	//��������
 //A��������Ϸ����-------------------------------
 //��������
 public://����,�ⲿ�ɵ���
 MAN		man[SU_LIANG];	//����������,����ΪSU_LIANG
 HDC		MemDC;			//�����豸���
 HBITMAP	OldMak;
 HDC		hScrDC;			//��Ļ�豸���
 HBITMAP	bitmap;			//��ͼλͼ�ڴ�

 HBITMAP	hBMP0;
 HBITMAP	hBMP1;
 HDC		hDC0;
 HDC		hDC1;

 CString	dir;			//����·��
 short int 	rs;				//��ǰ������
 short int 	scrx,scry;		//��ͼ�ƶ���
 CString	mapbak;			//��ͼ����
 int		w,h;			//����ͼƬ����
 char appdir[256];			//��ǰĿ¼
 short int mansmz[5];		//0����1����2��Ǯ3����4
 short int da;
 private://˽��,���ڲ�ʹ��
 CFont Font;
 short int 	sys;			//��ǰ����ϵͳ
  BLENDFUNCTION rBlend;			//��͸��
 //��������
 public://����,�ⲿ�ɵ��á�----------------------------------------
 BOOL init();						//��ʼ��
 void exit();						//�˳�
 void Memcpy0(unsigned char *mu,unsigned char *yu,int z);
 void loadmap(CString name);		//�����ͼ
 BOOL loadbmp(CString cc);			//��BMPͼƬ[2��]
// BOOL getpic(CString cc,int p,int a);//��ͼƬDX
 BOOL getpic(int q,int a);//��ͼƬDX
 void Alphasetobj (int q,int a);	//������ʾ
 void Alpha(int x,int y);
 void setman (int q);				//���û�����ֵ
 void sort();						//����(ð�ݷ�)
 void TransparentBlt2(HDC hdc0,		//Ŀ��DC
		int nX0,int nY0,int nW0,int nH0,//Ŀ��������,Ŀ���߿�
		HDC hdc1,						//ԴDC
		int nX1,int nY1,int nW1,int nH1,//Դ�������,Դ��߿�
		UINT Tcol);						//͸��ɫ,COLORREF����
 BOOL inscreer(int i);				//����ʾ����
 void setxtx(int q,int x,int y);	//��ʾ����ֵ����
 private://˽��,���ڲ�ʹ��

 int  getsys();						//ʶ��ϵͳ
 void bianfw (int q);				//��λת��
 void manmove(int i);				//�������ƶ�
 //B����չ��Ϸ����[ѹ����Դ��ʹ��]------------
 //��������
 public://����,�ⲿ�ɵ���
 short int 	mann;				//�����±�
 short int 	mans;				//��ʾ��������
 short int 	find_p;				//������0������1
 short int 	SCRP0;				//ʵ�ʵ�ͼ����	
 CFile		sfile,rfile,jfile,wfile;	//ѹ����Դ�����ļ�ָ��
 BYTE		*stmp,*rtmp,*jtmp,*wtmp;	//ѹ�����ڴ����
 int		sbufadd[SBUF];		//�޵���Դָ��
 short int	sbufx  [SBUF];		//�޵�ƫ����x
 short int	sbufy  [SBUF];		//�޵�ƫ����y
 int		rbufadd[RBUF];		//�˵���Դָ��
 short int	rbufx  [RBUF];		//�˵�ƫ����x
 short int	rbufy  [RBUF];		//�˵�ƫ����y
 int		jbufadd[JBUF];		//������Դָ��
 int		wbufadd[10];
 //C���༭���ܵı���
 short int 	edi;				//�༭��־
//������DirectX��������������////////////////////////////////
 public://����,�ⲿ�ɵ���
 LPDIRECTDRAWSURFACE DXSBack1;	//������ҳ��1
 LPDIRECTDRAWSURFACE DXSBack0;	//������ͼ����ҳ��0
 LPDIRECTDRAWSURFACE DXSBack00;	//��ͼ�ƶ�����ҳ��0
 void FreeDDraw(void );			//�ͷ����е�DirectDraw����
 void Bk1ToPr(HDC scrhdc,CRect lpRect);//��ҳ1��ǰҳ
 RECT rect;
 private://˽��,���ڲ�ʹ��
 DDSURFACEDESC		 ddsd; //ҳ������
 HRESULT			 ddrval;
 LPDIRECTDRAW		 DXW;		// DXDraw����
 DDCOLORKEY			 col;		//͸���ؼ�ɫ
 LPDIRECTDRAWSURFACE DXSPrimary;// DXDraw��ҳ��
 LPDIRECTDRAWSURFACE DXSgonh;	//���󻺴�ҳ��
 BOOL InitDDraw(void);			//��ʼ��DirectDraw����
 void Surface(int w,int h);		//���建��ҳ��Ĵ�С

/////////////////////////////////////////////////////////////////////////////
 public://����,�ⲿ�ɵ���
 void Insert();			//����
 void Delete(int q);	//ɾ��
/*
//**************************************************
//  BOOL getpic(CString cc,int p,int a) ����ͨͼƬ
//  A����ccָ����ѹ��ͼ�ΰ��е�p��ͼ�κ�ͼ�εĳߴ�w��h
//	B��a=0ʱȡ�õ�ͼ���ڶ��󻺴�ҳ��DXSgonh�С�
//	C��a=1ʱȡ�õ�ͼ����MemDC�С�
//**************************************************
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
}*/
};