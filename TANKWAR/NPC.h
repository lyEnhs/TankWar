#pragma once
#include"CRole.h"

class CNpc:public CRole
{

public:
	CNpc();
	~CNpc(){};
	void InitNpc(float x,float y,int dir);//初始化NPC
	void move();//NPC的移动方法
	void collide();//NPC的碰撞检测
	void Render();//渲染

	float m_nspeed;//NPC的移动速度

};