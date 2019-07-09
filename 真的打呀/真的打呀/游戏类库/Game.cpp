/*********************************
[学VC编游戏]
编著、程序设计：唐明理 2004.7
E-mail:  cqtml@163.com
Downlaod by http://www.codefans.net
**********************************/
#include "stdafx.h"
#include "game.h"

JCDZ zjdz[6]={0,5,40,10,120,10,200,10,280,10,360,5};//人动作结构400幅
			//0站,1走,  2刺,   3劈,   4倒    5尸
JCDZ zjdw[6]={0,5,40,10,120,10,200,10,280,10,360,5};//兽动作结构400幅
			//0站,1走,  2跑,   3斗,   4倒,   5尸
unsigned short dw[7][6]={0,1,1,3,4,5,	//0豹,无跑
						 0,1,2,3,4,5,	//1狼,
						 0,1,1,3,4,5,	//2猪,无跑
						 0,1,2,3,4,5,	//3鹿,
						 0,2,2,2,4,5,	//4马,无走、斗
						 0,1,1,1,4,5,	//5羊,无跑、斗
						 0,1,1,3,4,5	//6雀,无跑
						 };
////////////////////////////////////////////////////////////////////////////
game:: game(){}	//构造函数
game::~game(){}	//析构函数
//****************************************************************
// init() 初始化,建立图形处理环境
//	BkDC0-装载背景地面
//	BkDC1-在此生成即时场景，在1个时钟周期后翻转到当前显示屏。
//	MemDC-调入的对象图片。
//****************************************************************
BOOL game::init()//初始化
{	hScrDC=CreateDC("DISPLAY", NULL, NULL, NULL);	//创建屏幕设备句柄
	BkDC0 =CreateCompatibleDC(hScrDC);				//创建地图设备句柄
	BkDC1 =CreateCompatibleDC(hScrDC);				//创建暂存设备句柄
	bit0  =CreateCompatibleBitmap(hScrDC,WIDTH,HEIGHT);//创建暂存位图内存0
	bit1  =CreateCompatibleBitmap(hScrDC,WIDTH,HEIGHT);//创建暂存位图内存1
	SelectObject(BkDC1,bit1);						//暂存位图内存1与暂存设备句柄关联
	OldMak=(HBITMAP)SelectObject(BkDC0,bit0);		//暂存位图内存0与地图设备句柄关联
	MemDC =CreateCompatibleDC(hScrDC);				//创建对象设备句柄
//==================================================
	BK =CreateCompatibleDC(hScrDC);//创建暂存设备句柄
	bi =CreateCompatibleBitmap(hScrDC,WIDTH,HEIGHT);
	SelectObject(BK,bi);

	bitya=CreateCompatibleBitmap(hScrDC,220,200);
	DeleteDC(hScrDC);								//删除屏幕设备句柄
	rBlend.BlendOp = AC_SRC_OVER;	//
	rBlend.BlendFlags = 0;			//
	rBlend.AlphaFormat = 0;			//
	rBlend.SourceConstantAlpha=140;
//==================================================
	GetCurrentDirectory(256,appdir);//取当前目录
	dir=appdir;
	if(dir.Right(8)=="运行程序")
			dir="图片/";
	else	
		dir="../运行程序/图片/";	//图片路径
//==================================================
	sys=getsys();	//取当前系统
	scrx=0;scry=0;
	rs=0;			//对象数置0
	find_p=0;		//无搜索0有搜索1
	stmp=NULL;rtmp=NULL;jtmp=NULL;
	return TRUE;
}
//**************************************************
//  exit() 退出, 删除图形处理环境
//**************************************************
void game::exit()//退出
{	DeleteDC(BK);
	DeleteObject(bi);
	DeleteObject(bitya);
	DeleteObject(bit0);	//删除暂存位图内存
	DeleteObject(bit1);	//删除暂存位图内存
	DeleteDC(BkDC0);	//删除地图设备句柄
	DeleteDC(BkDC1);	//删除暂存设备句柄
	DeleteDC(MemDC);	//删除对象设备句柄
	DeleteDC(hScrDC);	//删除屏幕设备句柄
}
//****************************************************
//	getsys()//识别操作系统
//	使用TransparentBlt()透明显示的需要；
//	是WIN2000，直接调用TransparentBlt()；否则调用自编的。
//****************************************************
int game::getsys()//识别操作系统
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
//	inscreer(int i)//在显示区？
//**********************************************************
BOOL game::inscreer(int i)//在显示区？
{	int xs=man[i].xix-scrx-man[i].w/2;		//x当前位置
	int ys=man[i].xiy-scry-man[i].h;		//y当前位置
	if(xs>(-man[i].w+2)&&xs<WIDTH&&ys>(-man[i].h+10)&&ys<HEIGHT)
			return TRUE;
	else	return FALSE;
}

