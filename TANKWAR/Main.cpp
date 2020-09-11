#include"StdAfx.h"
#include"map.h"
#include"player.h"
#include"DrawTools.h"
#include"CBulletManager.h"
#include"CBurstManager.h"
#include"NpcManager.h"
#include"score.h"
#include"GameOver.h"
 
#pragma comment(lib,"MSImg32.lib")
const int g_width = 800;
const int g_height = 600;

CDBBuffer buffer;
Cmap g_map ;
Cplayer player ;
COver          g_over;
CDrawTools     g_cdrawtools ;
CBulletManager g_CBulletManager;
CBurstManager  g_CBurstManager;
CNpcManager    g_CNpcManager;
CScore         g_score;
 

HWND g_hwnd ;
HDC  g_hdc;
HBITMAP g_hbmp;
HDC  memdc;
HDC  bufferdc;
float g_fElapasedTime = 0.0f;
static int g_state =0;
static int g_time = 0 ;
static bool g_Read = false ;
static bool g_InRect = false; 
static bool g_InRt = false ;
HBITMAP hbmap ;
HBITMAP hbrick ;
HBITMAP hgangzhuan;
HBITMAP hwater;

HBITMAP htank;
HBITMAP hmaskbmp;

void LoadResource()//加载资源
{ 
	g_cdrawtools.loadImage("map.bmp","bground");
	g_cdrawtools.loadImage("brick.bmp","brick");
	g_cdrawtools.loadImage("gangzhuan.bmp","gangzhuan");
	g_cdrawtools.loadImage("water.bmp","water");
	g_cdrawtools.loadImage("tank.bmp","tank");
	g_cdrawtools.loadImage("bullet.bmp","bullet");
	g_cdrawtools.loadImage("Boss.bmp","boss");
	g_cdrawtools.loadImage("grass.bmp","grass");
	g_cdrawtools.loadImage("bomb.bmp","bomb");
	g_cdrawtools.loadImage("NPC.bmp","NPC");
	g_cdrawtools.loadImage("gameover.bmp","over");
	g_cdrawtools.loadImage("win.bmp","win");
	g_cdrawtools.loadImage("GS0_BKIMAGE.bmp","GS0_BKIMAGE");
	g_cdrawtools.loadImage("GS3_JOINGAME1_BTN.bmp","GS3_JOINGAME1_BTN");
	g_cdrawtools.loadImage("GS3_JOINGAME2_BTN.bmp","GS3_JOINGAME2_BTN");
	g_cdrawtools.loadImage("GS3_JOINGAME3_BTN.bmp","GS3_JOINGAME3_BTN");
	g_cdrawtools.loadImage("GS0_EXITD_BTN.bmp","GS0_EXITD_BTN");
	g_cdrawtools.loadImage("GS0_EXITH_BTN.bmp","GS0_EXITH_BTN");
	g_cdrawtools.loadImage("GS0_EXITN_BTN.bmp","GS0_EXITN_BTN");
	
}

void KeyBoard()
{
	static bool IsUp = false ;
	if ( GetAsyncKeyState(38) & 0x8000 )
	{
		player.move( D_UP );
		player.collide(D_UP);		
	}
	else
	if ( GetAsyncKeyState(40) & 0x8000 )
	{
		player.move( D_DOWN );
		player.collide(D_DOWN);		 
	}
	else
	if ( GetAsyncKeyState(37) & 0x8000 )
	{
		player.move( D_LEFT );
		player.collide(D_LEFT);
	}
	else
	if ( GetAsyncKeyState(39) & 0x8000 )
	{
		player.move( D_RIGHT );
		player.collide(D_RIGHT);		
	}
	else
	if( GetAsyncKeyState(32) & 0x8000 )
	{
		if( IsUp == false )
		{
			player.Fire();
			PlaySound("hit.wav",NULL,SND_LOOP||SND_ASYNC);
			IsUp = true ;
		}
	}
	if( IsUp && !(GetAsyncKeyState(32) & 0x8000))
	{
		 IsUp = false ;
	}
}


