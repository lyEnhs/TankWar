#pragma once

class CScore
{
public:
	CScore();
	~CScore();

	void Render();//渲染
	
	int m_score ;//成绩
	int m_Life ;//玩家生命
	int m_numNPC;//NPC个数
	int m_Level;//关卡
	char str[50];//保存字符串
};