#include"StdAfx.h"
#include"burst.h"
#include"player.h"

Cburst::Cburst( )
{
	//
}

Cburst::~Cburst()
{
	//	
}

void Cburst::InitBurst( float x, float y,CRole *p )
{
	m_curX = x ;
	m_curY = y ;
	powner = p ;

}

