/*********************************
[学VC编游戏]
编著、程序设计：唐明理 2004.7
E-mail:  cqtml@163.com
**********************************/
#include "stdafx.h"
#include "game_寻路.h"
extern unsigned short dw[7][6];
extern unsigned short smz[2][7];
gamepro:: gamepro(){}	//构造函数
gamepro::~gamepro(){}	//析构函数
//**************************************************
//	lookit(int i)//角色碰撞
//	只判断人是否与动物相遇；若相遇，动物停下来。
//	由位置差使双方面对面（位置调整），开始打斗（动作变换）。
//  播放打斗的WAV声音。
//**************************************************
void gamepro::lookit(int i)//角色碰撞
{	if(man[i].lb>=2) return;
	if(man[i].smz<1) return;		//兽生命值完
	{for(int q=0;q<rs;q++)
		{if(q==i) continue;				//是自己
		 if(man[q].lb==2) continue;		//是景
		 if(man[q].lb==0&&man[q].zs>3) return;//人已倒
		 int x=man[i].xix-man[q].xix;	//取q,i对象的位置差
		 int y=man[i].xiy-man[q].xiy;	//
		 if(abs(x)<man[q].w*4/3 && abs(y)<man[q].h*4/3)//相遇
			{int x0=man[q].xix-scrx-man[q].w/2;	//q对象当前位置x
			 int y0=man[q].xiy-scry-man[q].h/2;	//q对象当前位置y
			 if(man[i].lb==0&&man[q].lb==3)		//人见物
			 {if(man[q].p==0) man[i].smz=200;//生命
			  if(man[q].p==1) mansmz[1]=mansmz[1]+10;//经验
			  if(man[q].p==2) mansmz[2]=mansmz[2]+10;//金钱1
			  if(man[q].p==3) mansmz[2]=mansmz[2]+20;//金钱2
			  if(man[q].p==4) mansmz[2]=mansmz[2]+50;//金钱5
			  if(man[q].p==5) mansmz[3]=mansmz[3]+smz[0][man[q].js];//食物
			  Delete(q);return;			//删除物品
			  
			 }
			 if(man[q].lb>=1) continue;//是兽看见人
			 if(man[i].lb!=man[q].lb) //不同类
				{ man[i].x0=man[i].fx=man[i].xix;//
				  man[i].y0=man[i].fy=man[i].xiy;//
				  man[i].fid=man[i].pk;//兽停下来
				  //双方面对面
				  if(x==0&&y<0) {man[i].fw=0;man[q].fw=4;}//北
				  if(x>0&&y< 0) {man[i].fw=1;man[q].fw=5;}//东北
				  if(x>0&&y==0) {man[i].fw=2;man[q].fw=6;}//东
				  if(x>0&&y> 0) {man[i].fw=3;man[q].fw=7;}//东南
				  if(x==0&&y>0) {man[i].fw=4;man[q].fw=0;}//南
				  if(x<0&&y> 0) {man[i].fw=5;man[q].fw=1;}//西南
				  if(x<0&&y==0) {man[i].fw=6;man[q].fw=2;}//西
				  if(x<0&&y< 0) {man[i].fw=7;man[q].fw=3;}//西北
				  man[i].zs=dw[man[i].js][3];man[i].zd=1; //开打	
				  man[q].zs=3;				 man[q].zd=1; //开打
				  
				  //生命值
				  if(man[q].p==man[q].m1-8) 
				  {man[q].smz=man[q].smz-smz[1][man[i].js];	//兽对人攻击力
				   if(man[q].smz<0) man[q].smz=0;			//生命值校正
				   man[i].smz=man[i].smz-mansmz[1];			//人对兽攻击力
				   if(man[i].smz<0) man[i].smz=0;  			//生命值校正
				   da=da+smz[1][man[i].js];					//长经验值计数
				   if(da>50) {mansmz[1]=mansmz[1]+1;da=0;}	//长经验值
				  }
				  //================================================================
				  if(inscreer(i))				//在显示区？
				  {if(man[i].p==man[i].m1-8) sndPlaySound("砍1.wav",SND_ASYNC);//声音
				   if(man[q].p==man[q].m1-2) sndPlaySound("羊.wav",SND_ASYNC);//声音
				  }
				  break;
				 }
			}
		}
	}
}
//**************************************************
// randxy()//随机产生兽的移动目标
//	
//**************************************************
void gamepro::randxy()//随机产生兽的移动目标
{ for(int q=0;q<rs;q++)
	 {if(fidf==TRUE)	return;		//搜索路径正忙
	  if(rand()%20>0)	continue;	//20次跳过19次，不要移动太频繁。
	  if(man[q].lb!=1||man[q].fid<man[q].pk)//不是兽或正在移动
						continue;	//跳过

	  if(man[q].zd==1)  continue;	//正在打,跳过
	  int x=man[q].x0+WIDTH/2-rand()%WIDTH;	 //随机产生兽的x位移
	  int y=man[q].y0+HEIGHT/2-rand()%HEIGHT;//随机产生兽的y位移
	  //边界检测
	  if(x<GX) x=GX;
	  if(y<GY) y=GY;
	  if(x>WIDTH *SCRP0-GX) x=WIDTH *SCRP0-GX;
	  if(y>HEIGHT*SCRP0-GY) y=HEIGHT*SCRP0-GY;
	  if(FindPath(q,x,y)<0) continue;//A*算法寻路,搜索路径在man[i].ph中
	  man[q].p=man[q].m1-1;	//中止当前动作
	 }
}
//**************************************************
//  int FindPath(int i,int x,int y) A*算法寻路
//	A、由(x,y)目标点先滤出无效点。
//	B、设置起点、目标点调A*算法寻路
//	C、将寻得路径装入对象的路径中
//	D、取寻得路径的第一个点，作为对象移动的目标。
//	返回寻路时间
//**************************************************
int gamepro::FindPath(int i,int x,int y)//A*算法寻路
{	if(find_p==0) return 0;
	if(fidf==TRUE) return -4;//搜索路径正忙
//	A、由(x,y)目标点先滤出无效点。
	if(x<=0||y<=0) return -3;//无路
	int x0=x/GX,y0=y/GY;
	if(m_fid.map[x0][y0]=='1') 
		{fidf=FALSE;return -1;}	//目标点是障碍点
	if(x0==man[i].xix/GX&&y0==man[i].xiy/GY) 
		{fidf=FALSE;return -2;}	//目标点是起始点
	if(x0<1||y0<1) 
		{fidf=FALSE;return -10;}//左上边界
	if((x0+1)>=WIDTH*SCRP0/GX||(y0+1)>=HEIGHT*SCRP0/GY) 
		{fidf=FALSE;return -20;}//右下边界
//	B、设置起点、目标点调A*算法寻路
	fidf=TRUE;//置搜索路径正忙
	int tim=timeGetTime();		//进入时间
	m_fid.end_y  =man[i].xix/GX;//目标点
	m_fid.end_x  =man[i].xiy/GY;//
	m_fid.start_y=x0;			//起始点
	m_fid.start_x=y0;
	if(m_fid.findpath()==-1)	//A*算法寻路,
		{fidf=FALSE;
		 return-1;				//无路返回-1
		}
	man[i].pk=zlpath();			//重组路径
	if(man[i].pk<0) 
		{fidf=FALSE;return -3;}	//无路返回
	if(man[i].pk>250) {man[i].pk=0;fidf=FALSE;return -5;}
//	C、将寻得路径装入对象的路径中
	for(int j=0;j<man[i].pk;j++) 
		man[i].ph[j]=pathn[j];//路径保存到对应的对象(i)
	man[i].fx=x;man[i].fy=y;	//保留目标点
//	D、取寻得路径的第一个点，作为对象移动的目标。
	man[i].fid=1;				//取路径计数
	if(man[i].pk>1)				//取路径初值
	{man[i].x0=man[i].ph[man[i].fid].x*GX+man[i].w/2;
	 man[i].y0=man[i].ph[man[i].fid].y*GY+man[i].h/2;
	 man[i].fid++;
	}
	fidf=FALSE;//取消搜索路径正忙
	return timeGetTime()-tim;	//返回寻路时间
}
//**************************************************
//int zlpath() 重组路径,合并有效点，使行走平滑。
//**************************************************
int gamepro::zlpath()//重组路径
{	int k=1;
	int yy0;
	int xx=m_fid.path[0]/m_fid.map_w;
	int yy=m_fid.path[0]%m_fid.map_w;
	pathn[0].x=xx;pathn[0].y=yy;
	for(int j=1;m_fid.path[j]>0;j++)
	{xx= m_fid.path[j]/m_fid.map_w;
	 yy= m_fid.path[j]%m_fid.map_w;
	 yy0=m_fid.path[j+1]%m_fid.map_w;
	 pathn[k].x=xx;pathn[k].y=yy;
	 if(yy!=yy0)  k++;
	 if(k>500) return -1;
	}
	int p=1;
	for(j=1;j<k;j++)
	{pathn[p].x=pathn[j].x;pathn[p].y=pathn[j].y;
	 if(pathn[j].x!=pathn[j+1].x)  p++;
	}
	return p;
}
//*********************************************
//	loadza(CString name)//调入障碍表
//	调入障碍表(.map)，障碍表的格式：
//	第1行，障碍表的行列值，以后1 行就是障碍表1行的数据。
//*********************************************
void gamepro::loadza(CString name)//调入障碍表
{//	B、调入障碍表(.map)
  char cc[256];
  FILE *f;
  int i,j;
  strcpy(cc,name);cc[lstrlen(name)-3]=0;//变换文件名
  strcat(cc,"map");
  f=fopen(cc,"r");
  if(f==NULL) goto aa;			  //如果没有障碍文件
  fscanf(f,"%d,%d\n",&w,&h);
  SCRP0=w/16;					  //换成地图倍数
  m_fid.map_w=WIDTH*SCRP0/GX;
  m_fid.map_h=HEIGHT*SCRP0/GY;
  if(w>WIDTH*SCRP/GX||h>HEIGHT*SCRP/GY)	
	{SetCurrentDirectory(appdir);//置当前目录
	 return;
	}
  for(i=0;i<h;i++)
	  fgets(&m_fid.map[i][0],w+2,f);
  fclose(f);
aa:for(i=0;i<m_fid.map_w;i++)
		for(j=0;j<m_fid.map_h;j++)
				if(m_fid.map[i][j]!='1') m_fid.map[i][j]='0';
  find_p=1;		//无搜索0有搜索1
  SetCurrentDirectory(appdir);//置当前目录
}
//**************************************************
// game::loaddata()//调压缩资源包
//	A、分别调入景j、兽s、人r的图形压缩包指针
//	   和位置偏移量(.dat)到相应数组
//		Xbufadd	,图形压缩包指针
//		Xsbufx	,x位置偏移量
//		Xsbufy	,y位置偏移量
//	B、分别调入物w、景j、兽s、人r的图形压缩包数据到
//		内存wfile、jtmp、stmp、rtmp中
//**************************************************
void gamepro::loaddata()//调压缩资源包
{//	A、......
	FILE *f;
	int len,i,j;
	CString cc;

	cc=dir+"物.dar";
    f=fopen(cc,"r");
    if(f==NULL) return;
	fscanf(f,"%d",&len);
	for(i=0;i<len;i++)
		fscanf(f,"%d,%d,%d",&wbufadd[i],&j,&j);//读图形的位置
	fclose(f);

	cc=dir+"景.dar";
    f=fopen(cc,"r");
    if(f==NULL) return;
	fscanf(f,"%d",&len);
	for(i=0;i<len;i++)
		fscanf(f,"%d,%d,%d",&jbufadd[i],&j,&j);//读图形的位置
	fclose(f);

	cc=dir+"兽.dar";
    f=fopen(cc,"r");
    if(f==NULL) return;
	fscanf(f,"%d",&len);
	for(i=0;i<len;i++)
		fscanf(f,"%d,%d,%d",&sbufadd[i],&sbufx[i],&sbufy[i]);//角色的偏移位置
	fclose(f);

	cc=dir+"人.dar";
    f=fopen(cc,"r");
    if(f==NULL) return;
	fscanf(f,"%d",&len);
	for(i=0;i<len;i++)
		fscanf(f,"%d,%d,%d",&rbufadd[i],&rbufx[i],&rbufy[i]);//角色的偏移位置
	fclose(f);
//	B、......
	cc=dir+"物.gam";
	if( !wfile.Open(cc, CFile::modeRead, NULL ) ) return;
	cc=dir+"兽.gam";
	if( !sfile.Open(cc, CFile::modeRead, NULL ) ) return;
	cc=dir+"人.gam";
	if( !rfile.Open(cc, CFile::modeRead, NULL ) ) return;
	cc=dir+"景.gam";
	if( !jfile.Open(cc, CFile::modeRead, NULL ) ) return;
	UINT len0=sfile.GetLength();
	stmp=(BYTE *)new BYTE[len0];//兽
	sfile.Read( stmp, len0);
	sfile.Close();
	len0=rfile.GetLength();
	rtmp=(BYTE *)new BYTE[len0];//人
	rfile.Read( rtmp, len0);
	rfile.Close();
	len0=jfile.GetLength();
	jtmp=(BYTE *)new BYTE[len0];//景
	jfile.Read( jtmp, len0);
	jfile.Close();

	len0=wfile.GetLength();
	wtmp=(BYTE *)new BYTE[len0];//景
	wfile.Read( wtmp, len0);
	wfile.Close();
}
//**************************************************
// int leftdown(HDC hdc,int x,int y)//按左键
//	这是由按鼠标左键调用的。
//	A、在显示区按键，给出主角的目标位置，调A*算法寻路
//	B、在小地图区按键，调定位地图。
//	若是寻路，返回寻路的时间。
//**************************************************
int gamepro::leftdown(HDC hdc,int x,int y)//按左键
{	int fidtim=0;
	if(find_p==0)			//无搜索0有搜索1
		{gamemap::leftdown(hdc,x,y);
		 return fidtim;
		}
	if(x>0&&x<WIDTH&&y>0&&y<HEIGHT&&edi==0)	//在显示区,非编辑态
	{int i=mann;							//只对主角取目标点
	 fidtim=FindPath(i,x-2+scrx,y-10+scry);//A*算法寻路,得寻路时间
	 man[i].p=man[i].m1-1;//中止当前动作
	}
	if(dingweimap(x,y)==TRUE)		//在小地图上点左键,调定位地图
					smlmap(hdc);	//显示小地图
	return fidtim;
}
