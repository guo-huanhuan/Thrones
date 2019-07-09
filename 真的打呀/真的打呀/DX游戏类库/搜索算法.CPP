#include "stdafx.h"
#include "搜索算法.h"
/////////////////////////////////////////////////////////////////////////////
findpt::findpt(){}	//构造函数
findpt::~findpt(){}	//析构函数
/////////////////////////////////////////////////////////////////////////////
// 初始化队列
void findpt::init_queue()
{	queue=(LINK)malloc(sizeof(*queue));
	queue->node=NULL;
	queue->f=-1;
	queue->next=(LINK)malloc(sizeof(*queue));
	queue->next->f=MAXINT;
	queue->next->node=NULL;
	queue->next->next=NULL;
}
// 待处理节点入队列, 依靠对目的地估价距离插入排序
void findpt::enter_queue(TREE node,int f)
{	LINK p=queue,father,q;
	while(f>p->f)
		{ father=p; p=p->next;}
	q=(LINK)malloc(sizeof(*q));
	q->f=f,q->node=node,q->next=p;
	father->next=q;
}
// 将离目的地估计最近的方案出队列
TREE findpt::get_from_queue()
{	TREE bestchoice=queue->next->node;
	LINK next=queue->next->next;
	free(queue->next);
	queue->next=next;
	stack[stacktop++]=bestchoice;
	return bestchoice;
}
// 释放申请过的所有节点
void findpt::freetree()
{	int i;
	LINK p;
	for (i=0;i<stacktop;i++) free(stack[i]);
	while (queue)
		{ p=queue;
		  free(p->node);
		  queue=queue->next;
		  free(p);
		}
	free(queue);
}
// 估价函数,估价 x,y 到目的地的距离,估计值必须保证比实际值小
int findpt::judge(int x,int y)
{	int distance;
	distance=abs(end_x-x)+abs(end_y-y);
	return distance;
}
// 尝试下一步移动到 x,y 可行否
int findpt::trytile(int x,int y,TREE father)
{	TREE p=father;
	int h;
	if (map[y][x]!='0') return 1; //如果(x,y)处是障碍,失败
	h=father->h+1;
	if (h>=dis_map[y][x]) return 1; // 如果曾经有更好的方案移动到 (x,y) 失败
	dis_map[y][x]=h; // 记录这次到 (x,y) 的距离为历史最佳距离
	// 将这步方案记入待处理队列
	p=(TREE)malloc(sizeof(*p));
	p->father=father;
	p->h=father->h+1;
	p->tile=tile_num(x,y);
	enter_queue(p,p->h+judge(x,y));
	return 0;
}

// 路径寻找主函数
int findpt::findpath()
{	TREE root;
	int i,j;
	stacktop=0;
	for (i=0;i<map_h;i++)
       for (j=0;j<map_w;j++)
         dis_map[i][j]=MAXINT;
	init_queue();
	root=(TREE)malloc(sizeof(*root));
	root->tile=tile_num(start_x,start_y);
	root->h=0;
	root->father=NULL;
	enter_queue(root,judge(start_x,start_y));
	for (;;)
		{ int x,y,child;
		  root=get_from_queue();
		  if (root==NULL)
			{*path=-1; 
			 free(root); freetree();//释放
		     return -1;
			}
		  x=tile_x(root->tile);
		  y=tile_y(root->tile);
		  if (x==end_x && y==end_y) break;//达到目的地成功返回
		  child =trytile(x,  y-1,root); //尝试向北  移动
		  child&=trytile(x+1,y-1,root); //尝试向东北移动
		  child&=trytile(x+1,y,  root); //尝试向东  移动
		  child&=trytile(x+1,y+1,root); //尝试向东南移动
		  child&=trytile(x,  y+1,root); //尝试向南  移动
		  child&=trytile(x-1,y+1,root); //尝试向西南移动
		  child&=trytile(x-1,y,  root); //尝试向西  移动
		  child&=trytile(x-1,y-1,root); //尝试向西北移动
		  if (child!=0)	free(stack[--stacktop]);
					    //如果8个方向均不能移动,释放这个死节点(释放栈顶节点)
		}
// 回溯树，将求出的最佳路径保存在 path[] 中
	for (i=0;root;i++)
		{ path[i]=root->tile;  root=root->father;}
	path[i]=-1;
	free(root);	freetree();//释放
	return 0;
}