//**********************************************************
//  sort() 排序(冒泡法)
//  将rs个对象序列对Y位置进行排序;用于在显示时分出前后位置。
//**********************************************************
void game::sort()//排序(冒泡法)
{	MAN man0;
	for(int a=0;a<rs-1;a++)
	 for(int b=a+1;b<rs;b++)
		if(man[a].xiy>man[b].xiy)//前数大于后数
			{man0=man[a];		 //两数交换
			 man[a]=man[b];
			 man[b]=man0;
			}					 //排序结果，当前位置Y小的在前。							
	mans=0;						 //显示区对象数置0
}
//**************************************************
//  getobjwh(int q) 取对象的尺寸
//  取序号q对象的尺寸(宽man[q].w高man[q].h)。
//**************************************************
void game::getobjwh(int q)//取对象的尺寸
{	CString cc;
	if(man[q].lb==0)	{cc="人";}
	if(man[q].lb==1)	{cc="兽";}	
	if(man[q].lb==2) 	{cc="景";}
	if(getpic(cc,man[q].p)==FALSE) return;
	man[q].w=w; man[q].h=h;			//对象的尺寸
}
//**********************************************************************
//  TransparentBlt2 (......)透明显示
//  根据关键色，将hdc1中的图形在hdc0中
//  自动生成掩模，并生成透明图形。
//	注:TransparentBlt(......)是一个WIN API函数，功能和这里的相同。
//	在WIN2000和以后的系统上可用。在WIN98中有严重的资源泄漏，根本不能用。
//  使用TransparentBlt(......)前，需引用:
//  #include <wingdi.h>
//  #pragma comment (lib,"msimg32.lib")
//**********************************************************************
void game::TransparentBlt2(HDC hdc0,			//目标DC
				int nX0,int nY0,int nW0,int nH0,//目标左坐标,目标宽高宽
				HDC hdc1,						//源DC
				int nX1,int nY1,int nW1,int nH1,//源起点坐标,源宽高宽
				UINT Tcol)						//透明色,COLORREF类型
					 
