/*********************************
[ѧVC����Ϸ]
������������ƣ������� 2004.7
E-mail:  cqtml@163.com
**********************************/
#include "stdafx.h"
#include "game_��ͼ.h"
extern unsigned short dw[7][6];
gamemap:: gamemap(){}	//���캯��
gamemap::~gamemap()
{DeleteObject(pen1); //ɾ������Ѱ·����
}	//��������
//***********************************************
//	B��	����С��ͼ��λ�á��ߴ�
//	C��	SMAP-װ��С��ͼ
//		����4������pen0��pen1��pen��penz�༭��
//	D��	���ü�����ʼ����
//***********************************************
void gamemap::initmap()//��ʼ����ͼ����
{	mapt=10,mapb=120;			//С��ͼ����
	maph=mapb-mapt;				//С��ͼ��
	mapl=WIDTH+6;				//С��ͼ��
	mapr=mapl+maph*WIDTH/HEIGHT;//С��ͼ�ұ��ǰ���ʾ������ȡ��
	mapw=mapr-mapl;				//С��ͼ��

	hScrDC=CreateDC("DISPLAY", NULL, NULL, NULL);	//������Ļ�豸���

	SMAP  =CreateCompatibleDC(hScrDC);				//����С��ͼ�豸���
	mapbit=CreateCompatibleBitmap(hScrDC,mapw,maph);//����С��ͼλͼ�ڴ�
	SelectObject(SMAP,mapbit);						//С��ͼλͼ�ڴ���С��ͼ�豸�������
	pen0.CreatePen(PS_SOLID,1,RGB(0x0,0xf0,0xf0));	//С��ͼ�еķ��񻭱�
	pen1.CreatePen(PS_SOLID,1,RGB(0x60,0x60,0x60));	//����Ѱ·����
	DeleteDC(hScrDC);								//ɾ����Ļ�豸���
	fls=0;			//��˸��־
	movemap=0;		//��ͼ�ƶ���
	init();
}
void gamemap::exitmap()//�˳�
{	DeleteDC(BK);
	DeleteObject(bi);
	DeleteObject(mapbit);//ɾ��С��ͼλͼ�ڴ�
	DeleteDC(SMAP);		//ɾ��С��ͼ�豸���
	DeleteObject(pen0); //ɾ��С��ͼ�еķ��񻭱�
	exit();
}
//**************************************************
// mlmap()//��ͼ���ƶ�ƴ��
// ����ʹ�õ��ǵ���ͼ�޷�ƴ���ƶ��㷨��
//**************************************************
void gamemap::mlmap()//��ͼ���ƶ�ƴ��
{	if(	movemap==0)		//��ͼ�ƶ���
		BitBlt(BkDC1,0,0,WIDTH,HEIGHT,BkDC0,0,0,SRCCOPY);
	else
	{int gx=scrx%WIDTH,gy=scry%HEIGHT;
	 BitBlt(BK,   0,0,        WIDTH-gx,HEIGHT,BkDC0,gx,0,SRCCOPY);//��ͼ�����ƶ�
	 BitBlt(BK,   WIDTH-gx,   0,gx,HEIGHT,    BkDC0,0,0, SRCCOPY);
	 BitBlt(BkDC1,0,0,        WIDTH,HEIGHT-gy,BK,0,gy,   SRCCOPY);//��ͼ�����ƶ�
	 BitBlt(BkDC1,0,HEIGHT-gy,WIDTH,gy,       BK,0,0,    SRCCOPY);
	}
	sort();			 //��Y��������,��������ʾʱ�ֳ�ǰ��λ��
	movemap=0;		//��ͼ�ƶ���
}
//**************************************************
//	getsmap()//����С��ͼ
//	A��������鵽BkDC0��ͼ�豸���
//	B��ȫ��ͼ����С��ͼ��SMAP
//	C��ȫ��ͼ����΢����SMAP
//**************************************************
void gamemap::getsmap()//����С��ͼ
{//A��������鵽BkDC0��ͼ�豸���
	char name[256];
	sprintf(name,"%s%s",dir,mapbak);
	loadbmp(name);
	SelectObject(BkDC0,bitmap);//
	DeleteObject(bitmap);			//ɾ���ϴε�λͼ�ڴ档
//B��ȫ��ͼ����С��ͼ
	int i,j;
	COLORREF col=RGB(255,255,255);
	for(i=0;i<mapw;i=i+mapw/SCRP0)
		for(j=0;j<maph;j=j+maph/SCRP0)
			   TransparentBlt2
					(SMAP,i,j,mapw/SCRP0,maph/SCRP0,
					 BkDC0,0,0,WIDTH,HEIGHT,col);//͸����ʾ
//C��ȫ��ͼ����΢��
	int wi=WIDTH*SCRP0,he=HEIGHT*SCRP0;
	for(int q=0;q<rs;q++)
	  if(man[q].lb==2)					//�Ǿ���
		{if(getpic("��",man[q].p)==FALSE) continue;//��ȡλͼ�ļ�cc
		 int x=(man[q].xix-w/4)*mapw;	//x��ǰλ��
		 int y=(man[q].xiy-h)*maph;		//y��ǰλ��
		 TransparentBlt2
			 (SMAP,x/wi,y/he,(w*mapw)/(wi*2/3),(h*maph)/(he*2/3),
			  MemDC,0,0,w,h,col);//͸����ʾ
		}
//	OldMak=(HBITMAP)SelectObject(MemDC,bitya);//?????????????????
}
//**************************************************
//	movesmap(int x0,int y0)//�ƶ���ͼ
//	��곬���߽�ʱ���ı�(scrx,scry)ʹ������������Ӧ���ƶ���
//	ÿ��������ƶ������г����⡣
//**************************************************
void gamemap::movesmap(int x0,int y0)//�ƶ���ͼ
{	int a=3;
	if(edi==1) a=1;	//�༭ʱʹ�㷨�򵥡�
	if(x0>SCRWI-10)	//��곬���ұ߽�
		{scrx=scrx+GX/a;if(scrx>WIDTH*(SCRP0-1)) scrx=WIDTH*(SCRP0-1);}
	if(x0<10)		//��곬����߽�
		{scrx=scrx-GX/a;if(scrx<0) scrx=0;}
	if(y0>SCRHE-10)	//��곬���±߽�
		{scry=scry+GY/a;if(scry>HEIGHT*(SCRP0-1)) scry=HEIGHT*(SCRP0-1);}
	if(y0<10)		//��곬���ϱ߽�
		{scry=scry-GY/a;if(scry<0) scry=0;}
	movemap=1;		//��ͼ�ƶ���
}
//**************************************************
//	BOOL dingweimap(int x,int y)//��λ��ͼ
//	�����ɰ����������õġ�
//	���ݰ���λ�ã��ı�(scrx,scry)ʹ�����������ƶ�
//**************************************************
BOOL gamemap::dingweimap(int x,int y)//��λ��ͼ
{	if(y>mapt&&y<mapb&&x>mapl&&x<mapr)//��С��ͼ�ϰ���
	{scrx=(x-mapl)*WIDTH *SCRP0/mapw-mapw*2;
	 scry=(y-mapt)*HEIGHT*SCRP0/maph-maph*2;
	 scrx=(scrx/GX)*GX;
	 scry=(scry/GY)*GY;
	 //���б߽��⡣
	 if(scrx>WIDTH*(SCRP0-1)) scrx=WIDTH*(SCRP0-1);
	 if(scrx<0) scrx=0;
	 if(scry>HEIGHT*(SCRP0-1)) scry=HEIGHT*(SCRP0-1);
	 if(scry<0) scry=0;
	 return TRUE;
	}
	return FALSE;
}
//**************************************************
// smlmap(HDC hdc)//��ʾС��ͼ
//	0��С��ͼˢ��
//	A����С��ͼ����ʾ������
//	B����ʾ������С��ͼ���ƶ�
//	C����С��ͼ����ʾ����Ѱ·��·��
//**************************************************
void gamemap::smlmap(HDC dc0)//��ʾС��ͼ
{	if(rs<1||SCRP0<1) return;
	CDC* dc = CDC::FromHandle (dc0);
//0��С��ͼˢ��
	BitBlt(dc0,mapl,mapt,mapw,maph,SMAP,0,0,SRCCOPY);//С��ͼˢ��
//A����С��ͼ����ʾ������
	CPen *old;
	old=dc->SelectObject(&pen0);//����ɫ����
	int mapw0=mapw/SCRP0,maph0=maph/SCRP0-1;

	int scrx0=mapl+(scrx*mapw)/(WIDTH*SCRP0);
	int scry0=mapt+(scry*maph)/(HEIGHT*SCRP0);
	//���߻�����
	dc->MoveTo(scrx0,scry0);		//���ϵ�
	dc->LineTo(scrx0+mapw0,scry0);	//���ϵ�
	dc->LineTo(scrx0+mapw0,scry0+maph0);//���µ�
	dc->LineTo(scrx0,scry0+maph0);	//���µ�
	dc->LineTo(scrx0,scry0);		//���ϵ�
//B����ʾ������С��ͼ���ƶ�
	for(int q=0;q<rs;q++)
	{	COLORREF col=RGB(0x0,0x0,0x0);//

		scrx0=(man[q].xix*mapw)/(WIDTH*SCRP0)-1;
		scry0=(man[q].xiy*maph)/(HEIGHT*SCRP0)-2;
		if(scrx0<1||scry0<1) continue;
		if(man[q].jisu==0)
		 {mann=q;		//ȡ��̬�������±�
		  if(fls==0){fls=1;col=RGB(0xf0,0xf0,0xf0);}//����˸	
		  else		{fls=0;col=RGB(0xf0,0x0,0x0);}  //��
		  dc->SetPixel(mapl+scrx0+1,mapt+scry0,  col);
		  dc->SetPixel(mapl+scrx0+1,mapt+scry0+1,col);
		 }
		if(man[q].lb==2) continue;
		dc->SetPixel(mapl+scrx0,mapt+scry0,  col);
		dc->SetPixel(mapl+scrx0,mapt+scry0+1,col);

	}
//C����С��ͼ����ʾ����Ѱ·��·��
	setfind(dc,old);				//��Ѱ·ʱ�ã���ʾ����Ѱ·��·��

	dc->SelectObject(old);
	CDC::DeleteTempMap( );
}
//**************************************************
// int leftdown(HDC hdc,int x,int y)//�����
//	�����ɰ����������õġ�
//	A������ʾ���������������ǵ�Ŀ��λ�ã���A*�㷨Ѱ·
//	B����С��ͼ������������λ��ͼ��
//	����Ѱ·������Ѱ·��ʱ�䡣
//**************************************************
int gamemap::leftdown(HDC hdc,int x,int y)//�����
{	int fidtim=0;
	if(x>0&&x<WIDTH&&y>0&&y<HEIGHT&&edi==0)	//����ʾ��,�Ǳ༭̬
	{int i=mann;					//ֻ������ȡĿ���
	 man[i].x0=x-2+scrx;
	 man[i].y0=y-10+scry;
	 man[i].p=man[i].m1-1;			//��ֹ��ǰ����
	}
	if(dingweimap(x,y)==TRUE)		//��С��ͼ�ϵ����,����λ��ͼ
					smlmap(hdc);	//��ʾС��ͼ
	return fidtim;
}
//////////////////////////////////////////////////////////////////////
void gamemap::setfind(CDC* dc,CPen *old)//��Ѱ·ʱ�ã���ʾ����Ѱ·��·��
{//C����С��ͼ����ʾ����Ѱ·��·��
	int i=mann;//ȡ����
	dc->SelectObject(old);
	if(man[i].pk<1) 
	{	CDC::DeleteTempMap( );
		return;
	}
	int x,y,x0,y0;
	x=man[i].ph[0].x*GX;
	y=man[i].ph[0].y*GY;
	x0=mapl+(x*mapw)/(WIDTH*SCRP0);
	y0=mapt+(y*maph)/(HEIGHT*SCRP0);
	old=dc->SelectObject(&pen1);//����ɫ����
	for (int j=1;j<man[i].pk;j++)
		{dc->MoveTo(x0,y0);
		 x=man[i].ph[j].x*GX;
		 y=man[i].ph[j].y*GY;
		 x0=mapl+(x*mapw)/(WIDTH*SCRP0);
		 y0=mapt+(y*maph)/(HEIGHT*SCRP0);
		 dc->LineTo(x0,y0);
		}
	x0=mapl+(man[i].fx*mapw)/(WIDTH*SCRP0);
	y0=mapt+(man[i].fy*maph)/(HEIGHT*SCRP0);
	dc->LineTo(x0,y0);
}