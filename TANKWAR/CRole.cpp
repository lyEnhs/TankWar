#include"StdAfx.h"
#include"CRole.h"
#include"CBulletManager.h"
#include"map.h"
#include"DrawTools.h"
#include"NpcManager.h"
#include"player.h"

extern Cplayer player ;
extern float g_fElapasedTime;
extern CBulletManager g_CBulletManager ;
extern Cmap g_map ;
extern CDrawTools g_cdrawtools;
extern CNpcManager    g_CNpcManager;

CRole::CRole():m_tx(0),m_ty(0),m_dir(0),m_NumMaxBullet(10),m_state(0),m_speed(100), m_NumCurBullet(0)
{
	//
}


CRole::~CRole()
{
	//
}

bool CRole::Fire()
{
	if(m_NumCurBullet < m_NumMaxBullet )
	{
		g_CBulletManager.CreateBullet(this);
		m_NumCurBullet++;
		return true ;
	}
	return false ;
}

void  CRole::move(DIRECTION dir)
{
	switch( dir )
	{
	  case D_UP: 
            m_dir = 0 ;
			m_ty -= g_fElapasedTime * m_speed;
			if( m_ty<=32 )
			{
				m_ty += g_fElapasedTime * m_speed;
			}
	  break;

      case D_DOWN:
			m_dir = 1 ;
			m_ty += g_fElapasedTime * m_speed;
			if( m_ty>=460)
			{
				m_ty -= g_fElapasedTime * m_speed;
			}
	  break;

	  case D_LEFT:
			m_dir = 2;
			m_tx -= g_fElapasedTime * m_speed;
			if(m_tx<=32)
			{
				m_tx += g_fElapasedTime * m_speed;
			}
	  break;

	  case D_RIGHT: 
			m_dir = 3 ;
			m_tx += g_fElapasedTime * m_speed;
			if( m_tx>=460)
			{
				m_tx -= g_fElapasedTime * m_speed;
			}
	  break;
	  }
	
}


bool CRole::judge()
{
		m_tank.left = m_tx;
		m_tank.top =  m_ty;
		m_tank.right = m_tx+20;
		m_tank.bottom = m_ty+20;

		RECT DestRect;
		for(int i= 0;i<16;i++)
		{	
			for(int j=0;j<16;j++)
			{
				int ID =0;
				IntersectRect(&DestRect,&g_map.m_map[j][i].rt,&m_tank);
				ID = g_map.m_map[j][i].ID;
				if( ID != 0&&ID != 3 && ID != 4 )
				{
					if(!IsRectEmpty(&DestRect))
					{				
						 return true;
					}
				}
			
			}
		}
	
		return false;
}


bool CRole::Judge()
{
	/////////player与NPC碰撞
	RECT ret ;
	std::list<CNpc*>::iterator itor = g_CNpcManager.ActiveList.begin();
	for( ; itor != g_CNpcManager.ActiveList.end(); itor++ )
	{
		IntersectRect(&ret,&(*itor)->m_tank,&player.m_tank);

		if( !IsRectEmpty(&ret) )
		{	
			m_tmpX = (*itor)->m_tx;
			m_tmpY = (*itor)->m_ty;

			if ( (*itor)->m_dir+player.m_dir==1 || (*itor)->m_dir+player.m_dir==5 )
			{
				g_CNpcManager.JudgeDir();
				
				int index = 0;
				do
				{
					index = rand()%4;				
				}
				while ( g_CNpcManager.m_tmpdir[index] == (*itor)->m_dir );

				(*itor)->m_dir =  g_CNpcManager.m_tmpdir[index];

				ZeroMemory(&g_CNpcManager.m_tmpdir,sizeof(g_CNpcManager.m_tmpdir));
				
			}
			return true ;
		}
				
	}

	return false ;
}


void CRole::collide(DIRECTION dir)
{
	switch(dir)
	{
		case D_UP: 
			if(CRole::judge())
			{
				m_ty =(int)m_ty/32*32+32 ;

			}
			if(CRole::Judge())
			 {
				m_ty =m_tmpY+20;
			 }
	  break;

      case D_DOWN:
			 if(CRole::judge())
			 {
				 m_ty = (int)m_ty/32*32+12;
			 }
			if(CRole::Judge())
			 {
				m_ty =m_tmpY-20;
			 }
			 
	  break;

	  case D_LEFT:
			 if(CRole::judge())
			 {
				 m_tx = (int)m_tx/32*32+32;
			 }
			 if(CRole::Judge())
			 {
				m_tx = m_tmpX+20;
			 }
			
			 
	  break;

	  case D_RIGHT: 
			 if(CRole::judge())
			 {
				 m_tx = (int)m_tx/32*32+12;
			 }
			 if(CRole::Judge())
			 {
				m_tx = m_tmpX-20;
			 }
			 
	  break;
	
	}
}


void CRole::Render()
{
	if(m_state==0)
	{
		switch( m_dir )//根据状态绘制不同方向的坦克
		{
	
		case 0:
			g_cdrawtools.Render("tank",m_tx,m_ty,0,0,20,20);
			break;
			
		case 1:
			g_cdrawtools.Render("tank",m_tx,m_ty,0,40,20,20 );
			break;
				 		
		case 2:
			g_cdrawtools.Render("tank",m_tx,m_ty,0,60,20,20 );
			break;

		case 3:
			g_cdrawtools.Render("tank",m_tx,m_ty,0,20,20,20);
			break;
		}	
	}
}