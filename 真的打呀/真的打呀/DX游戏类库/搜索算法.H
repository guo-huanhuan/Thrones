#include "常数定义.h"

#define MAXINT    8192  //定义一个最大整数, 地图上任意两点距离不会超过它8192 
#define STACKSIZE 40000 //保存搜索节点的堆栈大小65536
#define tile_num(x,y) ((y)*map_w+(x))  //将 x,y 坐标转换为地图上块的编号
#define tile_x(n) ((n)%map_w)          //由块编号得出 x,y 坐标
#define tile_y(n) ((n)/map_w)
//定义结构----------------------------------------------------------------------
typedef struct node *TREE;// 树结构
struct node
 {int h; int tile; TREE father;};
typedef struct node2 *LINK;// 树结构
struct node2
 { TREE node; int f; LINK next;};
//---------------------------------------------
class findpt
{public: findpt();	//构造函数
 virtual~findpt();	//析构函数
 public://公有,外部可调用
 int		path[MAXINT];
 char		map[WIDTH*SCRP/GX+2][HEIGHT*SCRP/GY+2];	//地图障碍格数据
 short int	dis_map[WIDTH*SCRP/GX+2][HEIGHT*SCRP/GY+2];//保存搜索路径时,中间目标地最优解
 int		map_w,map_h;							//地图障碍格宽和高
 int		start_x,start_y,end_x,end_y;			//起点坐标,终点坐标

 int		findpath();								//路径寻找主函数
 private://私有,类内部使用
 LINK queue;						//保存没有处理的行走方法的节点
 TREE stack[STACKSIZE];				//保存已经处理过的节点(搜索完后释放)
 int  stacktop;

 void init_queue();					// 初始化队列
 void enter_queue(TREE node,int f);	//待处理节点入队列,依靠对目的地估价距离插入排序
 TREE get_from_queue();				//将离目的地估计最近的方案出队列
 void freetree();					//释放申请过的所有节点
 int  judge(int x,int y);			//估价函数,估价x,y到目的地的距离,估计值必须保证比实际值小
 int  trytile(int x,int y,TREE father);//尝试下一步移动到x,y可行否
};