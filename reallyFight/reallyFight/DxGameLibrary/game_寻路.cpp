/*********************************
[ѧVC����Ϸ]
������������ƣ������� 2004.7
E-mail:  cqtml@163.com
**********************************/
#include "stdafx.h"
#include "game_Ѱ·.h"
extern unsigned short dw[7][6];
extern unsigned short smz[2][7];
gamepro:: gamepro(){}	//���캯��
gamepro::~gamepro(){}	//��������
//**************************************************
//	lookit(int i)//��ɫ��ײ
//	ֻ�ж����Ƿ��붯��������������������ͣ������
//	��λ�ò�ʹ˫������棨λ�õ���������ʼ�򶷣������任����
//  ���Ŵ򶷵�WAV������
//**************************************************
void gamepro::lookit(int i)//��ɫ��ײ
{	if(man[i].lb>=2) return;
	if(man[i].smz<1) return;		//������ֵ��
	{for(int q=0;q<rs;q++)
		{if(q==i) continue;				//���Լ�
		 if(man[q].lb==2) continue;		//�Ǿ�
		 if(man[q].lb==0&&man[q].zs>3) return;//���ѵ�
		 int x=man[i].xix-man[q].xix;	//ȡq,i�����λ�ò�
		 int y=man[i].xiy-man[q].xiy;	//
		 if(abs(x)<man[q].w*4/3 && abs(y)<man[q].h*4/3)//����
			{int x0=man[q].xix-scrx-man[q].w/2;	//q����ǰλ��x
			 int y0=man[q].xiy-scry-man[q].h/2;	//q����ǰλ��y
			 if(man[i].lb==0&&man[q].lb==3)		//�˼���
			 {if(man[q].p==0) man[i].smz=200;//����
			  if(man[q].p==1) mansmz[1]=mansmz[1]+10;//����
			  if(man[q].p==2) mansmz[2]=mansmz[2]+10;//��Ǯ1
			  if(man[q].p==3) mansmz[2]=mansmz[2]+20;//��Ǯ2
			  if(man[q].p==4) mansmz[2]=mansmz[2]+50;//��Ǯ5
			  if(man[q].p==5) mansmz[3]=mansmz[3]+smz[0][man[q].js];//ʳ��
			  Delete(q);return;			//ɾ����Ʒ
			  
			 }
			 if(man[q].lb>=1) continue;//���޿�����
			 if(man[i].lb!=man[q].lb) //��ͬ��
				{ man[i].x0=man[i].fx=man[i].xix;//
				  man[i].y0=man[i].fy=man[i].xiy;//
				  man[i].fid=man[i].pk;//��ͣ����
				  //˫�������
				  if(x==0&&y<0) {man[i].fw=0;man[q].fw=4;}//��
				  if(x>0&&y< 0) {man[i].fw=1;man[q].fw=5;}//����
				  if(x>0&&y==0) {man[i].fw=2;man[q].fw=6;}//��
				  if(x>0&&y> 0) {man[i].fw=3;man[q].fw=7;}//����
				  if(x==0&&y>0) {man[i].fw=4;man[q].fw=0;}//��
				  if(x<0&&y> 0) {man[i].fw=5;man[q].fw=1;}//����
				  if(x<0&&y==0) {man[i].fw=6;man[q].fw=2;}//��
				  if(x<0&&y< 0) {man[i].fw=7;man[q].fw=3;}//����
				  man[i].zs=dw[man[i].js][3];man[i].zd=1; //����	
				  man[q].zs=3;				 man[q].zd=1; //����
				  
				  //����ֵ
				  if(man[q].p==man[q].m1-8) 
				  {man[q].smz=man[q].smz-smz[1][man[i].js];	//�޶��˹�����
				   if(man[q].smz<0) man[q].smz=0;			//����ֵУ��
				   man[i].smz=man[i].smz-mansmz[1];			//�˶��޹�����
				   if(man[i].smz<0) man[i].smz=0;  			//����ֵУ��
				   da=da+smz[1][man[i].js];					//������ֵ����
				   if(da>50) {mansmz[1]=mansmz[1]+1;da=0;}	//������ֵ
				  }
				  //================================================================
				  if(inscreer(i))				//����ʾ����
				  {if(man[i].p==man[i].m1-8) sndPlaySound("��1.wav",SND_ASYNC);//����
				   if(man[q].p==man[q].m1-2) sndPlaySound("��.wav",SND_ASYNC);//����
				  }
				  break;
				 }
			}
		}
	}
}
//**************************************************
// randxy()//��������޵��ƶ�Ŀ��
//	
//**************************************************
void gamepro::randxy()//��������޵��ƶ�Ŀ��
{ for(int q=0;q<rs;q++)
	 {if(fidf==TRUE)	return;		//����·����æ
	  if(rand()%20>0)	continue;	//20������19�Σ���Ҫ�ƶ�̫Ƶ����
	  if(man[q].lb!=1||man[q].fid<man[q].pk)//�����޻������ƶ�
						continue;	//����

	  if(man[q].zd==1)  continue;	//���ڴ�,����
	  int x=man[q].x0+WIDTH/2-rand()%WIDTH;	 //��������޵�xλ��
	  int y=man[q].y0+HEIGHT/2-rand()%HEIGHT;//��������޵�yλ��
	  //�߽���
	  if(x<GX) x=GX;
	  if(y<GY) y=GY;
	  if(x>WIDTH *SCRP0-GX) x=WIDTH *SCRP0-GX;
	  if(y>HEIGHT*SCRP0-GY) y=HEIGHT*SCRP0-GY;
	  if(FindPath(q,x,y)<0) continue;//A*�㷨Ѱ·,����·����man[i].ph��
	  man[q].p=man[q].m1-1;	//��ֹ��ǰ����
	 }
}
//**************************************************
//  int FindPath(int i,int x,int y) A*�㷨Ѱ·
//	A����(x,y)Ŀ������˳���Ч�㡣
//	B��������㡢Ŀ����A*�㷨Ѱ·
//	C����Ѱ��·��װ������·����
//	D��ȡѰ��·���ĵ�һ���㣬��Ϊ�����ƶ���Ŀ�ꡣ
//	����Ѱ·ʱ��
//**************************************************
int gamepro::FindPath(int i,int x,int y)//A*�㷨Ѱ·
{	if(find_p==0) return 0;
	if(fidf==TRUE) return -4;//����·����æ
//	A����(x,y)Ŀ������˳���Ч�㡣
	if(x<=0||y<=0) return -3;//��·
	int x0=x/GX,y0=y/GY;
	if(m_fid.map[x0][y0]=='1') 
		{fidf=FALSE;return -1;}	//Ŀ������ϰ���
	if(x0==man[i].xix/GX&&y0==man[i].xiy/GY) 
		{fidf=FALSE;return -2;}	//Ŀ�������ʼ��
	if(x0<1||y0<1) 
		{fidf=FALSE;return -10;}//���ϱ߽�
	if((x0+1)>=WIDTH*SCRP0/GX||(y0+1)>=HEIGHT*SCRP0/GY) 
		{fidf=FALSE;return -20;}//���±߽�
//	B��������㡢Ŀ����A*�㷨Ѱ·
	fidf=TRUE;//������·����æ
	int tim=timeGetTime();		//����ʱ��
	m_fid.end_y  =man[i].xix/GX;//Ŀ���
	m_fid.end_x  =man[i].xiy/GY;//
	m_fid.start_y=x0;			//��ʼ��
	m_fid.start_x=y0;
	if(m_fid.findpath()==-1)	//A*�㷨Ѱ·,
		{fidf=FALSE;
		 return-1;				//��·����-1
		}
	man[i].pk=zlpath();			//����·��
	if(man[i].pk<0) 
		{fidf=FALSE;return -3;}	//��·����
	if(man[i].pk>250) {man[i].pk=0;fidf=FALSE;return -5;}
//	C����Ѱ��·��װ������·����
	for(int j=0;j<man[i].pk;j++) 
		man[i].ph[j]=pathn[j];//·�����浽��Ӧ�Ķ���(i)
	man[i].fx=x;man[i].fy=y;	//����Ŀ���
//	D��ȡѰ��·���ĵ�һ���㣬��Ϊ�����ƶ���Ŀ�ꡣ
	man[i].fid=1;				//ȡ·������
	if(man[i].pk>1)				//ȡ·����ֵ
	{man[i].x0=man[i].ph[man[i].fid].x*GX+man[i].w/2;
	 man[i].y0=man[i].ph[man[i].fid].y*GY+man[i].h/2;
	 man[i].fid++;
	}
	fidf=FALSE;//ȡ������·����æ
	return timeGetTime()-tim;	//����Ѱ·ʱ��
}
//**************************************************
//int zlpath() ����·��,�ϲ���Ч�㣬ʹ����ƽ����
//**************************************************
int gamepro::zlpath()//����·��
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
//	loadza(CString name)//�����ϰ���
//	�����ϰ���(.map)���ϰ���ĸ�ʽ��
//	��1�У��ϰ��������ֵ���Ժ�1 �о����ϰ���1�е����ݡ�
//*********************************************
void gamepro::loadza(CString name)//�����ϰ���
{//	B�������ϰ���(.map)
  char cc[256];
  FILE *f;
  int i,j;
  strcpy(cc,name);cc[lstrlen(name)-3]=0;//�任�ļ���
  strcat(cc,"map");
  f=fopen(cc,"r");
  if(f==NULL) goto aa;			  //���û���ϰ��ļ�
  fscanf(f,"%d,%d\n",&w,&h);
  SCRP0=w/16;					  //���ɵ�ͼ����
  m_fid.map_w=WIDTH*SCRP0/GX;
  m_fid.map_h=HEIGHT*SCRP0/GY;
  if(w>WIDTH*SCRP/GX||h>HEIGHT*SCRP/GY)	
	{SetCurrentDirectory(appdir);//�õ�ǰĿ¼
	 return;
	}
  for(i=0;i<h;i++)
	  fgets(&m_fid.map[i][0],w+2,f);
  fclose(f);
aa:for(i=0;i<m_fid.map_w;i++)
		for(j=0;j<m_fid.map_h;j++)
				if(m_fid.map[i][j]!='1') m_fid.map[i][j]='0';
  find_p=1;		//������0������1
  SetCurrentDirectory(appdir);//�õ�ǰĿ¼
}
//**************************************************
// game::loaddata()//��ѹ����Դ��
//	A���ֱ���뾰j����s����r��ͼ��ѹ����ָ��
//	   ��λ��ƫ����(.dat)����Ӧ����
//		Xbufadd	,ͼ��ѹ����ָ��
//		Xsbufx	,xλ��ƫ����
//		Xsbufy	,yλ��ƫ����
//	B���ֱ������w����j����s����r��ͼ��ѹ�������ݵ�
//		�ڴ�wfile��jtmp��stmp��rtmp��
//**************************************************
void gamepro::loaddata()//��ѹ����Դ��
{//	A��......
	FILE *f;
	int len,i,j;
	CString cc;

	cc=dir+"��.dar";
    f=fopen(cc,"r");
    if(f==NULL) return;
	fscanf(f,"%d",&len);
	for(i=0;i<len;i++)
		fscanf(f,"%d,%d,%d",&wbufadd[i],&j,&j);//��ͼ�ε�λ��
	fclose(f);

	cc=dir+"��.dar";
    f=fopen(cc,"r");
    if(f==NULL) return;
	fscanf(f,"%d",&len);
	for(i=0;i<len;i++)
		fscanf(f,"%d,%d,%d",&jbufadd[i],&j,&j);//��ͼ�ε�λ��
	fclose(f);

	cc=dir+"��.dar";
    f=fopen(cc,"r");
    if(f==NULL) return;
	fscanf(f,"%d",&len);
	for(i=0;i<len;i++)
		fscanf(f,"%d,%d,%d",&sbufadd[i],&sbufx[i],&sbufy[i]);//��ɫ��ƫ��λ��
	fclose(f);

	cc=dir+"��.dar";
    f=fopen(cc,"r");
    if(f==NULL) return;
	fscanf(f,"%d",&len);
	for(i=0;i<len;i++)
		fscanf(f,"%d,%d,%d",&rbufadd[i],&rbufx[i],&rbufy[i]);//��ɫ��ƫ��λ��
	fclose(f);
//	B��......
	cc=dir+"��.gam";
	if( !wfile.Open(cc, CFile::modeRead, NULL ) ) return;
	cc=dir+"��.gam";
	if( !sfile.Open(cc, CFile::modeRead, NULL ) ) return;
	cc=dir+"��.gam";
	if( !rfile.Open(cc, CFile::modeRead, NULL ) ) return;
	cc=dir+"��.gam";
	if( !jfile.Open(cc, CFile::modeRead, NULL ) ) return;
	UINT len0=sfile.GetLength();
	stmp=(BYTE *)new BYTE[len0];//��
	sfile.Read( stmp, len0);
	sfile.Close();
	len0=rfile.GetLength();
	rtmp=(BYTE *)new BYTE[len0];//��
	rfile.Read( rtmp, len0);
	rfile.Close();
	len0=jfile.GetLength();
	jtmp=(BYTE *)new BYTE[len0];//��
	jfile.Read( jtmp, len0);
	jfile.Close();

	len0=wfile.GetLength();
	wtmp=(BYTE *)new BYTE[len0];//��
	wfile.Read( wtmp, len0);
	wfile.Close();
}
//**************************************************
// int leftdown(HDC hdc,int x,int y)//�����
//	�����ɰ����������õġ�
//	A������ʾ���������������ǵ�Ŀ��λ�ã���A*�㷨Ѱ·
//	B����С��ͼ������������λ��ͼ��
//	����Ѱ·������Ѱ·��ʱ�䡣
//**************************************************
int gamepro::leftdown(HDC hdc,int x,int y)//�����
{	int fidtim=0;
	if(find_p==0)			//������0������1
		{gamemap::leftdown(hdc,x,y);
		 return fidtim;
		}
	if(x>0&&x<WIDTH&&y>0&&y<HEIGHT&&edi==0)	//����ʾ��,�Ǳ༭̬
	{int i=mann;							//ֻ������ȡĿ���
	 fidtim=FindPath(i,x-2+scrx,y-10+scry);//A*�㷨Ѱ·,��Ѱ·ʱ��
	 man[i].p=man[i].m1-1;//��ֹ��ǰ����
	}
	if(dingweimap(x,y)==TRUE)		//��С��ͼ�ϵ����,����λ��ͼ
					smlmap(hdc);	//��ʾС��ͼ
	return fidtim;
}
