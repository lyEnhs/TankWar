#include"StdAfx.h"
#include"NPC.h"
#include"CBulletManager.h"
#include"DrawTools.h"

extern CBulletManager g_CBulletManager;
extern CDrawTools g_cdrawtools;
extern float g_fElapasedTime;
static int Curtime = 0;


CNpc::CNpc():m_nspeed(50)
{ 
	//	 
}

void CNpc::InitNpc(float x,float y,int dir)
{
	m_tx = x ;
	m_ty = y ;
	m_dir = dir ;
}

void CNpc::move()
{	
	
	Curtime++;
	if(Curtime>1000)
	{
		this->Fire();
		Curtime=0;
	}

	switch(m_dir)
	{	
		case 0:

			m_ty -= g_fElapasedTime * m_nspeed;
			if( m_ty < 32 )
			{
				m_dir = rand()%4;
				
			}
			
			break;
			
		case 1:
			  m_ty += g_fElapasedTime * m_nspeed;
			  if( m_ty > 460 )
			{
				m_dir = rand()%4;
			}
			break;
				 		
		case 2:
			 m_tx -= g_fElapasedTime * m_nspeed;
			 if( m_tx < 32 )
			{
				m_dir = rand()%4;
			}
			break;

		case 3:
			 m_tx += g_fElapasedTime * m_nspeed;
			 if( m_tx > 460)
			{
				m_dir = rand()%4;
			}
			break;
	}
}

void CNpc::collide( )
{
	switch( m_dir )
	{
		case 0:
			if(CNpc::judge())
			{
				m_ty =(int)m_ty/32*32+32 ;
				m_dir = rand()%4;
			}
			break;

		case 1:
			if(CNpc::judge())
			{
				m_ty =(int)m_ty/32*32+12 ;
				m_dir = rand()%4;
			}
			break;

		case 2:
			 if(CNpc::judge())
			 {
				 m_tx = (int)m_tx/32*32+32;
				 m_dir = rand()%4;
			 }
			break;

		case 3:
			 if(CNpc::judge())
			 {
				 m_tx = (int)m_tx/32*32+12;
				 m_dir = rand()%4;
			 }
			break;
	}

}


 void CNpc::Render()
 {
	switch( m_dir )//根据状态绘制不同方向的坦克
	{
	
		case 0:
			g_cdrawtools.Render("NPC",m_tx,m_ty,0,0,20,20);
			break;
			
		case 1:
			g_cdrawtools.Render("NPC",m_tx,m_ty,40,0,20,20 );
			break;
				 		
		case 2:
			g_cdrawtools.Render("NPC",m_tx,m_ty,20,0,20,20 );
			break;

		case 3:
			g_cdrawtools.Render("NPC",m_tx,m_ty,60,0,20,20);
			break;
		default:
			
			break;
	}
 
 }