void Logic()//逻辑判断
{
	switch(g_state)
	{
	case 1:
		if(!g_Read)
		{
			g_map.Initmap(g_Read);
			g_CNpcManager.CreatNpc(75,75,rand()%4);
			g_CNpcManager.CreatNpc(450,75,rand()%4);
			g_CNpcManager.CreatNpc(200,75,rand()%4);
			g_CNpcManager.CreatNpc(400,75,rand()%4);
			g_Read = true;
			
		}
		if(g_score.m_numNPC==0)
		{
			g_state = 2 ;
				 
		}
		if(g_score.m_Life==0||g_map.m_map[14][7].ID==0)
		{
			g_state = 3 ;
		};
		break ;
	case 2:
		if(g_Read)
		{
			g_map.Initmap(g_Read);
			g_CBulletManager.ClearUp();
			g_CBurstManager.ClearUp();
			g_CNpcManager.ClearUp();
			g_CNpcManager.CreatNpc(70,70,rand()%4);
			g_CNpcManager.CreatNpc(450,75,rand()%4);
			g_CNpcManager.CreatNpc(200,75,rand()%4);
			g_CNpcManager.CreatNpc(400,75,rand()%4);
			player.m_tx = 100;
			player.m_ty = 460;
			player.m_dir = 0 ;
			g_score.m_Life = 3 ;
			g_score.m_numNPC = 4 ;
			g_score.m_score = 0 ;
			g_Read = false ;
		}
		if(g_score.m_numNPC<1 && g_score.m_score>800)
		{
			g_state = 3 ;
		}
		if(g_score.m_Life<1 || g_map.m_map[14][7].ID==0)
		{
			g_state = 3 ;
		}
		break;
	case 3:
		g_time += 1;
		if(g_time > 1000)
		{
			g_CBurstManager.ClearUp();
			g_CBulletManager.ClearUp();
			g_CNpcManager.ClearUp();
			player.m_tx = 100;
			player.m_ty = 460;
			player.m_dir = 0 ;
			g_score.m_Life = 3 ;
			g_score.m_numNPC = 4 ;
			g_score.m_score = 0 ;
			g_state = 0;
			g_time = 0 ;
		}
		break;

	}

 
	KeyBoard();
	g_CBulletManager.Update();
	g_CNpcManager.Update();
	g_CNpcManager.Collide();
			 
	
}
void Render()//绘制地图
{
	float fFPS;
	static float fTime = 0.0f;
	static int   fFrame = 0;
	fTime+=g_fElapasedTime;
	if(fTime>=1.0f )
	{
		fFPS = (float)fFrame/fTime;
		fTime-=1.0f;
		fFrame=0;
	}
	fFrame++;

	switch(g_state)
	{
	case 0:
		g_cdrawtools.Render("GS0_BKIMAGE",0,0);
		if(g_InRect)
		{
			g_cdrawtools.Render("GS3_JOINGAME1_BTN",500,300,0,0,224,64);
			
		}else
		{
			g_cdrawtools.Render("GS3_JOINGAME2_BTN",500,300,0,0,224,64);
			
		}

		if(g_InRt)
		{
			g_cdrawtools.Render("GS0_EXITH_BTN",500,400,0,0,224,64);
		}
		else
		{
			g_cdrawtools.Render("GS0_EXITN_BTN",500,400,0,0,224,64);
		}
		
		
		break;
	case 1:
		g_cdrawtools.Render( "bground",0,0);
		g_map.Render();
		g_CBulletManager.Render();
		g_CNpcManager.Render();
		player.Render();
		g_CBurstManager.Render();
		g_map.RenderGrass();
		g_score.Render();
		break ;
	case 2:
		g_cdrawtools.Render( "bground",0,0);
		g_map.Render();
		g_CBulletManager.Render();
		g_CNpcManager.Render();
		player.Render();
		g_CBurstManager.Render();
		g_map.RenderGrass();
		g_score.Render();
		g_score.m_Level = 2 ;
		break;
	case 3:
		g_over.Render();
		break;
	
	}

	
	buffer.Flush();//从缓冲区画到屏幕上
	
};



LRESULT CALLBACK WndProc(//回调函数

	HWND hwnd,

    UINT uMsg,

    WPARAM wParam,

    LPARAM lParam
)
{
	
	PAINTSTRUCT ps ;
	POINT point ;
	RECT rect;
	RECT rt;

	SetRect(&rect,500,300,726,364);
	SetRect(&rt,500,400,726,464);

	switch( uMsg )
	{
	case WM_CREATE:
				
		break;
	case WM_ACTIVATE:
			
		 
		break;
	case WM_LBUTTONDOWN:
		switch(g_state)
		{
		case 0:
			if(g_InRect)
			{
				g_state=1;
				g_Read = false;
			}
			if(g_InRt)
			{
				exit(1);
			}
		break;
		}
		break;
	case WM_MOUSEMOVE:
		point.x= (int)LOWORD(lParam);
		point.y =  (int)HIWORD(lParam);
		if(PtInRect(&rect,point))
		{
			 g_InRect =true ;
			
		}
		else
		{
			 g_InRect =false ;
			 
		}
		if(PtInRect(&rt,point))
		{
			 g_InRt = true ;
		}
		else
		{
			g_InRt = false ;
		}
		break;
	case WM_TIMER:
	
		break;

	case WM_CLOSE:

		DestroyWindow( g_hwnd );

		break ;

	case WM_DESTROY:
		DeleteObject(hbmap);
		DeleteObject(hbrick);
		DeleteObject(hgangzhuan);
		DeleteObject(hwater);
		DeleteObject(hmaskbmp);
		DeleteDC( memdc);
		DeleteDC( bufferdc);	 
		PostQuitMessage( 0 );
		break ;

	}

	return DefWindowProc( hwnd,uMsg,wParam,lParam ) ;

}


