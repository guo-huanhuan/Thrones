#include "��������.h"

//����ṹ----------------------------------------------------------------------
typedef struct 
 {	short int x;
	short int y;
 } PATHN;//��������·��
typedef struct 
 {	short int qi;		//�������
	short int bc;		//��������
 } JCDZ;	//�˻��޵Ķ����ṹ
typedef struct
{	short int jisu;		//���
	short int xix,xiy;	//��ǰλ��
	short int x0,y0;	//Ŀ��λ��
	short int w,h;		//����ߴ�
	short int lb;		//���:  [0��1��2��]
	short int p;		//����
	//�����ˡ�����ʹ��
	short int m0,m1;	//λ�ó�ֵ����ֵ
	short int zs;		//����:��[0վ1��2��3��4��]
						//����:��[0վ1��2��3��4��5ʬ]
	short int js;		//��ɫ:��[0��1Ů]
						//��ɫ:��[0��1��2¹3��4ȸ5��6��]
	short int fw;		//��λ:	 [0��1����2��3����4��5����6��7����]
	short int zd;		//��ǰ״̬[0,1��]
	//��������ʹ��
	PATHN	  ph[250];	//������·��
	short int pk;		//·����
	short int fid;		//·������
	short int fx,fy;	//����Ŀ���
} MAN;		//����ṹ
//������-------------------------------------------------------------------------
class game 
{public: game();	//���캯��
 virtual~game();	//��������
 //A��������Ϸ����-------------------------------
 //��������
 public://����,�ⲿ�ɵ���
 MAN		man[SU_LIANG];	//����������,����ΪSU_LIANG
 HDC		hScrDC;			//��Ļ�豸����
 HDC		BkDC0;			//��ͼ�豸����
 HDC		BkDC1;			//�ݴ��豸����
 HDC		MemDC;			//�����豸����
 HBITMAP	bitmap;			//��ͼλͼ�ڴ�
 HBITMAP	OldMak;

 CString	dir;			//����·��
 short int 	rs;				//��ǰ������
 short int 	scrx,scry;		//��ͼ�ƶ���
 CString	mapbak;			//��ͼ����
 int		w,h;			//����ͼƬ����
 char appdir[256];			//��ǰĿ¼

 short int 	mans;				//��ʾ��������
 short int	sbufx  [SBUF];		//�޵�ƫ����x
 short int	sbufy  [SBUF];		//�޵�ƫ����y
 short int	rbufx  [RBUF];		//�˵�ƫ����x
 short int	rbufy  [RBUF];		//�˵�ƫ����y

 short int	find_p;				//find_p������0��1��û��Ѱ·ʱ��Ҫ��

 private://˽��,���ڲ�ʹ��

 HBITMAP	bit0;			//�ݴ�λͼ�ڴ�
 HBITMAP	bit1;			//�ݴ�λͼ�ڴ�
 short int 	sys;			//��ǰ����ϵͳ
 //��������
 public://����,�ⲿ�ɵ��á�----------------------------------------
 BOOL init();						//��ʼ��
 void exit();						//�˳�
 void loadmap(CString name);		//�����ʼ��
 BOOL getpic(CString cc,int p);		//��ͼƬ�����λͼ[3��]
 BOOL loadbmp(CString cc);			//��BMPͼƬ[2��]
 void setobj (int q);				//������ʾ
 void setman (int q);				//���û�����ֵ
 void getobjwh(int q);				//ȡ����ĳߴ�
 void sort();						//����(ð�ݷ�)
 void TransparentBlt2(HDC hdc0,		//Ŀ��DC
		int nX0,int nY0,int nW0,int nH0,//Ŀ��������,Ŀ���߿�
		HDC hdc1,						//ԴDC
		int nX1,int nY1,int nW1,int nH1,//Դ�������,Դ��߿�
		UINT Tcol);						//͸��ɫ,COLORREF����
 private://˽��,���ڲ�ʹ��
 BOOL inscreer(int i);				//����ʾ����
 int  getsys();						//ʶ��ϵͳ
 void bianfw (int q);				//��λת��
 void manmove(int i);				//�������ƶ�

 //A����̹���ʹ��//////////////////////////////////////////////
 void find_a(int i);				//û��Ѱ·ʱ��Ҫ��
 public://����,�ⲿ�ɵ��á�----------------------------------------
 HDC		BK;					//���ڵ�ͼ�ƶ�
 HBITMAP	bi;					//���ڵ�ͼ�ƶ�

 HBITMAP	bitya;
 BLENDFUNCTION rBlend;			//��͸��
 CFile		sfile,rfile,jfile;	//ѹ����Դ�����ļ�ָ��
 BYTE		*stmp,*rtmp,*jtmp;	//ѹ�����ڴ����

 int		sbufadd[SBUF];		//�޵���Դָ��
 int		rbufadd[RBUF];		//�˵���Դָ��
 int		jbufadd[JBUF];		//������Դָ��

 void Alphasetobj(int q,int a);	//��͸���Ķ�����ʾ
 void game::Alpha(int x,int y);//
 BOOL getpic0(CString cc,int p);//��ѹ��ͼƬ
 void Memcpy0(unsigned char *mu,unsigned char *yu,int z);
};