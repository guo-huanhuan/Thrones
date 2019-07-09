/*********************************
[学VC编游戏]
编著、程序设计：唐明理 2004.7
E-mail:  cqtml@163.com
**********************************/
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")//时间函数库
#include <wingdi.h>
#pragma comment (lib,"msimg32.lib")//透明显示库
#include <vfw.h>
#pragma comment (lib,"vfw32.lib")
#include <ddraw.h>
#pragma comment (lib,"ddraw.lib")//DirectX库
//定义常数-------------------------------------------------
 #define SU_LIANG   450		//定义对象数
 #define TIMER		120		//主时钟周期
 #define WIDTH		640		//游戏显示区宽
 #define HEIGHT		480		//游戏显示区高
 #define SCRWI		800		//程序界面宽
 #define SCRHE		600		//程序界面高
 #define GX			40		//地图格宽
 #define GY			30		//地图格高
 #define SCRP		12		//地图最大为显示区的12倍
 #define SBUF		2801	//兽最大数
 #define RBUF		801		//人最大数
 #define JBUF		100		//景最大数
 #define WBUF		10		//物最大数
//-------------------------------------------------------
 #define SCRWI0		840		//
 #define SCRHE0		780		//
 #define SCRW		100
 #define SCRH		150