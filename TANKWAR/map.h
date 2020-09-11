#pragma once

#include"StdAfx.h"

class Cmap
{
	struct Smap
	{
		int ID ;
		RECT rt;
	};
public:
	Cmap();
	
	~Cmap();

	void Initmap(bool read);//读取文件信息
	void Render();//渲染
	void RenderGrass();//渲染草坪

	Smap m_map[16][16];//位图结构体信息


};


