/*********************************
[学VC编游戏]
编著、程序设计：唐明理 2004.7
E-mail:  cqtml@163.com
Download by http://www.codefans.net
**********************************/
#include "stdafx.h"
#include "编辑.h"

#define PALVERSION   0x300
#define WIDTHBYTES_E(bits) (((bits)+31)/32*4)
int PalEntriesOnDevice(HDC hDC);			// 获取颜色位
HPALETTE GetSystemPalette();				// 获取系统调色板
WORD PaletteSize(LPBYTE lpDIB);				// 计算调色板长度
HANDLE BitmapToDIB(HBITMAP hBitmap, HPALETTE hPal);	// DDB->DIB转化

gmedit:: gmedit(){}	//构造函数
gmedit::~gmedit(){}	//析构函数

//地图编辑用/////////////////////////////////////////
void gmedit::initedit()//初始化
{	pen. CreatePen(PS_SOLID,1,RGB(0x80,0x80,0x80));	//编辑方格灰色画笔
	penz.CreatePen(PS_SOLID,1,RGB(0x80,0x0,0x0));	//障碍点褐色画笔
	initmap();//初始化地图参数
}
void gmedit::exitedit()//返回
{	DeleteObject(pen);  //删除编辑方格灰色画笔
	DeleteObject(penz); //删除障碍点褐色画笔
	exitmap();
}
//**************************************************
// Insert(int no,int dorj) //插入
//	插入第no号对象，dorj=0是景；dorj=1是兽
//**************************************************
void gmedit::Insert(int no,int dorj) //插入
{	//dorj选择0景物或1动物
	if(rs>SU_LIANG-2)
		{AfxMessageBox("对象数超出!");	 return;}
	 int i=rs;
	 man[i].jisu=i+1;				//序号
	 if(dorj==0) man[i].lb=2;		//类别:2景
	 else		 man[i].lb=1;		//类别:1兽
	 man[i].fw=1;					//方位1西南
	 man[i].zs=0;					//动作0站
	 man[i].p=no;					//静物图形号
	 man[i].js=dorj*(no-tml);		//兽[0豹1狼2鹿3马4雀5羊6猪]
	 if(man[i].lb!=2) setman(i);	//设置活动对象初值
	 getobjwh(i);					//取对象的尺寸
	 man[i].xix=scrx+WIDTH/2;		//当前位置x
	 man[i].xiy=scry+HEIGHT/2;		//当前位置y
	 man[i].x0=man[i].xix;			//目标位置x
	 man[i].y0=man[i].xiy;			//目标位置y
	 if(dorj==1)					//加入的是兽，马上走开
	 {	int x=man[i].x0+(100-rand()%200);//x随机位移
		int y=man[i].y0+(100-rand()%200);//y随机位移
		FindPath(i,x,y);
	 }
	 rs++;//对象数加1
}
//**************************************************
// Delete() //删除
//	删除选 中的gno号对象。并重整序号
//**************************************************
void gmedit::Delete() //删除
{	if(gno==0||rs<2)	return;
	for(int i=0;i<rs;i++)
	  if(man[i].jisu==gno)
		{for (int j=i;j<rs-1;j++)	man[j]=man[j+1];//删除gno
		 rs--;//对象数减1
		 for(int k=0;k<rs;k++)//重整序号
			if(man[k].jisu!=0) man[k].jisu=k+1;	
		 return;
		}
}
//**************************************************
// getno(int x,int y)选择对象
//入口参数，x,y为按左键时的坐标。
//出口参数，类变量gno中为选中对象的序号。
//          类变量x1,y1选中对象的坐标。
//在主显区根据图形的位置选中对象；用于移动或删除对象。
//**************************************************
void gmedit::getno(int x,int y)//选择对象,编辑地图用
{	gno=-1;//对象选择重置
	for(int i=0;i<rs;i++)
		{if((x+scrx)>(man[i].xix-man[i].w/2+2)&&(x+scrx)<(man[i].xix+man[i].w/2+2)&&
			(y+scry)>(man[i].xiy-man[i].h+10)&&(y+scry)<(man[i].xiy+10)) 
			{gno=man[i].jisu;	//保存选中对象的序号
			 x1=man[i].xix;		//保存选中对象的坐标
			 y1=man[i].xiy;		//
			 return;
			}
		}
}
//**************************************************
// getobj(HDC hdc,int i)//加入选择
//	在对象选择栏中选择对象。
//**************************************************
void gmedit::getobj(HDC hdc,int i)//加入选择,编辑地图用
{	int x,y=HEIGHT+19,w=48,h=47;
	CDC* bc = CDC::FromHandle (hdc);
	CPen *old;
	old=bc->SelectObject(&pen0);
	for(int j=0;j<12;j++)
	{x=j*50+2;
	 bc->MoveTo(x,y);	//全部刷新
	 bc->LineTo(x+w,y);	 bc->LineTo(x+w,y+h);
	 bc->LineTo(x,y+h);	 bc->LineTo(x,y);
	}
	bc->SelectObject(old);
	if(i<0) return;
	old=bc->SelectObject(&pen1);
	x=(i-tml)*50+2;
	bc->MoveTo(x,y);	//选择框
	bc->LineTo(x+w,y);	 bc->LineTo(x+w,y+h);
	bc->LineTo(x,y+h);	 bc->LineTo(x,y);
	bc->SelectObject(old);
	CDC::DeleteTempMap( );
	BitBlt(hdc,WIDTH+10-1, SCRHE-100-1,w+1,h+1,hdc,x,y,SRCCOPY);//选中对象拷贝到被选框
}
//**************************************************
// getwp(HDC hdc)//显示选择对象,编辑地图用
//	调图形在选择栏缩放居中透明显示。
//
//**************************************************
void gmedit::getwp(HDC hdc,int dorj)//显示选择对象
{	CString cc;
	int xx=2;	int yy=HEIGHT+18;//显示栏定位
	int wh=50;
	if(edi==0)//非编辑态，选择栏底板呈灰色
	{CBrush Brush(RGB(0xd0,0xd0,0xd0));
	 SelectObject(hdc,Brush);
	 PatBlt(hdc,xx,yy,WIDTH,wh,PATCOPY);			//选择栏
	 PatBlt(hdc,WIDTH+8, SCRHE-102,50,50,PATCOPY);	//被选框
	 return;
	}
	else //编辑态，选择栏调地图块
		BitBlt(hdc,xx,yy,WIDTH,wh,BkDC0,0,0,SRCCOPY);//选择栏
	int p=0;//计数指针
	int tml0;
	if(dorj==1) tml0=0;
	else		tml0=tml;
	for(int i=tml0;i<tml0+12;i++)
	{int p0;
	 if(dorj==0){cc="景";p0=i;}
	 else		{cc="兽";p0=i*400+1*5;}
	 if(getpic(cc,p0)==FALSE) 
				{getobj(hdc,-1);return;}
	 //图形缩放居中
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
// showline()//显示编辑方格
//	在编辑态显示编辑方格和障碍格
//**************************************************
void gmedit::showline()//显示编辑方格
{	 CDC* bc = CDC::FromHandle (BkDC1);
	 CPen *old;
	 old=bc->SelectObject(&pen);
	 for(int i=GY;i<HEIGHT;i=i+GY)//横条
		 {bc->MoveTo(0,i);  bc->LineTo(WIDTH,i); }
	 for(int j=GX;j<WIDTH;j=j+GX)//竖条
		 {bc->MoveTo(j,0);  bc->LineTo(j,HEIGHT);}
	 bc->SelectObject(old);
	 //------------------------------------------
	 old=bc->SelectObject(&penz);//显示障碍格
	 for(i=0;i<WIDTH+GX;i=i+GX)
	   for(j=0;j<HEIGHT+GY;j=j+GY)
		 {int x=(i+scrx)/GX-1,y=(j+scry)/GY-1;
		  if(m_fid.map[x][y]=='1')//画障碍格 
		  {	bc->MoveTo(i,j);	bc->LineTo(i-GX,j-GY);//叉
			bc->MoveTo(i-GX,j);	bc->LineTo(i,j-GY);
			bc->MoveTo(i,j);						  //方格
			bc->LineTo(i,j-GY);	bc->LineTo(i-GX,j-GY);
			bc->LineTo(i-GX,j);	bc->LineTo(i,j);
		  }
		 }
	 //------------------------------------------
	for(i=0;i<rs;i++)//显示选中的对象
	 if(gno==man[i].jisu)
		{int w=man[i].w;
		 int h=man[i].h;
		 int x=man[i].xix-scrx-w/2;		//x当前位置
		 int y=man[i].xiy-scry-h;		//y当前位置
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
//	savemap(CString name)//保存地图
//	A、保存编制好的对象场景(.dat)
//	   场景文件(.dat)的格式：
//		第1行，为背景图形
//		第2行，对象数,后面一行是一个对象。
//		序号,类别,角色,静物图形号,x,y位置6个数据
//	B、保存 障碍表(.map)，障碍表的格式：
//		第1行，障碍表的行列值，以后1 行就是障碍表1行的数据。
//**************************************************
void gmedit::savemap(CString name)//保存地图
{//	A、保存对象场景(.dat) 
  FILE *f;
  int i,j;
  f=fopen(name,"w");
  if(f==NULL) {AfxMessageBox("不能写文件!!!");return;}
  fprintf(f,"%s\n",mapbak);			//地图块名
  fprintf(f,"%d\n",rs);				//对象数
  for (i=0;i<rs;i++)
	{fprintf(f,"%d,",man[i].jisu);	//序号
	 fprintf(f,"%d,",man[i].lb);	//类别:  [0人1兽2景]
	 fprintf(f,"%d,",man[i].js);	//角色:人[0男1女]
									//角色:兽[0豹1狼2鹿3马4雀5羊6猪]
	 fprintf(f,"%d,",man[i].p);		//静物图形号
	 fprintf(f,"%d,",man[i].xix);	//当前位置x
	 fprintf(f,"%d,\n",man[i].xiy);	//当前位置y
	}
  fclose(f);
//	B、保存障碍表(.map)
  char cc[256];
  strcpy(cc,name);cc[lstrlen(name)-3]=0;//变换文件名
  strcat(cc,"map");
  f=fopen(cc,"w");
  if(f==NULL) {AfxMessageBox("不能写文件!!!");return;}
  fprintf(f,"%d,%d\n",WIDTH*SCRP0/GX,HEIGHT*SCRP0/GY);
  for(i=0;i<WIDTH*SCRP0/GX;i++)
  {for(j=0;j<HEIGHT*SCRP0/GY;j++)
	 fprintf(f,"%c",m_fid.map[i][j]);
   fprintf(f,"\n");
  }
  fclose(f);
/*  //========DDB转换为DIB=======================================================
	HPALETTE  hPal= GetSystemPalette();// 获取系统调色板
	HANDLE hDIB = BitmapToDIB(mapbit,hPal);// DDB->DIB转化
	DeleteObject(hPal);
//========将图形拷入tmp缓冲
	LPBITMAPINFOHEADER bi1 = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
	strcpy(cc,name);cc[lstrlen(name)-3]=0;//变换文件名
	strcat(cc,"bmp");
	SaveBmp(cc,bi1); //存位图
	GlobalUnlock(hDIB); 
	DeleteObject(hDIB);GlobalFree(hDIB);*/
}
//**************************************************
//	newmap()//新建地图
//	根据新建地图选定的角色，初始化对象表和地图大小。
//**************************************************
void gmedit::newmap()//新建地图
{	rs=1;
	man[0].jisu=0;//序号
	man[0].lb=0;  //类别:  [0人1兽2景]
//	man[0].js=1;  //角色:人[0男1女]
				  //角色:兽[0豹1狼2鹿3马4雀5羊6猪]
	man[0].p=0;	  //静物图形号
	man[0].xix=WIDTH/2;		//当前位置x
	man[0].xiy=HEIGHT/2;	//当前位置y

	man[0].x0=man[0].xix;	//目标位置x
	man[0].y0=man[0].xiy;	//目标位置y
	man[0].fw=1;	//方位:  [0南1西南2西3西北4北5东北6东7东南]
	man[0].zs=0;	//动作:人[0站1走2刺3劈4倒]
					//动作:兽[0站1走2跑3斗4倒5尸]
	man[0].pk =-1;	//路径长
	man[0].fid=-1;	//路径计数
	man[0].zd=0;
	setman(man[0].jisu);	//设置活动对象初值
	getobjwh(0);			//取对象的尺寸
	//设地图大小
	m_fid.map_w=WIDTH*SCRP0/GX;	//
	m_fid.map_h=HEIGHT*SCRP0/GY;//
	int i,j;
	for(i=0;i<m_fid.map_w;i++)
		for(j=0;j<m_fid.map_h;j++)
				m_fid.map[i][j]='0';	
	getsmap();	//生成小地图
}
void gmedit::SaveBmp(CString fileName,LPBITMAPINFOHEADER bi1) //存位图
{   BITMAPFILEHEADER hdr;
    DWORD dwTmp;
	if(bi1==NULL){AfxMessageBox("无图形数据!");return;}
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
HANDLE BitmapToDIB(HBITMAP hBitmap, HPALETTE hPal)// DDB->DIB转化
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
WORD PaletteSize(LPBYTE lpDIB)// 计算调色板长度
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
HPALETTE GetSystemPalette()// 获取系统调色板
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

int PalEntriesOnDevice(HDC hDC)// 获取颜色位
{   int nColors;
    nColors = (1 << (GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES)));
    ASSERT(nColors);
    return nColors;
}