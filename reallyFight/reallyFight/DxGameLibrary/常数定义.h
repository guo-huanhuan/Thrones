/*********************************
[ѧVC����Ϸ]
������������ƣ������� 2004.7
E-mail:  cqtml@163.com
**********************************/
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")//ʱ�亯����
#include <wingdi.h>
#pragma comment (lib,"msimg32.lib")//͸����ʾ��
#include <vfw.h>
#pragma comment (lib,"vfw32.lib")
#include <ddraw.h>
#pragma comment (lib,"ddraw.lib")//DirectX��
//���峣��-------------------------------------------------
 #define SU_LIANG   450		//���������
 #define TIMER		120		//��ʱ������
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
 #define WBUF		10		//�������
//-------------------------------------------------------
 #define SCRWI0		840		//
 #define SCRHE0		780		//
 #define SCRW		100
 #define SCRH		150