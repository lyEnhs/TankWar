#pragma once
#include"NPC.h"
class CNpcManager
{
public:
	CNpcManager();
	~CNpcManager();

	void CreatNpc(float x,float y,int dir);//创建NPC
	void JudgeDir();//判断NPC有几条路可走
	void Update();//NPC的移动
	void Collide();//NPC的碰撞
	void Render();//NPC的渲染
	void ClearUp();//清空管理器

	std::list<CNpc*> ActiveList ;
	std::list<CNpc*> FreeList ;

	int m_tmpdir[4];//记录可走方向的数组
};