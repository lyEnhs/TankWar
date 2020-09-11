#include"StdAfx.h"
#include"GameOver.h"
#include"DrawTools.h"
#include"score.h"
#include"map.h"

extern CScore         g_score;
extern Cmap g_map ;
extern CDrawTools g_cdrawtools;
extern CDBBuffer buffer;

COver::COver()
{
	//
}

COver::~COver()
{
	//
}


void COver::Render()
{
	
	if(g_map.m_map[14][7].ID==0||g_score.m_Life==0)
	{
		g_cdrawtools.Render("over",0,0);

	}
	if(g_score.m_numNPC==0&&g_score.m_score==800)
	{
		g_cdrawtools.Render("win",0,0);
	}
}