/*********************************
[学VC编游戏]
编著、程序设计：唐明理 2004.7
E-mail:  cqtml@163.com
**********************************/
#include "stdafx.h"
#include "game_地图.h"
extern unsigned short dw[7][6];
gamemap:: gamemap(){}	//构造函数
gamemap::~gamemap()
{DeleteObject(pen1); //删除主角寻路画笔
}	//析构函数
//***********************************************
//	B、	设置小地图的位置、尺寸
//	C、	SMAP-装载小地图
//		定义4个画笔pen0、pen1；pen、penz编辑用
//	D、	设置几个初始量。
//***********************************************
void gamemap::initmap()//初始化地图参数
{	mapt=10,mapb=120;			//小地图上下
	maph=mapb-mapt;				//小地图高
	mapl=WIDTH+6;				//小地图左
	mapr=mapl+maph*WIDTH/HEIGHT;//小地图右边是按显示区比例取得
	mapw=mapr-mapl;				//小地图宽

	hScrDC=CreateDC("DISPLAY", NULL, NULL, NULL);	//创建屏幕设备句柄

	SMAP  =CreateCompatibleDC(hScrDC);				//创建小地图设备句柄
	mapbit=CreateCompatibleBitmap(hScrDC,mapw,maph);//创建小地图位图内存
	SelectObject(SMAP,mapbit);						//小地图位图内存与小地图设备句柄关联
	pen0.CreatePen(PS_SOLID,1,RGB(0x0,0xf0,0xf0));	//小地图中的方格画笔
	pen1.CreatePen(PS_SOLID,1,RGB(0x60,0x60,0x60));	//主角寻路画笔
	DeleteDC(hScrDC);								//删除屏幕设备句柄
	fls=0;			//闪烁标志
	movemap=0;		//地图移动否？
	init();
}
void gamemap::exitmap()//退出
{	DeleteDC(BK);
	DeleteObject(bi);
	DeleteObject(mapbit);//删除小地图位图内存
	DeleteDC(SMAP);		//删除小地图设备句柄
	DeleteObject(pen0); //删除小地图中的方格画笔
	exit();
}
//**************************************************
// mlmap()//地图块移动拼接
// 这里使用的是单地图无缝拼接移动算法。
//**************************************************
void gamemap::mlmap()//地图块移动拼接
{	if(	movemap==0)		//地图移动否？
		BitBlt(BkDC1,0,0,WIDTH,HEIGHT,BkDC0,0,0,SRCCOPY);
	else
	{int gx=scrx%WIDTH,gy=scry%HEIGHT;
	 BitBlt(BK,   0,0,        WIDTH-gx,HEIGHT,BkDC0,gx,0,SRCCOPY);//地图横向移动
	 BitBlt(BK,   WIDTH-gx,   0,gx,HEIGHT,    BkDC0,0,0, SRCCOPY);
	 BitBlt(BkDC1,0,0,        WIDTH,HEIGHT-gy,BK,0,gy,   SRCCOPY);//地图纵向移动
	 BitBlt(BkDC1,0,HEIGHT-gy,WIDTH,gy,       BK,0,0,    SRCCOPY);
	}
	sort();			 //按Y坐标排序,用于在显示时分出前后位置
	movemap=0;		//地图移动否？
}
//**************************************************
//	getsmap()//生成小地图
//	A、调地面块到BkDC0地图设备句柄
//	B、全地图缩成小地图到SMAP
//	C、全地图景物微缩到SMAP
//**************************************************
void gamemap::getsmap()//生成小地图
{//A、调地面块到BkDC0地图设备句柄
	char name[256];
	sprintf(name,"%s%s",dir,mapbak);
	loadbmp(name);
	SelectObject(BkDC0,bitmap);//
	DeleteObject(bitmap);			//删除上次的位图内存。
//B、全地图缩成小地图
	int i,j;
	COLORREF col=RGB(255,255,255);
	for(i=0;i<mapw;i=i+mapw/SCRP0)
		for(j=0;j<maph;j=j+maph/SCRP0)
			   TransparentBlt2
					(SMAP,i,j,mapw/SCRP0,maph/SCRP0,
					 BkDC0,0,0,WIDTH,HEIGHT,col);//透明显示
//C、全地图景物微缩
	int wi=WIDTH*SCRP0,he=HEIGHT*SCRP0;
	for(int q=0;q<rs;q++)
	  if(man[q].lb==2)					//是静物
		{if(getpic("景",man[q].p)==FALSE) continue;//读取位图文件cc
		 int x=(man[q].xix-w/4)*mapw;	//x当前位置
		 int y=(man[q].xiy-h)*maph;		//y当前位置
		 TransparentBlt2
			 (SMAP,x/wi,y/he,(w*mapw)/(wi*2/3),(h*maph)/(he*2/3),
			  MemDC,0,0,w,h,col);//透明显示
		}
//	OldMak=(HBITMAP)SelectObject(MemDC,bitya);//?????????????????
}
//**************************************************
//	movesmap(int x0,int y0)//移动地图
//	鼠标超过边界时，改变(scrx,scry)使主显屏产生相应的移动。
//	每个方向的移动都进行超界检测。
//**************************************************
void gamemap::movesmap(int x0,int y0)//移动地图
{	int a=3;
	if(edi==1) a=1;	//编辑时使算法简单。
	if(x0>SCRWI-10)	//鼠标超过右边界
		{scrx=scrx+GX/a;if(scrx>WIDTH*(SCRP0-1)) scrx=WIDTH*(SCRP0-1);}
	if(x0<10)		//鼠标超过左边界
		{scrx=scrx-GX/a;if(scrx<0) scrx=0;}
	if(y0>SCRHE-10)	//鼠标超过下边界
		{scry=scry+GY/a;if(scry>HEIGHT*(SCRP0-1)) scry=HEIGHT*(SCRP0-1);}
	if(y0<10)		//鼠标超过上边界
		{scry=scry-GY/a;if(scry<0) scry=0;}
	movemap=1;		//地图移动否？
}
//**************************************************
//	BOOL dingweimap(int x,int y)//定位地图
//	这是由按鼠标左键调用的。
//	根据按键位置，改变(scrx,scry)使主显屏快速移动
//**************************************************
BOOL gamemap::dingweimap(int x,int y)//定位地图
{	if(y>mapt&&y<mapb&&x>mapl&&x<mapr)//在小地图上按键
	{scrx=(x-mapl)*WIDTH *SCRP0/mapw-mapw*2;
	 scry=(y-mapt)*HEIGHT*SCRP0/maph-maph*2;
	 scrx=(scrx/GX)*GX;
	 scry=(scry/GY)*GY;
	 //进行边界检测。
	 if(scrx>WIDTH*(SCRP0-1)) scrx=WIDTH*(SCRP0-1);
	 if(scrx<0) scrx=0;
	 if(scry>HEIGHT*(SCRP0-1)) scry=HEIGHT*(SCRP0-1);
	 if(scry<0) scry=0;
	 return TRUE;
	}
	return FALSE;
}
//**************************************************
// smlmap(HDC hdc)//显示小地图
//	0、小地图刷新
//	A、在小地图上显示主屏框
//	B、显示主角在小地图的移动
//	C、在小地图上显示主角寻路的路径
//**************************************************
void gamemap::smlmap(HDC dc0)//显示小地图
{	if(rs<1||SCRP0<1) return;
	CDC* dc = CDC::FromHandle (dc0);
//0、小地图刷新
	BitBlt(dc0,mapl,mapt,mapw,maph,SMAP,0,0,SRCCOPY);//小地图刷新
//A、在小地图上显示主屏框
	CPen *old;
	old=dc->SelectObject(&pen0);//调白色画笔
	int mapw0=mapw/SCRP0,maph0=maph/SCRP0-1;

	int scrx0=mapl+(scrx*mapw)/(WIDTH*SCRP0);
	int scry0=mapt+(scry*maph)/(HEIGHT*SCRP0);
	//用线画方框
	dc->MoveTo(scrx0,scry0);		//左上点
	dc->LineTo(scrx0+mapw0,scry0);	//右上点
	dc->LineTo(scrx0+mapw0,scry0+maph0);//右下点
	dc->LineTo(scrx0,scry0+maph0);	//左下点
	dc->LineTo(scrx0,scry0);		//左上点
//B、显示对象在小地图的移动
	for(int q=0;q<rs;q++)
	{	COLORREF col=RGB(0x0,0x0,0x0);//

		scrx0=(man[q].xix*mapw)/(WIDTH*SCRP0)-1;
		scry0=(man[q].xiy*maph)/(HEIGHT*SCRP0)-2;
		if(scrx0<1||scry0<1) continue;
		if(man[q].jisu==0)
		 {mann=q;		//取动态的主角下标
		  if(fls==0){fls=1;col=RGB(0xf0,0xf0,0xf0);}//白闪烁	
		  else		{fls=0;col=RGB(0xf0,0x0,0x0);}  //红
		  dc->SetPixel(mapl+scrx0+1,mapt+scry0,  col);
		  dc->SetPixel(mapl+scrx0+1,mapt+scry0+1,col);
		 }
		if(man[q].lb==2) continue;
		dc->SetPixel(mapl+scrx0,mapt+scry0,  col);
		dc->SetPixel(mapl+scrx0,mapt+scry0+1,col);

	}
//C、在小地图上显示主角寻路的路径
	setfind(dc,old);				//有寻路时用，显示主角寻路的路径

	dc->SelectObject(old);
	CDC::DeleteTempMap( );
}
//**************************************************
// int leftdown(HDC hdc,int x,int y)//按左键
//	这是由按鼠标左键调用的。
//	A、在显示区按键，给出主角的目标位置，调A*算法寻路
//	B、在小地图区按键，调定位地图。
//	若是寻路，返回寻路的时间。
//**************************************************
int gamemap::leftdown(HDC hdc,int x,int y)//按左键
{	int fidtim=0;
	if(x>0&&x<WIDTH&&y>0&&y<HEIGHT&&edi==0)	//在显示区,非编辑态
	{int i=mann;					//只对主角取目标点
	 man[i].x0=x-2+scrx;
	 man[i].y0=y-10+scry;
	 man[i].p=man[i].m1-1;			//中止当前动作
	}
	if(dingweimap(x,y)==TRUE)		//在小地图上点左键,调定位地图
					smlmap(hdc);	//显示小地图
	return fidtim;
}
//////////////////////////////////////////////////////////////////////
void gamemap::setfind(CDC* dc,CPen *old)//有寻路时用，显示主角寻路的路径
{//C、在小地图上显示主角寻路的路径
	int i=mann;//取主角
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
	old=dc->SelectObject(&pen1);//调红色画笔
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