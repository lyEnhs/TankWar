#pragma once
#include"burst.h"
#include"CRole.h"
class CBurstManager
{
public:
	CBurstManager();
	~CBurstManager();

	void CreateBurst( CRole *pRole ,bool state );//创建爆炸效果
	void ClearUp();//清空链表
	void Render();//爆炸效果渲染
 
	std::list<Cburst*> ActiveList ;
	std::list<Cburst*> FreeList ;

	float m_curX;//爆炸当前X坐标
	float m_curY;//爆炸当前Y坐标
	bool  m_state;//爆炸存活状态
	 
};