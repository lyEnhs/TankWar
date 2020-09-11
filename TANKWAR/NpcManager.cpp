#include"StdAfx.h"
#include"NpcManager.h"
#include"map.h"
extern Cmap g_map ;

CNpcManager::CNpcManager()
{
	//
}

CNpcManager::~CNpcManager()
{
	ClearUp();
}


void CNpcManager::ClearUp()
{
	std::list<CNpc*>::iterator itor = ActiveList.begin();
		   
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


void CNpcManager::CreatNpc(float x, float y, int dir)
{
	CNpc *npc = NULL ;
	 
	if( FreeList.size() > 0 )
	{
		std::list<CNpc* >::iterator itor = FreeList.end(); 
		itor-- ;
		npc = (*itor) ;
		FreeList.pop_back();
	}
	else
	{
		  npc= new CNpc();
	
	}
	npc->InitNpc(x,y,dir);
	ActiveList.push_back(npc);

}


void CNpcManager::JudgeDir()
{
	std::list<CNpc*>::iterator itor = ActiveList.begin();
		   
	for( ; itor != ActiveList.end() ; itor++)
	{
		int i =(int)((*itor)->m_ty/32);
		int j =(int)((*itor)->m_tx/32);
		 
		if(g_map.m_map[i-1][j].ID==0&&i>1)
		 {
			m_tmpdir[0] = 0;
		 }

		 if(g_map.m_map[i+1][j].ID==0)
		 {
			m_tmpdir[1] = 1;
		 }

		 if(g_map.m_map[i][j-1].ID==0&&j>1)
		 {
			m_tmpdir[2] = 2;
		 }

		 if(g_map.m_map[i][j+1].ID==0)
		 {
			m_tmpdir[3] = 3;
		 }

	}
}


void CNpcManager::Update()
{
	std::list<CNpc*>::iterator tmp,itor = ActiveList.begin();

	for( ;itor != ActiveList.end() ; )
	{
		(*itor)->move();
		tmp  = itor ;
		itor++ ;
		if((*tmp)->m_state==1)
		{
			FreeList.push_back(*tmp);
			ActiveList.erase(tmp);
		}
	}
}


void CNpcManager::Collide()
{
	std::list<CNpc*>::iterator itor = ActiveList.begin();
		   
	for( ; itor != ActiveList.end() ; itor++)
	{
		(*itor)->collide(); 
	}


}


void CNpcManager::Render()
{
	std::list<CNpc*>::iterator itor = ActiveList.begin();
		   
	for( ; itor != ActiveList.end() ; itor++)
	{
		(*itor)->Render(); 
	}
}