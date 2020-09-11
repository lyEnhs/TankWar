#include"StdAfx.h"
#include"CBurstManager.h"
#include"DrawTools.h"
extern CDrawTools g_cdrawtools;

static int k = 0 ;
static int time = 0; 

CBurstManager::CBurstManager():m_curX(0),m_curY(0)
{
	//
}

CBurstManager::~CBurstManager()
{
	ClearUp();
}

void CBurstManager::ClearUp()
{
	std::list<Cburst*>::iterator itor = ActiveList.begin();
		   
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

	m_state = false ;
}

void CBurstManager::CreateBurst( CRole *pRole,bool state )
{

	m_state = state ;
	Cburst *pBurst = NULL ;
	 
	if( FreeList.size() > 0 )
	{
		std::list<Cburst* >::iterator itor = FreeList.end(); 
		itor-- ;
		pBurst = (*itor) ;
		FreeList.pop_back();
	}
	else
	{
		  pBurst= new Cburst(  );
	
	}

	pBurst->InitBurst( m_curX,m_curY,pRole );
	ActiveList.push_back( pBurst );
}
 
void CBurstManager::Render()
{
	 if( m_state )
	{
		if( k>8)
		{
			k=0;
			m_state = false ;
		}
		g_cdrawtools.Renderbomb("bomb",m_curX,m_curY,20*k,0,20,20);
		time++;
		if( time > 50 )
		{
			k++;
			time = 0 ;
		
		}
	 }	
}