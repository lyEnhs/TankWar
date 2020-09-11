#include"StdAfx.h"
#include"CBulletManager.h"
#include"CBurstManager.h"
#include"bullet.h"
#include"player.h"
#include"DrawTools.h"


extern CDrawTools g_cdrawtools;
extern CBurstManager  g_CBurstManager;

static int k = 0 ;
static int time = 0; 

CBulletManager::CBulletManager():m_Maxboard(475),m_Minboard(32),m_curX(0),m_curY(0)
{
	//
}

CBulletManager::~CBulletManager()
{
	 ClearUp();
}

void CBulletManager::ClearUp()
{
	std::list<Cbullet*>::iterator itor = ActiveList.begin();
		   
	for( ; itor != ActiveList.end() ; itor++)
	{
		delete *itor ;
	}
	ActiveList.clear();
	itor = FreeList.begin();
	for( ;itor != FreeList.end(); itor++ )
	{
		delete *itor ;
	}
	FreeList.clear();
}

void CBulletManager::CreateBullet( CRole *pRole )
{

	Cbullet *pBullet = NULL ;
	 
	if( FreeList.size() > 0 )
	{
		std::list<Cbullet* >::iterator itor = FreeList.end(); 
		itor-- ;
		pBullet = (*itor) ;
		FreeList.pop_back();
	}
	else
	{
		  pBullet= new Cbullet( );
	
	}
	pBullet->InitBullet( pRole->m_dir,pRole->m_tx+6,pRole->m_ty+6,pRole );
	ActiveList.push_back( pBullet );
}

void CBulletManager::Update()
{
	std::list<Cbullet *>::iterator tmp,itor = ActiveList.begin();

	for( ;itor != ActiveList.end() ; )
	{
		(*itor)->Update();
		////×Óµ¯³ö½ç¼ì²â
		if( (*itor)->m_x < m_Minboard || (*itor)->m_x > m_Maxboard || (*itor)->m_y < m_Minboard || (*itor)->m_y > m_Maxboard )
		{
			tmp  = itor ;
			itor++ ;
			if( (*tmp)->powner )
			{
				(*tmp)->powner->m_NumCurBullet--;
			}
			FreeList.push_back(*tmp);
			ActiveList.erase(tmp);
		
		}
		else//Åö×²¼ì²â
		{
			if((*itor)->Judge())
			{
				tmp = itor ;
				if( (*tmp)->m_Zdir == 0 )
				{
					g_CBurstManager.m_curX = (*tmp)->m_x-5 ;
					g_CBurstManager.m_curY = (*tmp)->m_y-15 ;
				}
				else if((*tmp)->m_Zdir == 1 )
				{
					g_CBurstManager.m_curX = (*tmp)->m_x ;
					g_CBurstManager.m_curY = (*tmp)->m_y+15 ;
				}
				else if((*tmp)->m_Zdir == 2 )
				{
					g_CBurstManager.m_curX = (*tmp)->m_x-15 ;
					g_CBurstManager.m_curY = (*tmp)->m_y-5;
				}
				else if((*tmp)->m_Zdir == 3 )
				{
					g_CBurstManager.m_curX = (*tmp)->m_x+15 ;
					g_CBurstManager.m_curY = (*tmp)->m_y-5 ;
				}
				g_CBurstManager.CreateBurst((*tmp)->powner ,true);
				itor++;
				if((*tmp)->powner)
				{
					(*tmp)->powner->m_NumCurBullet--;
				}
				FreeList.push_back(*tmp);
				ActiveList.erase(tmp);
			}
			else
			{
			 itor++;
			}
			 
		}
		
	}
}

void CBulletManager::bombeffect()
{
	std::list< Cbullet *>::iterator itor = ActiveList.begin();
		for( ; itor != ActiveList.end(); itor++)
		{
			if((*itor)->m_state ==1 )
			{
				if( k>8)
				{
					k=0;
					(*itor)->m_state = 0 ;
				}
				g_cdrawtools.Renderbomb("bomb",m_curX,m_curY,20*k,0,20,20);
				time++;
				if( time > 100)
				{
					k++;
					time = 0 ;
				
				}
			}
		}
}

void CBulletManager::Render()
{
	
	std::list<Cbullet*>::iterator itor = ActiveList.begin();
		   
	
	for( ; itor != ActiveList.end() ; itor++)
	{
		
		(*itor)->Render(); 
	}

}