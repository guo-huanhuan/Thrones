/*********************************
[ѧVC����Ϸ]
������������ƣ������� 2004.7
E-mail:  cqtml@163.com
Download by http://www.codefans.net
**********************************/
#include "stdafx.h"
#include "�༭.h"

#define PALVERSION   0x300
#define WIDTHBYTES_E(bits) (((bits)+31)/32*4)
int PalEntriesOnDevice(HDC hDC);			// ��ȡ��ɫλ
HPALETTE GetSystemPalette();				// ��ȡϵͳ��ɫ��
WORD PaletteSize(LPBYTE lpDIB);				// �����ɫ�峤��
HANDLE BitmapToDIB(HBITMAP hBitmap, HPALETTE hPal);	// DDB->DIBת��

gmedit:: gmedit(){}	//���캯��
gmedit::~gmedit(){}	//��������

//��ͼ�༭��/////////////////////////////////////////
void gmedit::initedit()//��ʼ��
{	pen. CreatePen(PS_SOLID,1,RGB(0x80,0x80,0x80));	//�༭�����ɫ����
	penz.CreatePen(PS_SOLID,1,RGB(0x80,0x0,0x0));	//�ϰ����ɫ����
	initmap();//��ʼ����ͼ����
}
void gmedit::exitedit()//����
{	DeleteObject(pen);  //ɾ���༭�����ɫ����
	DeleteObject(penz); //ɾ���ϰ����ɫ����
	exitmap();
}
//**************************************************
// Insert(int no,int dorj) //����
//	�����no�Ŷ���dorj=0�Ǿ���dorj=1����
//**************************************************
void gmedit::Insert(int no,int dorj) //����
{	//dorjѡ��0�����1����
	if(rs>SU_LIANG-2)
		{AfxMessageBox("����������!");	 return;}
	 int i=rs;
	 man[i].jisu=i+1;				//���
	 if(dorj==0) man[i].lb=2;		//���:2��
	 else		 man[i].lb=1;		//���:1��
	 man[i].fw=1;					//��λ1����
	 man[i].zs=0;					//����0վ
	 man[i].p=no;					//����ͼ�κ�
	 man[i].js=dorj*(no-tml);		//��[0��1��2¹3��4ȸ5��6��]
	 if(man[i].lb!=2) setman(i);	//���û�����ֵ
	 getobjwh(i);					//ȡ����ĳߴ�
	 man[i].xix=scrx+WIDTH/2;		//��ǰλ��x
	 man[i].xiy=scry+HEIGHT/2;		//��ǰλ��y
	 man[i].x0=man[i].xix;			//Ŀ��λ��x
	 man[i].y0=man[i].xiy;			//Ŀ��λ��y
	 if(dorj==1)					//��������ޣ������߿�
	 {	int x=man[i].x0+(100-rand()%200);//x���λ��
		int y=man[i].y0+(100-rand()%200);//y���λ��
		FindPath(i,x,y);
	 }
	 rs++;//��������1
}
//**************************************************
// Delete() //ɾ��
//	ɾ��ѡ �е�gno�Ŷ��󡣲��������
//**************************************************
void gmedit::Delete() //ɾ��
{	if(gno==0||rs<2)	return;
	for(int i=0;i<rs;i++)
	  if(man[i].jisu==gno)
		{for (int j=i;j<rs-1;j++)	man[j]=man[j+1];//ɾ��gno
		 rs--;//��������1
		 for(int k=0;k<rs;k++)//�������
			if(man[k].jisu!=0) man[k].jisu=k+1;	
		 return;
		}
}
//**************************************************
// getno(int x,int y)ѡ�����
//��ڲ�����x,yΪ�����ʱ�����ꡣ
//���ڲ����������gno��Ϊѡ�ж������š�
//          �����x1,y1ѡ�ж�������ꡣ
//������������ͼ�ε�λ��ѡ�ж��������ƶ���ɾ������
//**************************************************
void gmedit::getno(int x,int y)//ѡ�����,�༭��ͼ��
{	gno=-1;//����ѡ������
	for(int i=0;i<rs;i++)
		{if((x+scrx)>(man[i].xix-man[i].w/2+2)&&(x+scrx)<(man[i].xix+man[i].w/2+2)&&
			(y+scry)>(man[i].xiy-man[i].h+10)&&(y+scry)<(man[i].xiy+10)) 
			{gno=man[i].jisu;	//����ѡ�ж�������
			 x1=man[i].xix;		//����ѡ�ж��������
			 y1=man[i].xiy;		//
			 return;
			}
		}
}
//**************************************************
// getobj(HDC hdc,int i)//����ѡ��
//	�ڶ���ѡ������ѡ�����
//**************************************************
void gmedit::getobj(HDC hdc,int i)//����ѡ��,�༭��ͼ��
{	int x,y=HEIGHT+19,w=48,h=47;
	CDC* bc = CDC::FromHandle (hdc);
	CPen *old;
	old=bc->SelectObject(&pen0);
	for(int j=0;j<12;j++)
	{x=j*50+2;
	 bc->MoveTo(x,y);	//ȫ��ˢ��
	 bc->LineTo(x+w,y);	 bc->LineTo(x+w,y+h);
	 bc->LineTo(x,y+h);	 bc->LineTo(x,y);
	}
	bc->SelectObject(old);
	if(i<0) return;
	old=bc->SelectObject(&pen1);
	x=(i-tml)*50+2;
	bc->MoveTo(x,y);	//ѡ���
	bc->LineTo(x+w,y);	 bc->LineTo(x+w,y+h);
	bc->LineTo(x,y+h);	 bc->LineTo(x,y);
	bc->SelectObject(old);
	CDC::DeleteTempMap( );
	BitBlt(hdc,WIDTH+10-1, SCRHE-100-1,w+1,h+1,hdc,x,y,SRCCOPY);//ѡ�ж��󿽱�����ѡ��
}
//**************************************************
// getwp(HDC hdc)//��ʾѡ�����,�༭��ͼ��
//	��ͼ����ѡ�������ž���͸����ʾ��
//
//**************************************************
void gmedit::getwp(HDC hdc,int dorj)//��ʾѡ�����
{	CString cc;
	int xx=2;	int yy=HEIGHT+18;//��ʾ����λ
	int wh=50;
	if(edi==0)//�Ǳ༭̬��ѡ�����װ�ʻ�ɫ
	{CBrush Brush(RGB(0xd0,0xd0,0xd0));
	 SelectObject(hdc,Brush);
	 PatBlt(hdc,xx,yy,WIDTH,wh,PATCOPY);			//ѡ����
	 PatBlt(hdc,WIDTH+8, SCRHE-102,50,50,PATCOPY);	//��ѡ��
	 return;
	}
	else //�༭̬��ѡ��������ͼ��
		BitBlt(hdc,xx,yy,WIDTH,wh,BkDC0,0,0,SRCCOPY);//ѡ����
	int p=0;//����ָ��
	int tml0;
	if(dorj==1) tml0=0;
	else		tml0=tml;
	for(int i=tml0;i<tml0+12;i++)
	{int p0;
	 if(dorj==0){cc="��";p0=i;}
	 else		{cc="��";p0=i*400+1*5;}
	 if(getpic(cc,p0)==FALSE) 
				{getobj(hdc,-1);return;}
	 //ͼ�����ž���
	 float wi0=(float)w,he0=(float)h;
	 float bl=wi0/he0;
	 if(wi0<wh&&he0<wh) goto aa;
	 if(bl>1)	{wi0=(float)wh;he0=wi0/bl;}
	 else		{he0=(float)wh;wi0=he0*bl;}
aa:	 int x0=(int)(wh-wi0)/2+p*wh+xx;
	 int y0=(int)(wh-he0)/2+yy;
	 TransparentBlt2(hdc,x0,y0,(int)wi0,(int)he0,MemDC,0,0,w,h,RGB(255,255,255));
	 p++;
	}
	getobj(hdc,-1);
}
//**************************************************
// showline()//��ʾ�༭����
//	�ڱ༭̬��ʾ�༭������ϰ���
//**************************************************
void gmedit::showline()//��ʾ�༭����
{	 CDC* bc = CDC::FromHandle (BkDC1);
	 CPen *old;
	 old=bc->SelectObject(&pen);
	 for(int i=GY;i<HEIGHT;i=i+GY)//����
		 {bc->MoveTo(0,i);  bc->LineTo(WIDTH,i); }
	 for(int j=GX;j<WIDTH;j=j+GX)//����
		 {bc->MoveTo(j,0);  bc->LineTo(j,HEIGHT);}
	 bc->SelectObject(old);
	 //------------------------------------------
	 old=bc->SelectObject(&penz);//��ʾ�ϰ���
	 for(i=0;i<WIDTH+GX;i=i+GX)
	   for(j=0;j<HEIGHT+GY;j=j+GY)
		 {int x=(i+scrx)/GX-1,y=(j+scry)/GY-1;
		  if(m_fid.map[x][y]=='1')//���ϰ��� 
		  {	bc->MoveTo(i,j);	bc->LineTo(i-GX,j-GY);//��
			bc->MoveTo(i-GX,j);	bc->LineTo(i,j-GY);
			bc->MoveTo(i,j);						  //����
			bc->LineTo(i,j-GY);	bc->LineTo(i-GX,j-GY);
			bc->LineTo(i-GX,j);	bc->LineTo(i,j);
		  }
		 }
	 //------------------------------------------
	for(i=0;i<rs;i++)//��ʾѡ�еĶ���
	 if(gno==man[i].jisu)
		{int w=man[i].w;
		 int h=man[i].h;
		 int x=man[i].xix-scrx-w/2;		//x��ǰλ��
		 int y=man[i].xiy-scry-h;		//y��ǰλ��
		 old=bc->SelectObject(&pen1);
		 bc->MoveTo(x,y);
		 bc->LineTo(x+w,y);	 bc->LineTo(x+w,y+h);
		 bc->LineTo(x,y+h);	 bc->LineTo(x,y);
		 bc->SelectObject(old);
		}
	 bc->SelectObject(old);
	 CDC::DeleteTempMap( );
}
//**************************************************
//	savemap(CString name)//�����ͼ
//	A��������ƺõĶ��󳡾�(.dat)
//	   �����ļ�(.dat)�ĸ�ʽ��
//		��1�У�Ϊ����ͼ��
//		��2�У�������,����һ����һ������
//		���,���,��ɫ,����ͼ�κ�,x,yλ��6������
//	B������ �ϰ���(.map)���ϰ���ĸ�ʽ��
//		��1�У��ϰ��������ֵ���Ժ�1 �о����ϰ���1�е����ݡ�
//**************************************************
void gmedit::savemap(CString name)//�����ͼ
{//	A��������󳡾�(.dat) 
  FILE *f;
  int i,j;
  f=fopen(name,"w");
  if(f==NULL) {AfxMessageBox("����д�ļ�!!!");return;}
  fprintf(f,"%s\n",mapbak);			//��ͼ����
  fprintf(f,"%d\n",rs);				//������
  for (i=0;i<rs;i++)
	{fprintf(f,"%d,",man[i].jisu);	//���
	 fprintf(f,"%d,",man[i].lb);	//���:  [0��1��2��]
	 fprintf(f,"%d,",man[i].js);	//��ɫ:��[0��1Ů]
									//��ɫ:��[0��1��2¹3��4ȸ5��6��]
	 fprintf(f,"%d,",man[i].p);		//����ͼ�κ�
	 fprintf(f,"%d,",man[i].xix);	//��ǰλ��x
	 fprintf(f,"%d,\n",man[i].xiy);	//��ǰλ��y
	}
  fclose(f);
//	B�������ϰ���(.map)
  char cc[256];
  strcpy(cc,name);cc[lstrlen(name)-3]=0;//�任�ļ���
  strcat(cc,"map");
  f=fopen(cc,"w");
  if(f==NULL) {AfxMessageBox("����д�ļ�!!!");return;}
  fprintf(f,"%d,%d\n",WIDTH*SCRP0/GX,HEIGHT*SCRP0/GY);
  for(i=0;i<WIDTH*SCRP0/GX;i++)
  {for(j=0;j<HEIGHT*SCRP0/GY;j++)
	 fprintf(f,"%c",m_fid.map[i][j]);
   fprintf(f,"\n");
  }
  fclose(f);
/*  //========DDBת��ΪDIB=======================================================
	HPALETTE  hPal= GetSystemPalette();// ��ȡϵͳ��ɫ��
	HANDLE hDIB = BitmapToDIB(mapbit,hPal);// DDB->DIBת��
	DeleteObject(hPal);
//========��ͼ�ο���tmp����
	LPBITMAPINFOHEADER bi1 = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	strcpy(cc,name);cc[lstrlen(name)-3]=0;//�任�ļ���
	strcat(cc,"bmp");
	SaveBmp(cc,bi1); //��λͼ
	GlobalUnlock(hDIB); 
	DeleteObject(hDIB);GlobalFree(hDIB);*/
}
//**************************************************
//	newmap()//�½���ͼ
//	�����½���ͼѡ���Ľ�ɫ����ʼ�������͵�ͼ��С��
//**************************************************
void gmedit::newmap()//�½���ͼ
{	rs=1;
	man[0].jisu=0;//���
	man[0].lb=0;  //���:  [0��1��2��]
//	man[0].js=1;  //��ɫ:��[0��1Ů]
				  //��ɫ:��[0��1��2¹3��4ȸ5��6��]
	man[0].p=0;	  //����ͼ�κ�
	man[0].xix=WIDTH/2;		//��ǰλ��x
	man[0].xiy=HEIGHT/2;	//��ǰλ��y

	man[0].x0=man[0].xix;	//Ŀ��λ��x
	man[0].y0=man[0].xiy;	//Ŀ��λ��y
	man[0].fw=1;	//��λ:  [0��1����2��3����4��5����6��7����]
	man[0].zs=0;	//����:��[0վ1��2��3��4��]
					//����:��[0վ1��2��3��4��5ʬ]
	man[0].pk =-1;	//·����
	man[0].fid=-1;	//·������
	man[0].zd=0;
	setman(man[0].jisu);	//���û�����ֵ
	getobjwh(0);			//ȡ����ĳߴ�
	//���ͼ��С
	m_fid.map_w=WIDTH*SCRP0/GX;	//
	m_fid.map_h=HEIGHT*SCRP0/GY;//
	int i,j;
	for(i=0;i<m_fid.map_w;i++)
		for(j=0;j<m_fid.map_h;j++)
				m_fid.map[i][j]='0';	
	getsmap();	//����С��ͼ
}
void gmedit::SaveBmp(CString fileName,LPBITMAPINFOHEADER bi1) //��λͼ
{   BITMAPFILEHEADER hdr;
    DWORD dwTmp;
	if(bi1==NULL){AfxMessageBox("��ͼ������!");return;}
    HANDLE hf = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE,(DWORD) 0,NULL,
					CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,(HANDLE) NULL); 
    hdr.bfType = 0x4d42; // 0x42 = "B" 0x4d = "M" 
    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) +bi1->biSize + bi1->biClrUsed 
                 * sizeof(RGBQUAD) + bi1->biSizeImage); 
    hdr.bfReserved1 = 0; hdr.bfReserved2 = 0;  
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +bi1->biSize
						+bi1->biClrUsed * sizeof (RGBQUAD); 
    WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
        (LPDWORD) &dwTmp,  NULL);  
    WriteFile(hf, (LPVOID) bi1, sizeof(BITMAPINFOHEADER)-bi1->biSize
                  + bi1->biClrUsed * sizeof (RGBQUAD),(LPDWORD) &dwTmp, (NULL)); 
    DWORD dwTotal = bi1->biSizeImage;
    WriteFile(hf, (LPSTR) bi1, (int) dwTotal, (LPDWORD) &dwTmp,NULL);
	CloseHandle(hf);
}
HANDLE BitmapToDIB(HBITMAP hBitmap, HPALETTE hPal)// DDB->DIBת��
{
    BITMAP              bm;       
    BITMAPINFOHEADER    bi;       
    LPBITMAPINFOHEADER  lpbi;     
    DWORD               dwLen;    
    HANDLE              hDIB, h;  
    HDC                 hDC;      
    WORD                biBits;   

    if (!hBitmap) return NULL;
    if (!GetObject(hBitmap, sizeof(bm), (LPBYTE)&bm)) return NULL;
    if (hPal == NULL) hPal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);
    biBits = bm.bmPlanes * bm.bmBitsPixel;
    if (biBits <= 1) biBits = 1;
    else if (biBits <= 4) biBits = 4;
	else if (biBits <= 8) biBits = 8;
    else biBits = 16;// if greater than 8-bit, force to 24-bit
    // initialize BITMAPINFOHEADER
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = bm.bmWidth;
    bi.biHeight = bm.bmHeight;
    bi.biPlanes = 1;
    bi.biBitCount = biBits;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;
    // calculate size of memory block required to store BITMAPINFO
    dwLen = bi.biSize + PaletteSize((LPBYTE)&bi);
    hDC = GetDC(NULL);
    hPal = SelectPalette(hDC, hPal, FALSE);
    RealizePalette(hDC);
    hDIB = GlobalAlloc(GHND, dwLen);
    if (!hDIB)
    {	SelectPalette(hDC, hPal, TRUE);
		RealizePalette(hDC);
		ReleaseDC(NULL, hDC);
		return NULL;
    }
    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
    *lpbi = bi; 
	GetDIBits(hDC, hBitmap, 0, (UINT)bi.biHeight, NULL, (LPBITMAPINFO)lpbi,
        DIB_RGB_COLORS);
    bi = *lpbi;
    GlobalUnlock(hDIB);
    if (bi.biSizeImage == 0)
        bi.biSizeImage = WIDTHBYTES_E((DWORD)bm.bmWidth * biBits) * bm.bmHeight;
    dwLen = bi.biSize + PaletteSize((LPBYTE)&bi) + bi.biSizeImage;
    if (h = GlobalReAlloc(hDIB, dwLen, 0)) hDIB = h;
    else
    {   GlobalFree(hDIB);
        hDIB = NULL;
        SelectPalette(hDC, hPal, TRUE);
        RealizePalette(hDC);
        ReleaseDC(NULL, hDC);
        return NULL;
    }
    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	if (GetDIBits(hDC, hBitmap, 0, (UINT)bi.biHeight, (LPBYTE)lpbi +
            (WORD)lpbi->biSize + PaletteSize((LPBYTE)lpbi), (LPBITMAPINFO)lpbi,
            DIB_RGB_COLORS) == 0)
    {   GlobalUnlock(hDIB);
        hDIB = NULL;
        SelectPalette(hDC, hPal, TRUE);
        RealizePalette(hDC);
        ReleaseDC(NULL, hDC);
        return NULL;
    }	
    bi = *lpbi;
    GlobalUnlock(hDIB);
    SelectPalette(hDC, hPal, TRUE);
    RealizePalette(hDC);
    ReleaseDC(NULL, hDC);
    return hDIB;
}
WORD PaletteSize(LPBYTE lpDIB)// �����ɫ�峤��
{   WORD wBitCount;  
    DWORD dwClrUsed;
    dwClrUsed = ((LPBITMAPINFOHEADER)lpDIB)->biClrUsed;
    if (dwClrUsed) return (WORD)dwClrUsed*sizeof(RGBQUAD);
    wBitCount = ((LPBITMAPINFOHEADER)lpDIB)->biBitCount;
    switch (wBitCount)
    {   case 1:return 2*sizeof(RGBQUAD);
        case 4:return 16*sizeof(RGBQUAD);
        case 8:return 256*sizeof(RGBQUAD);
        default:return 0;
    }
}
HPALETTE GetSystemPalette()// ��ȡϵͳ��ɫ��
{   HDC hDC;               
    static HPALETTE hPal = NULL;
    HANDLE hLogPal;         
    LPLOGPALETTE lpLogPal;  
    int nColors;            
    hDC = GetDC(NULL);
    if (!hDC)return NULL;
    nColors = PalEntriesOnDevice(hDC);   // Number of palette entrie
    hLogPal = GlobalAlloc(GHND, sizeof(LOGPALETTE) + nColors * sizeof(PALETTEENTRY));
    if (!hLogPal)return NULL;
    lpLogPal = (LPLOGPALETTE)GlobalLock(hLogPal);
    lpLogPal->palVersion = PALVERSION;
    lpLogPal->palNumEntries = nColors;
    GetSystemPaletteEntries(hDC, 0, nColors,(LPPALETTEENTRY)(lpLogPal->palPalEntry));
    hPal = CreatePalette(lpLogPal);
    GlobalUnlock(hLogPal);
    GlobalFree(hLogPal);
    ReleaseDC(NULL, hDC);
    return hPal;
}

int PalEntriesOnDevice(HDC hDC)// ��ȡ��ɫλ
{   int nColors;
    nColors = (1 << (GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES)));
    ASSERT(nColors);
    return nColors;
}