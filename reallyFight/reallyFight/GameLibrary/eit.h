#include "game_Ѱ·.h"
class gmedit : public gamepro	//�̳�gamepro�� 
{public: gmedit();	//���캯��
 virtual~gmedit();	//��������
 public://����,�ⲿ�ɵ���
 //��������
 short int 	gno;				//ѡ�еĶ������
 short int 	tml;				//������ָ��
 short int 	x1,y1;				//ѡ�еĶ��������
 CPen pen;						//�༭���񻭱�
 CPen penz;						//�༭�ϰ�����
 //��������
 void initedit();				//��ʼ��
 void exitedit();				//����
 void newmap ();				//�½���ͼ
 void savemap(CString name);	//�����ͼ
 void Delete();					//ɾ��
 void Insert(int no,int dorj);	//����
 void getwp(HDC hdc,int dorj);	//��ʾѡ�����
 void getno(int x,int y);		//ѡ�����
 void getobj(HDC hdc,int i);	//����ѡ��
 void showline();				//��ʾ�༭����
 void SaveBmp(CString fileName,LPBITMAPINFOHEADER bi1); 
};