#include "常数定义.h"

//定义结构----------------------------------------------------------------------
typedef struct 
 {	short int x;
	short int y;
 } PATHN;//搜索整理路径
typedef struct 
 {	short int qi;		//动作起点
	short int bc;		//动作步数
 } JCDZ;	//人或兽的动作结构
typedef struct
{	short int jisu;		//序号
	short int xix,xiy;	//角色座标
	short int x0,y0;	//目标位置
	short int w,h;		//对象尺寸
	short int lb;		//类别:  [0人1兽2景]
	short int p;		//计数
	//以下人、动物使用
	short int m0,m1;	//位置初值、终值
	short int zs;		//动作:人[0站1走2刺3劈4倒]
						//动作:兽[0站1走2跑3斗4倒5尸]
	short int js;		//角色:人[0男1女]
						//角色:兽[0豹1狼2鹿3马4雀5羊6猪]
	short int fw;		//方位:	 [0南1西南2西3西北4北5东北6东7东南]
	short int zd;		//当前状态[0,1打斗]
	short int smz;		//生命值
	//以下搜索使用
	PATHN	  ph[250];	//搜索的路径
	short int pk;		//路径长
	short int fid;		//路径计数
	short int fx,fy;	//保留目标点
} MAN;		//对象结构
//定义类-------------------------------------------------------------------------
class game 
{public: game();	//构造函数
 virtual~game();	//析构函数
 //A、基本游戏功能-------------------------------
 //变量定义
 public://公有,外部可调用
 MAN		man[SU_LIANG];	//定义对象变量,数量为SU_LIANG
 HDC		MemDC;			//对象设备句柄
 HBITMAP	OldMak;
 HDC		hScrDC;			//屏幕设备句柄
 HBITMAP	bitmap;			//地图位图内存

 HBITMAP	hBMP0;
 HBITMAP	hBMP1;
 HDC		hDC0;
 HDC		hDC1;

 CString	dir;			//数据路径
 short int 	rs;				//当前对象数
 short int 	scrx,scry;		//地图移动量
 CString	mapbak;			//地图块名
 int		w,h;			//对象图片宽、高
 char appdir[256];			//当前目录
 short int mansmz[5];		//0生命1经验2金钱3猎物4
 short int da;
 private://私有,类内部使用
 CFont Font;
 short int 	sys;			//当前运行系统
  BLENDFUNCTION rBlend;			//半透明
 //函数定义
 public://公有,外部可调用。----------------------------------------
 BOOL init();						//初始化
 void exit();						//退出
 void Memcpy0(unsigned char *mu,unsigned char *yu,int z);
 void loadmap(CString name);		//调入地图
 BOOL loadbmp(CString cc);			//调BMP图片[2章]
// BOOL getpic(CString cc,int p,int a);//调图片DX
 BOOL getpic(int q,int a);//调图片DX
 void Alphasetobj (int q,int a);	//对象显示
 void Alpha(int x,int y);
 void setman (int q);				//设置活动对象初值
 void sort();						//排序(冒泡法)
 void TransparentBlt2(HDC hdc0,		//目标DC
		int nX0,int nY0,int nW0,int nH0,//目标左坐标,目标宽高宽
		HDC hdc1,						//源DC
		int nX1,int nY1,int nW1,int nH1,//源起点坐标,源宽高宽
		UINT Tcol);						//透明色,COLORREF类型
 BOOL inscreer(int i);				//在显示区？
 void setxtx(int q,int x,int y);	//显示生命值函数
 private://私有,类内部使用

