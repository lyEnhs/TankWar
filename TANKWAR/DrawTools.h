#pragma once
#include"StdAfx.h"
#include<string>
#include<map>

class	CDBBuffer//双缓冲区
{
public:
	CDBBuffer()
	{
	};

	~CDBBuffer()
	{
		if(m_hMemDc != NULL)
		{
			DeleteDC(m_hMemDc);
		}
		if(m_hBmap != NULL)
		{
			DeleteObject( m_hBmap);
		}
	}

	void Init(HDC hdc ,int iwidth ,int iheight)//初始化
	{
		m_hdc = hdc;
		m_iwidth = iwidth ;
		m_iheight = iheight;
		m_hMemDc = ::CreateCompatibleDC(hdc);
		m_hBmap = ::CreateCompatibleBitmap( hdc,iwidth,iheight);
		SelectObject(m_hMemDc,m_hBmap);//位图与DC相绑定
	}

	void Flush()
	{
		BitBlt( m_hdc,0,0,m_iwidth,m_iheight,m_hMemDc,0,0,SRCCOPY);//把DC上的图片画到前台
	}

	inline operator HDC()
	{
		return m_hMemDc;
	}
	inline operator HBITMAP()
	{
		return m_hBmap;
	}

	HDC m_hdc ;
	HDC m_hMemDc;
	HBITMAP m_hBmap;
	int m_iwidth;
	int m_iheight;

};
class CDrawTools//绘图工具
{

	struct ImageInfo//图片信息
	{
		HDC         m_Hdc;
		HBITMAP		m_hbmp;
		HBITMAP		m_hbmpold;
		int			m_iwidth;
		int			m_iheight;
		int			m_iFrame;
	};

	std::map<string,ImageInfo> m_map;//MAP容器
	

public:

	CDrawTools();
	~CDrawTools();

	void Init( HDC hdc )
	{
		m_hDC = hdc;
	
	}
	void loadImage( string pFileName , string Name ,int Frame = 1);//加载位图
	//渲染各种位图的方法
	void Render( string Name, int x, int y);
	void Render( string Name, int dx, int dy,int sx,int sy,int width ,int height );
	void Renderbomb( string Name, int dx, int dy,int sx,int sy,int width ,int height );

	HDC m_hDC;
	int m_frame;

};
