/*********************************
[ѧVC����Ϸ]
������������ƣ������� 2004.7
E-mail:  cqtml@163.com
**********************************/
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")//ʱ�亯����
#include <wingdi.h>
#pragma comment (lib,"gdi32.lib")
#pragma comment (lib,"msimg32.lib")//͸����ʾ��
#include <vfw.h>
#pragma comment (lib,"vfw32.lib")

//���峣��-----------------------------------------------------------------------
 #define SU_LIANG   500		//���������
 #define TIMER		150		//��ʱ������
 #define WIDTH		640		//��Ϸ��ʾ����
 #define HEIGHT		480		//��Ϸ��ʾ����
 #define SCRWI		800		//��������
 #define SCRHE		600		//��������
 #define GX			40		//��ͼ���
 #define GY			30		//��ͼ���
 #define SCRP		12		//��ͼ���Ϊ��ʾ����12��
 #define SBUF		2801	//�������
 #define RBUF		801		//�������
 #define JBUF		100		//�������
