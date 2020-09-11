#pragma once
#include"bullet.h"
#include"CRole.h"
class CBulletManager
{
public:
	CBulletManager();
	~CBulletManager();

	void CreateBullet( CRole *pRole );//创建子弹
	void Update();//子弹管理器的移动
	void Render();//子弹管理器的渲染
	void bombeffect();//爆炸效果
	void ClearUp();//清空链表

	std::list<Cbullet*> ActiveList ;
	std::list<Cbullet*> FreeList ;

    int m_Maxboard ;//边界最大值
    int m_Minboard ;//边界最小值
    float m_curX;//子弹当前X坐标
    float m_curY;//子弹当前Y坐标
	 
};