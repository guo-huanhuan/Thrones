#include "game_��ͼ.h"
#include "�����㷨.h"
class gamepro : public gamemap	//�̳�gamemap��
{public: gamepro();	//���캯��
 virtual~gamepro();	//��������
 public://����,�ⲿ�ɵ���
 //��������
 findpt		m_fid;				//A*�����������------
 PATHN		pathn[500];			//����·��
 BOOL		fidf;				//����æ�б�־

 //��������
 //BOOL pongcung(int i);			//���ϰ���ײ���(??)
 void loadza(CString name);			//�����ϰ���
 void lookit(int i);				//��ɫ��ײ
 void randxy();						//��������޵��ƶ�Ŀ��
 void loaddata();					//��ѹ����Դ��
 int  FindPath(int i,int x,int y);	//A*�㷨Ѱ·
 int  leftdown(HDC hdc,int x,int y);//�����
 int  zlpath();						//����·��

};