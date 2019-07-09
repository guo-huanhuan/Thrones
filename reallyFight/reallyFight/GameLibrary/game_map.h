#include "game.h"

class gamemap : public game	//继承game类
{public: gamemap();	//构造函数
 virtual~gamemap();	//析构函数
 public://公有,外部可调用

 HDC		SMAP;				//小地图设备场景
 HBITMAP	mapbit;				//小地图位图内存
 CPen		pen0,pen1;			//画笔句柄
 short int 	fls;				//小地图闪烁
 short int 	mann;				//主角下标
 short int 	mapt,mapb;			//小地图上下
 short int 	mapl,mapr;			//小地图左右
 short int 	mapw,maph;			//小地图高宽
 short int 	movemap;			//地图移动否？
 short int 	SCRP0;				//实际地图倍数
 void initmap();				//初始化地图参数
 void exitmap();				//退出
 BOOL dingweimap(int x,int y);	//定位地图 
 void getsmap();				//生成小地图
 void smlmap(HDC dc);			//显示小地图
 void movesmap(int x0,int y0);	//移动地图
 void mlmap();					//地图块移动拼接
 int  leftdown(HDC hdc,int x,int y);//按左键
 void setfind(CDC* dc,CPen *old);//有寻路时用，显示主角寻路的路径
 //编辑功能的变量
 short int edi;
};