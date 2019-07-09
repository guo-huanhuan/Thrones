#include "game_地图.h"
#include "搜索算法.h"
class gamepro : public gamemap	//继承gamemap类
{public: gamepro();	//构造函数
 virtual~gamepro();	//析构函数
 public://公有,外部可调用
 //变量定义
 findpt		m_fid;				//A*搜索类调用名------
 PATHN		pathn[500];			//重组路径
 BOOL		fidf;				//搜索忙闲标志

 //函数定义
 //BOOL pongcung(int i);			//与障碍碰撞检测(??)
 void loadza(CString name);			//调入障碍表
 void lookit(int i);				//角色碰撞
 void randxy();						//随机产生兽的移动目标
 void loaddata();					//调压缩资源包
 int  FindPath(int i,int x,int y);	//A*算法寻路
 int  leftdown(HDC hdc,int x,int y);//按左键
 int  zlpath();						//重组路径

};