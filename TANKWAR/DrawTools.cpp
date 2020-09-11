#include"StdAfx.h"
#include"DrawTools.h"

extern CDBBuffer buffer;
CDrawTools::CDrawTools()
{
	m_hDC = NULL ;
}


CDrawTools::~CDrawTools()
{
	if( m_hDC )
	{
		DeleteDC( m_hDC );
	}

}
 void CDrawTools::loadImage( string pFileName , string Name ,int Frame )
{

	HBITMAP  h =(HBITMAP)::LoadImage( NULL,pFileName.c_str() ,IMAGE_BITMAP,0,0,LR_LOADFROMFILE );
	BITMAP	bmp;
	GetObject( h ,sizeof(BITMAP),&bmp );

	ImageInfo temp ; //位图结构初始化
	temp.m_hbmp = h;
	temp.m_iwidth =bmp.bmWidth ;
	temp.m_iheight = bmp.bmHeight ;
	temp.m_Hdc = ::CreateCompatibleDC(NULL);
	temp.m_iFrame = Frame ;
	temp.m_hbmpold = (HBITMAP)SelectObject(temp.m_Hdc ,temp.m_hbmp );
	m_map[Name] = temp;	//位图对应MAP实值
}

 void CDrawTools::Render(string Name, int x, int y )
 {
	 BitBlt( buffer,x,y,m_map[Name].m_iwidth,m_map[Name].m_iheight,m_map[Name].m_Hdc,0,0,SRCCOPY);
 }

 void CDrawTools::Render(std::string Name, int dx, int dy, int sx,int sy,int width, int height)
 {
	 TransparentBlt( buffer,dx,dy,width,height,m_map[Name].m_Hdc,sx,sy,width,height,RGB(0,0,0));
 }

 void CDrawTools::Renderbomb(std::string Name, int dx, int dy, int sx,int sy,int width, int height)
 {
	 TransparentBlt( buffer,dx,dy,width,height,m_map[Name].m_Hdc,sx,sy,width,height,RGB(255,0,255));
 }