{	if(sys>1)//是win98以上的系统，直接调API函数TransparentBlt()
	{TransparentBlt(hdc0,nX0,nY0,nW0,nH0,hdc1,nX1,nY1,nW1,nH1,Tcol);
	 return;
	}
	HBITMAP hBMP   =CreateCompatibleBitmap(hdc0,nW0, nH0);	//创建位图内存
	HBITMAP mBMP   =CreateBitmap(nW0,nH0,1,1,NULL);			//创建单色掩码位图
	HDC		hDC    =CreateCompatibleDC(hdc0);				//创建设备句柄
	HDC		mDC    =CreateCompatibleDC(hdc0);				//创建设备句柄
	HBITMAP oldBMP =(HBITMAP)SelectObject(hDC, hBMP);
	HBITMAP oldmBMP=(HBITMAP)SelectObject(mDC, mBMP);
	// 将源DC中的位图拷贝到临时DC中
	if (nW0==nW1&&nH0==nH1)
		BitBlt(hDC,0,0,nW0,nH0,hdc1,nX1,nY1,SRCCOPY);
	else
		StretchBlt(hDC,0,0,nW0,nH0,hdc1,nX1,nY1,nW1,nH1,SRCCOPY);
	SetBkColor(hDC, Tcol);// 设置透明色
	BitBlt(mDC,0,0,nW0,nH0,hDC,0,0,SRCCOPY);//生成透明区域为白色,其它区域为黑色的掩码位图

	SetBkColor(hDC, RGB(0,0,0));			//生成透明区域为黑色,其它区域保持不变的位图
	SetTextColor(hDC, RGB(255,255,255));	//白色
	BitBlt(hDC,0,0,nW0,nH0,mDC,0,0,SRCAND);
	SetBkColor(hdc0,RGB(255,255,255));		//透明部分保持屏幕不变,其它部分变成黑色
	SetTextColor(hdc0,RGB(0,0,0));			//黑色

	BitBlt(hdc0,nX0,nY0,nW0,nH0,mDC,0,0,SRCAND);  //"与"运算,在hdc0生成掩模
	BitBlt(hdc0,nX0,nY0,nW0,nH0,hDC,0,0,SRCPAINT);//"或"运算,生成最终透明效果	
	SelectObject(hDC,oldBMP);
	SelectObject(mDC,oldmBMP);
	DeleteDC(hDC);
	DeleteDC(mDC);
	DeleteObject(hBMP);
	DeleteObject(mBMP);
}
//**************************************************
//  setman(int q) 设置活动对象初值
//  由给定的对象、方位、动作计算出图形的位置和数量。
//**************************************************
void game::setman(int q)//设置活动对象初值
{	int a=400;
	if(man[q].lb==0)//人
	{man[q].m0=man[q].js*a+zjdz[man[q].zs].qi
			  +man[q].fw*zjdz[man[q].zs].bc;//位置初值
	 man[q].m1=zjdz[man[q].zs].bc+man[q].m0;//位置终值
	 man[q].p=man[q].m0;					//数量计数
	}
	if(man[q].lb==1)//兽
	{man[q].m0=man[q].js*a+zjdw[man[q].zs].qi
			  +man[q].fw*zjdw[man[q].zs].bc;//位置初值
	 man[q].m1=zjdw[man[q].zs].bc+man[q].m0;//位置终值
	 man[q].p=man[q].m0;					//数量计数
	}
	man[q].zd=0;
}
//**************************************************
//  manmove(int i)	活动对象的移动
//  由当前、目标位置的差，计算当前位置向不同方位的改变。
//**************************************************
void game::manmove(int i)//活动对象的移动
{	if(man[i].lb==2)	return;		//是静物返回

	if(find_p==1&&man[i].pk<1)  return;//无搜索路径返回,没加寻路时不要这句。

	int stx,sty,qx,qy;
	switch(man[i].zs) 
		{case 2: {stx=9;sty=6;break;}//跑步长
	     case 1: {stx=4;sty=2;break;}//走步长
		 default:{stx=2;sty=1;break;}
		}
	qx=man[i].x0-man[i].xix;		//x当前、目标位置差
	qy=man[i].y0-man[i].xiy;		//y当前、目标位置差
	if (qx==0&&qy==0) 
	{if(find_p==1)	find_a(i);		//没加寻路时不要这句。
	 return ;		//到达返回
	}
	int qxa=abs(qx);				//x位置差绝对值
	int qya=abs(qy);				//y位置差绝对值
	if(qxa<stx)  stx=qxa;			//位置差不足步长，步长为差
	if(qya<sty)  sty=qya;			//
	if(qx!=0) man[i].xix+=qxa/qx*stx;//当前位置加步长
	if(qy!=0) man[i].xiy+=qya/qy*sty;//[qya/qy]单位绝对值
}
//**************************************************
//  bianfw(int q)//方位转换
//  由当前、目标位置的差，计算活动图形的方向取向。
//**************************************************
void game::bianfw(int q)//方位转换
{	int qx=man[q].x0-man[q].xix;		//x当前，目标位置差
	int qy=man[q].y0-man[q].xiy;		//y当前，目标位置差

	if(qx==0&&qy==0) 
		{if(man[q].zd==0) man[q].zs=0;	//为0,动作为站,方位保留
		 goto aa;
		}	
	if(man[q].zd==0)					//没打
	{int a=rand()%2+1;					//随机产生走、跑
	 if(man[q].lb==0) man[q].zs=1;		//是人设为走
	 if(man[q].lb==1) man[q].zs=dw[man[q].js][a];//是兽
	}
	if(qx<0&&qy>0)		{man[q].fw=1;goto aa;}//取西南向
	if(qx<0&&qy<0)		{man[q].fw=3;goto aa;}//取西北向
	if(qx>0&&qy<0)		{man[q].fw=5;goto aa;}//取东北向
	if(qx>0&&qy>0)		{man[q].fw=7;goto aa;}//取东南向
	if      (qy>0)		{man[q].fw=0;goto aa;}//取南向
	if(qx<0)			{man[q].fw=2;goto aa;}//取西向
	if      (qy<0)		{man[q].fw=4;goto aa;}//取北向
	if(qx>0)			{man[q].fw=6;goto aa;}//取东向
aa:	setman(q);								  //设置活动对象初值
	if(man[q].zs==0) 
		man[q].p=man[q].p+rand()%3;			  //避免动作一致
}
//**************************************************
//	loadmap(CString name)//对象初始化
//	调入编制好的对象场景(.dat)
//	场景文件(.dat)的格式：
//	第1行，为背景图形
//	第2行，对象数,后面一行是一个对象。
//	序号,类别,角色,静物图形号,x,y位置6个数据	
//**************************************************
void game::loadmap(CString name)//调地图
{ FILE *f;
  SetCurrentDirectory(appdir);	 //置当前目录
  f=fopen(name,"r");
  if(f==NULL) 
	{AfxMessageBox(name+"没有地图文件!!!");
     return;
	}
  fscanf(f,"%s\n",mapbak);		  //地图块名
  fscanf(f,"%d\n",&rs);			  //对象数
  if(rs>SU_LIANG)				  //对象数大于设定值返回
		{fclose(f);
		 SetCurrentDirectory(appdir);//置当前目录
		 return;
		}		  
  int i;
  for (i=0;i<rs;i++)
	{fscanf(f,"%d,",&man[i].jisu);//序号
	 fscanf(f,"%d,",&man[i].lb);  //类别:  [0人1兽2景]
	 fscanf(f,"%d,",&man[i].js);  //角色:人[0男1女]
								  //角色:兽[0豹1狼2鹿3马4雀5羊6猪]
	 fscanf(f,"%d,",&man[i].p);	  //静物图形号
	 fscanf(f,"%d,",&man[i].xix); //当前位置x
	 fscanf(f,"%d,",&man[i].xiy); //当前位置y
	 man[i].x0=man[i].xix;		  //目标位置x
	 man[i].y0=man[i].xiy;		  //目标位置y
	 man[i].fw=1;				  //方位:  [0南1西南2西3西北4北5东北6东7东南]
	 man[i].zs=0;				  //动作:人[0站1走2刺3劈4倒]
								  //动作:兽[0站1走2跑3斗4倒5尸]
	 man[i].pk =-1;				  //路径长
	 man[i].fid=-1;				  //路径计数
	 man[i].zd=0;
	 if(man[i].lb!=2) 
		 setman(man[i].jisu);	  //设置活动对象初值
	 getobjwh(i);				  //取对象的尺寸
	}
  fclose(f);
  SetCurrentDirectory(appdir);	 //置当前目录
}
//**************************************************
//  getpic(CString cc,int p) 调图片到相关位图
//  由p得到将调的图形文件名。
//  在指定目录中调入图形到相关位图bit
//**************************************************
BOOL game::getpic(CString cc,int p)//调图片到相关位图[3章]
{	char name[256];
	if(stmp==NULL)		//没有压缩资源
		{SetCurrentDirectory(appdir);			 //置当前目录
//调cc指定的图形
		 sprintf(name,"%s%s/c%05d.bmp",dir,cc,p);//生成将调的图形文件名
		 if(!loadbmp(name)) return FALSE;		 //调BMP图片
		 SelectObject(MemDC,bitmap);
//调cc指定的图形的偏移值。
		 sprintf(name,"%s%s/c%05d.txt",dir,cc,p);
		 FILE *f;
		 f=fopen(name,"r");
		 if(f!=NULL)
			{if(cc=="人") fscanf(f,"%d,%d",&rbufx[p],&rbufy[p]);//人的偏移量
			 if(cc=="兽") fscanf(f,"%d,%d",&sbufx[p],&sbufy[p]);//兽的偏移量
			 fclose(f);
			}
		 return TRUE;
		}
	else 
	{if(getpic0(cc,p)) return TRUE;//调压缩图片。
	 else return FALSE;
	}
}
//**************************************************
//  loadbmp(CString cc)//调BMP图片
//  调cc指定的图形;取得的图形在设备相关位图bit中
//  图形的宽、高存于全局变量w,h中
//**************************************************
BOOL game::loadbmp(CString cc)//调BMP图片[2章]
{	DeleteObject(bitmap);				//删除上次的位图内存。
	bitmap=(HBITMAP)LoadImage			//调入cc指定的图形
				(AfxGetInstanceHandle(),//
				 cc,IMAGE_BITMAP,		//文件名,位图方式				 			
				 0,0,					//图形宽,高
				 LR_LOADFROMFILE|LR_CREATEDIBSECTION//方式
				);
	if(bitmap==NULL) return FALSE;		//调图失败
	DIBSECTION ds;						//
	BITMAPINFOHEADER &bm = ds.dsBmih;	//
	GetObject(bitmap,sizeof(ds),&ds);	//取位图的信息->bminfo
	w = bm.biWidth;						//得到位图宽度值 
	h = bm.biHeight;					//得到位图高度值
	return TRUE;
}
/////////////////////////////////////////////////////////////////
void game::find_a(int i)//没加寻路时不要。
{//加入自动搜索后，应执行的代码
	if(man[i].fid<man[i].pk)	//从搜索的路径中取目标点
			{man[i].x0=man[i].ph[man[i].fid].x*GX+man[i].w/2;
			 man[i].y0=man[i].ph[man[i].fid].y*GY+man[i].h/2;
			 man[i].fid++;
			 if(man[i].x0<GX) man[i].x0=GX;
			 if(man[i].y0<GX) man[i].y0=GY;
			 bianfw(i);				//方位转换
			}
	else						//搜索路径取完
			{man[i].x0=man[i].fx;
			 man[i].y0=man[i].fy;
			}
}
//**************************************************
//  setobj(int q) 对象显示
//	调入由man[q].lb指出的，不同的man[q].p图片，和偏移值。
//  将对象q在各自的当前位置x,y上以透明方式TransparentBlt2显示。
//	之后进行移动或方位转换的功能。
//  为防止闪烁，所有对象先显示在暂存区BkDC1，一屏完成后再翻转到主屏上。
//**************************************************
void game::setobj(int q)//对象显示
{	CString cc;
	int x=man[q].xix-scrx-man[q].w/2;		//x当前位置
	int y=man[q].xiy-scry-man[q].h;			//y当前位置
	if(inscreer(q))//在显示区？
	{if(man[q].lb==0) {cc="人";}
	 if(man[q].lb==1) {cc="兽";}
	 if(man[q].lb==2) {cc="景";}
	 if(getpic(cc,man[q].p)==FALSE) return;
	 if(man[q].lb!=2)//调角色的偏移位置
     {int x0=0,y0=0;
	  if(man[q].lb==0) {x0=rbufx[man[q].p];y0=rbufy[man[q].p];}
	  if(man[q].lb==1) {x0=sbufx[man[q].p];y0=sbufy[man[q].p];}
	  if(man[q].fw>4) x0=w-x0;//是东北、东、东南方位
	  x=man[q].xix-scrx-x0;
	  y=man[q].xiy-scry-y0;
	 }
	 TransparentBlt2(BkDC1,x,y,w,h,MemDC,0,0,w,h,RGB(255,255,255));//透明显示
	 mans++;
	}
///////////////////////////////////////////////////////////////////////
	if(man[q].lb==2) return;
	else	manmove(q);				  //活动对象的移动
	man[q].p++;						  //下一动作
	if(man[q].p>=man[q].m1)	{bianfw(q);}//本动作完成,进行方位转换
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
	CString cc;
	int x=man[q].xix-scrx-man[q].w/2;		//x当前位置
	int y=man[q].xiy-scry-man[q].h;			//y当前位置
	if(inscreer(q))//在显示区？
	{if(man[q].lb==0) {cc="人";}
	 if(man[q].lb==1) {cc="兽";}
	 if(man[q].lb==2) {cc="景";}
	 if(getpic(cc,man[q].p)==FALSE) return;

	 if(man[q].lb!=2)						//调角色的偏移位置
     {int x0=0,y0=0;
	  if(man[q].lb==0) {x0=rbufx[man[q].p];y0=rbufy[man[q].p];}
	  if(man[q].lb==1) {x0=sbufx[man[q].p];y0=sbufy[man[q].p];}
	  if(man[q].fw>4) x0=w-x0;//是东北、东、东南方位
	  x=man[q].xix-scrx-x0;
	  y=man[q].xiy-scry-y0;
	 }
///////////////////////////////////////////////////////////////////////////////
	 if(a==0)
		{TransparentBlt2(BkDC1,x,y,w,h,MemDC,0,0,w,h,RGB(255,255,255));//透明显示
		 return;
		}
	 else	Alpha(x,y);
///////////////////////////////////////////////////////////////////////////////
	 mans++;
	}
///////////////////////////////////////////////////////////////////////
	if(man[q].lb==2) return;
	else	manmove(q);				  //活动对象的移动
	man[q].p++;						  //下一动作
	if(man[q].p>=man[q].m1)	{bianfw(q);}//本动作完成,进行方位转换
}
void game::Alpha(int x,int y)//
{	BitBlt(BK,0,0,w,h,BkDC1,x,y,SRCCOPY);
	TransparentBlt2(BkDC1,x,y,w,h,MemDC,0,0,w,h,RGB(255,255,255));//透明显示
	AlphaBlend(BkDC1,x,y,w,h,BK,0,0,w,h,rBlend);//半透明处理
}
//****************************************************************
//  BOOL getpic0(CString cc,int p) 调压缩图片
//  在cc指定的压缩库中取第p个图形和图形的尺寸w、h，取得的图形在MemDC中。
//****************************************************************
BOOL game::getpic0(CString cc,int p)//调压缩图片
{	int len;
	if(p<0) return FALSE;
	BYTE *tmp;
	if(cc=="人")
	{if(p>RBUF-1) return FALSE;
	 len=rbufadd[p+1]-rbufadd[p];	//取数据块长度
	 tmp=(BYTE *)new BYTE[len];
	 Memcpy0(tmp,rtmp+rbufadd[p],len);
	}
	if(cc=="兽")
	{if(p>SBUF-1) return FALSE;
	 len=sbufadd[p+1]-sbufadd[p];	//取数据块长度
	 tmp=(BYTE *)new BYTE[len];
	 Memcpy0(tmp,stmp+sbufadd[p],len);
	}
	if(cc=="景")
	{if(p>JBUF-6) return FALSE;
	 len=jbufadd[p+1]-jbufadd[p];	//取数据块长度
	 tmp=(BYTE *)new BYTE[len];
	 Memcpy0(tmp,jtmp+jbufadd[p],len);
	}
	LPBITMAPINFOHEADER bm=(BITMAPINFOHEADER *)tmp;//图形数据转换
	bm->biSize = sizeof(BITMAPINFOHEADER);
	w=bm->biWidth;	//图形高
	h=bm->biHeight;	//图形宽
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