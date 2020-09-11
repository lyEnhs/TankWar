#pragma once
#include"CRole.h"

class Cburst
{
public:
	 Cburst();
	~Cburst();

	void InitBurst( float x, float y,CRole *p );//爆炸效果初始化

	float m_curX;//爆炸x位置
	float m_curY;//爆炸y位置
	CRole *powner;//爆炸拥有者

};