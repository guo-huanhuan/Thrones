#include "game_寻路.h"
class gmedit : public gamepro	//继承gamepro类 
{public: gmedit();	//构造函数
 virtual~gmedit();	//析构函数
 public://公有,外部可调用
 //变量定义
 short int 	gno;				//选中的对象序号
 short int 	tml;				//滚动条指针
 short int 	x1,y1;				//选中的对象的坐标
 CPen pen;						//编辑方格画笔
 CPen penz;						//编辑障碍画笔
 //函数定义
 void initedit();				//初始化
 void exitedit();				//返回
 void newmap ();				//新建地图
 void savemap(CString name);	//保存地图
 void Delete();					//删除
 void Insert(int no,int dorj);	//插入
 void getwp(HDC hdc,int dorj);	//显示选择对象
 void getno(int x,int y);		//选择对象
 void getobj(HDC hdc,int i);	//加入选择
 void showline();				//显示编辑方格
 void SaveBmp(CString fileName,LPBITMAPINFOHEADER bi1); 
};