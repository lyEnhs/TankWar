#pragma once
#include"CRole.h"

class Cbullet
{
public:
	 Cbullet();
	~Cbullet();

	void InitBullet( int dir ,float x, float y,CRole *powner );//子弹初始化
	void Update();//子弹移动
	void Render();//子弹渲染
	bool Judge();//子弹碰撞检测

	int   m_Zdir;//子弹方向
	int   m_state;//子弹状态
	float m_speed;//子弹飞行速度
	float m_x;//子弹x位置
	float m_y;//子弹y位置
	RECT  rt;//子弹矩形
	CRole *powner;//子弹拥有者

};