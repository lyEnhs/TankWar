#pragma once
class CRole
{
public:
	CRole();
	~CRole();

	virtual bool Fire() ;//角色开火的方法
	void move( DIRECTION dir );//角色移动的方法
	bool judge();//判断角色与地图碰撞
	bool Judge();///判断NPC与player碰撞
	void collide( DIRECTION dir );
	void Render();//渲染方法

	float m_tx ;//角色X坐标
	float m_ty ;//角色Y坐标
	float m_tmpX;//临时X坐标
	float m_tmpY;//临时Y坐标

	int  m_dir ;//角色方向
	int  m_state;//角色存活状态
	int  m_speed ;//角色移动速度

	int m_NumMaxBullet ;//子弹最大个数
	int m_NumCurBullet ;//子弹当前个数

	RECT m_tank;//角色矩形
};