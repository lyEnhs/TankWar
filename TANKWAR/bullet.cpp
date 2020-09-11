#include"StdAfx.h"
#include"bullet.h"
#include"player.h"
#include"map.h"
#include"DrawTools.h"
#include"NpcManager.h"
#include"score.h"
 
extern CScore g_score;
extern Cplayer player ;
extern CNpcManager    g_CNpcManager;
extern Cplayer player ;
extern Cmap g_map ;
extern float g_fElapasedTime;
extern CDrawTools g_cdrawtools;
Cbullet::Cbullet( ):m_Zdir(0),m_state(0),m_speed(100),m_x(0),m_y(0)  
{
	  //
}

Cbullet::~Cbullet()
{
	//
}

void Cbullet::InitBullet( int dir ,float x, float y,CRole *p )
{
	m_Zdir  = dir ;
	m_x    = x ;
	m_y    = y ;
	powner = p ;

}

void Cbullet::Update()
{	
	switch( m_Zdir )
	{
	 case 0:

		m_y -=g_fElapasedTime *m_speed;	

		break;
	 case 1:

		 m_y +=g_fElapasedTime *m_speed;

		 break;
	 case 2:
		
		 m_x -= g_fElapasedTime *m_speed;
			
		 break;
	 case 3:
		 
		 m_x += g_fElapasedTime *m_speed;

		 break;	  
	 }
}
bool  Cbullet::Judge()
{
	rt.left = m_x;
	rt.top  = m_y;
	rt.right = m_x + 8;
	rt.bottom  = m_y + 8;
/////////子弹与地图碰撞
	RECT DestRect;
	for(int i= 0;i<16;i++)
	{	
		for(int j=0;j<16;j++)
		{
			int ID =0;
			IntersectRect(&DestRect,&g_map.m_map[j][i].rt,&rt);
			ID = g_map.m_map[j][i].ID;
			if(ID == 1 || ID == 5 )
			{
				if(!IsRectEmpty(&DestRect))
				{				
					g_map.m_map[j][i].ID = 0 ;
					PlaySound("Bang.wav",NULL,SND_LOOP||SND_ASYNC);
					return true;
				}
			}
			
		}
	}
/////////player的子弹与NPC碰撞
	RECT ret ;
	std::list<CNpc*>::iterator itor = g_CNpcManager.ActiveList.begin();
	for( ; itor != g_CNpcManager.ActiveList.end(); itor++ )
	{
 		IntersectRect(&ret,&(*itor)->m_tank,&rt);

		if( !IsRectEmpty(&ret) && (powner == &player) )
		{
			(*itor)->m_state = 1 ;
			PlaySound("Bang.wav",NULL,SND_LOOP||SND_ASYNC);
			g_score.m_score += 200;
			g_score.m_numNPC--;
			if(g_score.m_numNPC < 0 )
			{
				g_score.m_numNPC = 0 ;
			}
			return true ;
		}
	
	}
///////NPC的子弹与player碰撞
	RECT rect;
	IntersectRect(&rect ,&player.m_tank,&rt);
	if(!IsRectEmpty(&rect)&&(powner != &player))
	{
		 PlaySound("Bang.wav",NULL,SND_LOOP||SND_ASYNC);
		if( g_score.m_Life>0)
		{
			player.InitPlayer(100,460,0,0);	
		}
		else
		{
			player.m_state = 1 ;
		}
		 g_score.m_Life--;
		 if(g_score.m_Life<0)
		  {
			 g_score.m_Life=0;
		  }
		return true ;
	}

	return false ;
}

void Cbullet::Render( )
{ 
	g_cdrawtools.Render("bullet",m_x,m_y,0,0,8,8 ); 
	
}
 