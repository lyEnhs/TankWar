#pragma once
#include"CRole.h"
class Cplayer:public CRole
{
public:
	Cplayer();
	~Cplayer(){};

	void InitPlayer(float x ,float y,int dir,int state);//³õÊ¼»¯Íæ¼Ò


};