int WINAPI WinMain(

	HINSTANCE hInstance,

    HINSTANCE hPrevInstance,

    LPSTR lpCmdLine,

    int nCmdShow
	)
{
	srand(::timeGetTime());

  WNDCLASSEX wc ;

  ZeroMemory(&wc , sizeof(wc)) ;

  wc.cbClsExtra     = 0 ;// 额外类空间，可选择在其存放窗口类所共有的数据

  wc.cbSize         = sizeof( WNDCLASSEX ) ;

  wc.cbWndExtra     = 0 ; // 额外窗口空间，可选择在其中存放每个窗口所拥有的数据

  wc.hbrBackground  = (HBRUSH)GetStockObject(GRAY_BRUSH) ;// 取得绘制窗口背景的画刷颜色

  wc.hCursor        = LoadCursor( NULL ,IDC_HAND ) ; // 窗口类的的鼠标光标

  wc.hIcon          = LoadIcon( NULL ,IDI_APPLICATION ) ;// 窗口上和任务栏上显示的图标

  wc.hIconSm        = LoadIcon( NULL, IDI_APPLICATION ) ; // 窗口上和任务栏上显示的小图标

  wc.hInstance      = hInstance ; // 应用程序的实例句柄，标识这个窗口类和哪个应用程序的实例相关联

  wc.lpfnWndProc    = WndProc ; // 此类窗口的消息处理函数，这里指WndProc函数

  wc.lpszClassName  = _T("window_class") ;// 此窗口类的名称

  wc.lpszMenuName   = 0 ;

   // 窗口类的“操作”风格	当窗口水平方向和垂直方向变化时重绘整个窗口

  wc.style			= CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS|CS_BYTEALIGNCLIENT|CS_GLOBALCLASS ;
 
  RegisterClassEx( &wc ) ;

  int width  = (GetSystemMetrics( SM_CXFULLSCREEN) - g_width )/2;
  int height = (GetSystemMetrics( SM_CYFULLSCREEN) - g_height)/2;

  g_hwnd = CreateWindowEx( 0 ,_T("window_class") ,_T("TANKWAR") ,WS_OVERLAPPEDWINDOW & ~WS_MINIMIZEBOX & ~WS_MAXIMIZEBOX,
	  width,height,g_width,g_height,NULL,NULL,hInstance,NULL ) ;

  if( !g_hwnd )
  {
	  return false;
  }

  	RECT rt;;
	int iwidth;
	int iheight;
	GetClientRect( g_hwnd,&rt) ;
	iwidth = rt.right - rt.left ;
	iheight = rt.bottom - rt.top ;
	g_hdc = GetDC(g_hwnd);
	memdc = CreateCompatibleDC( g_hdc );
	buffer.Init(g_hdc,iwidth,iheight);
	LoadResource();


  ShowWindow( g_hwnd, nCmdShow ) ;

  UpdateWindow( g_hwnd );

  MSG msg ;

  ZeroMemory( &msg ,sizeof(msg) ) ;//清空MSG中的数据

  while( msg.message != WM_QUIT )
  {
	  if( PeekMessage( &msg,NULL,0,0,PM_REMOVE ))
	  {
		  TranslateMessage( &msg ) ;//翻译消息

		  DispatchMessage( &msg ) ;//处理信息
	  
	  }
	  else
	  {
		  static float fPerTime = (float)timeGetTime();
		  float fCurrentTime = (float)timeGetTime();
		  g_fElapasedTime = (fCurrentTime - fPerTime )*0.001f;
		  fPerTime = fCurrentTime ;

		  Logic();
		  Render();		  
	  }
  }

  ReleaseDC(g_hwnd,g_hdc);
  UnregisterClass(_T("window_class"),hInstance) ;	//注销窗口类
	//函数的返回值
  return (int)msg.wParam ;

}