#include"StdAfx.h"
#include"player.h"

Cplayer::Cplayer() 
{
	m_tx = 100;
	m_ty = 460;
	m_dir = 0 ;
	m_state = 0 ;
}

void Cplayer::InitPlayer(float x ,float y,int dir,int state)
{
	m_tx = x ;
	m_ty = y ;
	m_dir = dir ;
	m_state = state ;
	 
}
	
	 