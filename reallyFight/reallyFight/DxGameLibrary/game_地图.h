#include "game.h"

class gamemap : public game	//�̳�game��
{public: gamemap();	//���캯��
 virtual~gamemap();	//��������
 public://����,�ⲿ�ɵ���
 HDC hScrDC0;
 HDC		SMAP;				//С��ͼ�豸���
 HBITMAP	mapbit;				//С��ͼλͼ�ڴ�
 CPen		pen0,pen1;			//�ס��컭�ʾ��
 short int 	fls;				//С��ͼ��˸
 short int 	mann;				//�����±�
 short int 	mapt,mapb;			//С��ͼ����
 short int 	mapl,mapr;			//С��ͼ����
 short int 	mapw,maph;			//С��ͼ�߿�
 short int 	movemap;			//��ͼ�ƶ���
 void initmap();				//��ʼ����ͼ����
 void exitmap();				//�˳�
 BOOL dingweimap(int x,int y);	//��λ��ͼ 
 void getsmap();				//����С��ͼ
 void smlmap(HDC dc);			//��ʾС��ͼ
 void movesmap(int x0,int y0);	//�ƶ���ͼ
 void mlmap();					//��ͼ���ƶ�ƴ��
 int  leftdown(HDC hdc,int x,int y);//�����
};