 int  getsys();						//识别系统
 void bianfw (int q);				//方位转换
 void manmove(int i);				//活动对象的移动
 //B、扩展游戏功能[压缩资源包使用]------------
 //变量定义
 public://公有,外部可调用
 short int 	mann;				//主角下标
 short int 	mans;				//显示区对象数
 short int 	find_p;				//无搜索0有搜索1
 short int 	SCRP0;				//实际地图倍数	
 CFile		sfile,rfile,jfile,wfile;	//压缩资源包的文件指针
 BYTE		*stmp,*rtmp,*jtmp,*wtmp;	//压缩的内存变量
 int		sbufadd[SBUF];		//兽的资源指针
 short int	sbufx  [SBUF];		//兽的偏移量x
 short int	sbufy  [SBUF];		//兽的偏移量y
 int		rbufadd[RBUF];		//人的资源指针
 short int	rbufx  [RBUF];		//人的偏移量x
 short int	rbufy  [RBUF];		//人的偏移量y
 int		jbufadd[JBUF];		//景的资源指针
 int		wbufadd[10];
 //C、编辑功能的变量
 short int 	edi;				//编辑标志
//以下是DirectX变量、函数定义////////////////////////////////
 public://公有,外部可调用
 LPDIRECTDRAWSURFACE DXSBack1;	//主缓存页面1
 LPDIRECTDRAWSURFACE DXSBack0;	//背景地图缓存页面0
 LPDIRECTDRAWSURFACE DXSBack00;	//地图移动缓存页面0
 void FreeDDraw(void );			//释放所有的DirectDraw对象
 void Bk1ToPr(HDC scrhdc,CRect lpRect);//后页1到前页
 RECT rect;
 private://私有,类内部使用
 DDSURFACEDESC		 ddsd; //页面描述
 HRESULT			 ddrval;
 LPDIRECTDRAW		 DXW;		// DXDraw对象
 DDCOLORKEY			 col;		//透明关键色
 LPDIRECTDRAWSURFACE DXSPrimary;// DXDraw主页面
 LPDIRECTDRAWSURFACE DXSgonh;	//对象缓存页面
 BOOL InitDDraw(void);			//初始化DirectDraw环境
 void Surface(int w,int h);		//定义缓存页面的大小

/////////////////////////////////////////////////////////////////////////////
 public://公有,外部可调用
 void Insert();			//加入
 void Delete(int q);	//删除
/*
//**************************************************
//  BOOL getpic(CString cc,int p,int a) 调普通图片
//  A、调cc指定的压缩图形包中第p个图形和图形的尺寸w、h
//	B、a=0时取得的图形在对象缓存页面DXSgonh中。
//	C、a=1时取得的图形在MemDC中。
//**************************************************
BOOL game::getpic(int q,int a)//调图片
{	int len;
	int p=man[q].p;
	if(p<0) return FALSE;
	BYTE *tmp;
	if(man[q].lb==0)//if(cc=="人")
	{if(p>RBUF-1) return FALSE;
	 len=rbufadd[p+1]-rbufadd[p];	//取数据块长度
	 tmp=(BYTE *)new BYTE[len];
	 Memcpy0(tmp,rtmp+rbufadd[p],len);
	}
	if(man[q].lb==1)//if(cc=="兽")
	{if(p>SBUF-1) return FALSE;
	 len=sbufadd[p+1]-sbufadd[p];	//取数据块长度
	 tmp=(BYTE *)new BYTE[len];
	 Memcpy0(tmp,stmp+sbufadd[p],len);
	}
	if(man[q].lb==2)//if(cc=="景")
	{if(p>JBUF-6) return FALSE;
	 len=jbufadd[p+1]-jbufadd[p];	//取数据块长度
	 tmp=(BYTE *)new BYTE[len];
	 Memcpy0(tmp,jtmp+jbufadd[p],len);
	}
	if(man[q].lb==3)//if(cc=="物")
	{if(p>WBUF-1) return FALSE;
	 len=wbufadd[p+1]-wbufadd[p];	//取数据块长度
	 tmp=(BYTE *)new BYTE[len];
	 Memcpy0(tmp,wtmp+wbufadd[p],len);
	}
	LPBITMAPINFOHEADER bm=(BITMAPINFOHEADER *)tmp;//图形数据转换
	bm->biSize = sizeof(BITMAPINFOHEADER);
	w=bm->biWidth;	//图形高
	h=bm->biHeight;	//图形宽
	if(a==0)
//DX----------------------------------------------------------------------
	{HDC hdc;//将图形装入动画缓存区DXSgonh
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
//  setobj(int q) 对象显示
//	调入由man[q].lb指出的，不同的man[q].p图片，和偏移值。
//  将对象q在各自的当前位置x,y上以透明方式TransparentBlt2显示。
//	之后进行移动或方位转换的功能。
//  为防止闪烁，所有对象先显示在暂存区BkDC1，一屏完成后再翻转到主屏上。
//**************************************************
void game::Alphasetobj(int q,int a)//对象显示
{	if(a==1&&man[q].lb==2) return;
	if(man[q].zs>5)			//生命值
		{Delete(q);return;}	//删除对象返回
	CString cc;
	int x=man[q].xix-scrx-man[q].w/2;	//x当前位置
	int y=man[q].xiy-scry-man[q].h;		//y当前位置
	if(inscreer(q))//在显示区？
	{if(getpic(q,0)==FALSE) return;		//调图形，出错返回
	 if(man[q].lb<2)//调角色的偏移位置
		 {int x0=0,y0=0;
		  if(man[q].lb==0) {x0=rbufx[man[q].p];y0=rbufy[man[q].p];}
		  if(man[q].lb==1) {x0=sbufx[man[q].p];y0=sbufy[man[q].p];}
		  if(man[q].fw>4) x0=w-x0;//是东北、东、东南方位
		  x=man[q].xix-scrx-x0;
		  y=man[q].xiy-scry-y0;
		 }
	 rect.left=0,rect.top=0,rect.right=w,rect.bottom=h;
	 if(a==0)//DX
		{if(DXSBack1->BltFast(x+SCRW,y+SCRH,DXSgonh,&rect,
		    DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY)!=DD_OK) return;//在缓存区1上透明显示
		 return;
		}
	 else	Alpha(x,y);
	 mans++;
	}
///////////////////////////////////////////////////////////////////////
	if(man[q].lb>=2) return;
	else	manmove(q);				  //活动对象的移动
//生命值==================================================================
	if(man[q].zd==1) setxtx(q,x,y);	  //正在打时，调显示生命值函数
	if(man[q].zs>4)//生命值
		{man[q].smz=man[q].smz-1;	  //动物死后，smz用于尸体消失计数
		 if(man[q].smz<-200) {man[q].smz=0;man[q].p++;}
		}		
	else 
//========================================================================	
		man[q].p++;						  //下一动作
	if(man[q].p>=man[q].m1)	{bianfw(q);}//本动作完成,进行方位转换

}
void game::Alpha(int x,int y)//DX
{	HDC hdc;
	if ( DXSBack1->GetDC(&hdc) != DD_OK) return;
	BitBlt(hDC0,0,0,w,h,hdc,x+SCRW,y+SCRH,SRCCOPY);
	BitBlt(hDC1,0,0,w,h,hdc,x+SCRW,y+SCRH,SRCCOPY);
	DXSBack1->ReleaseDC(hdc);
	if ( DXSgonh->GetDC(&hdc) != DD_OK) return;
	TransparentBlt2(hDC1,0,0,w,h,hdc,0,0,w,h,RGB(255,255,255));//透明显示	  
	AlphaBlend(hDC1,0,0,w,h,hDC0,0,0,w,h,rBlend);//半透明处理
	BitBlt(hdc,0,0,w,h,hDC1,0,0,SRCCOPY);
	DXSgonh->ReleaseDC(hdc);
	if(DXSBack1->BltFast
		(x+SCRW,y+SCRH,DXSgonh,&rect,DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY)!=DD_OK) return;//在缓存区1上透明显示
}*/
};