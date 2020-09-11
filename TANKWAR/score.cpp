#include"StdAfx.h"
#include"score.h"
#include"DrawTools.h"

extern CDrawTools g_cdrawtools;
extern CDBBuffer buffer;

static TCHAR contect1[] = _T("第%d关");
static TCHAR contect2[] = _T("生命条数为:%d");
static TCHAR contect3[] = _T("敌方坦克个数为:%d");
static TCHAR contect4[] = _T("score:%d");
CScore::CScore():m_Life(3),m_numNPC(4),m_Level(1)
{
	//
}

CScore::~CScore()
{
	//
}

void CScore::Render()
{

	sprintf_s(str,contect1,m_Level);
	TextOut(buffer,540,50,str,_tcslen(str));


	g_cdrawtools.Render("tank",540,100,0,20,20,20);
	sprintf_s(str,contect2,m_Life);
	TextOut(buffer,560,100,str,_tcslen(str));

	g_cdrawtools.Render("NPC",540,200,60,0,20,20);
	sprintf_s(str,contect3,m_numNPC);
	TextOut(buffer,560,200,str,_tcslen(str));

	sprintf_s(str,contect4,m_score);
	TextOut(buffer,540,300,str,_tcslen(str));

	SetTextColor(buffer,RGB(255,0,0));
	SetBkColor(buffer,RGB(0,0,0));
}