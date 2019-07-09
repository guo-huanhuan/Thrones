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
	short int xix,xiy;	//当前位置
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
 HDC		hScrDC;			//屏幕设备场景
 HDC		BkDC0;			//地图设备场景
 HDC		BkDC1;			//暂存设备场景
 HDC		MemDC;			//对象设备场景
 HBITMAP	bitmap;			//地图位图内存
 HBITMAP	OldMak;

 CString	dir;			//数据路径
 short int 	rs;				//当前对象数
 short int 	scrx,scry;		//地图移动量
 CString	mapbak;			//地图块名
 int		w,h;			//对象图片宽、高
 char appdir[256];			//当前目录

 short int 	mans;				//显示区对象数
 short int	sbufx  [SBUF];		//兽的偏移量x
 short int	sbufy  [SBUF];		//兽的偏移量y
 short int	rbufx  [RBUF];		//人的偏移量x
 short int	rbufy  [RBUF];		//人的偏移量y

 short int	find_p;				//find_p搜索无0有1；没加寻路时不要。

 private://私有,类内部使用

 HBITMAP	bit0;			//暂存位图内存
 HBITMAP	bit1;			//暂存位图内存
 short int 	sys;			//当前运行系统
 //函数定义
 public://公有,外部可调用。----------------------------------------
 BOOL init();						//初始化
 void exit();						//退出
 void loadmap(CString name);		//对象初始化
 BOOL getpic(CString cc,int p);		//调图片到相关位图[3章]
 BOOL loadbmp(CString cc);			//调BMP图片[2章]
 void setobj (int q);				//对象显示
 void setman (int q);				//设置活动对象初值
 void getobjwh(int q);				//取对象的尺寸
 void sort();						//排序(冒泡法)
 void TransparentBlt2(HDC hdc0,		//目标DC
		int nX0,int nY0,int nW0,int nH0,//目标左坐标,目标宽高宽
		HDC hdc1,						//源DC
		int nX1,int nY1,int nW1,int nH1,//源起点坐标,源宽高宽
		UINT Tcol);						//透明色,COLORREF类型
 private://私有,类内部使用
 BOOL inscreer(int i);				//在显示区？
 int  getsys();						//识别系统
 void bianfw (int q);				//方位转换
 void manmove(int i);				//活动对象的移动

 //A、后继功能使用//////////////////////////////////////////////
 void find_a(int i);				//没加寻路时不要。
 public://公有,外部可调用。----------------------------------------
 HDC		BK;					//用于地图移动
 HBITMAP	bi;					//用于地图移动

 HBITMAP	bitya;
 BLENDFUNCTION rBlend;			//半透明
 CFile		sfile,rfile,jfile;	//压缩资源包的文件指针
 BYTE		*stmp,*rtmp,*jtmp;	//压缩的内存变量

 int		sbufadd[SBUF];		//兽的资源指针
 int		rbufadd[RBUF];		//人的资源指针
 int		jbufadd[JBUF];		//景的资源指针

 void Alphasetobj(int q,int a);	//半透明的对象显示
 void game::Alpha(int x,int y);//
 BOOL getpic0(CString cc,int p);//调压缩图片
 void Memcpy0(unsigned char *mu,unsigned char *yu,int z);
};