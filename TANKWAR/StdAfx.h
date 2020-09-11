
#pragma once

#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<TCHAR.h>
#include<list>
#include<vector>
using namespace std ;

enum DIRECTION
{
	D_UP,
	D_DOWN,
	D_LEFT,
	D_RIGHT,
	D_FIRE
};

#define D_NPCUP      0 ;
#define D_NPCDOWN    1 ;
#define D_NPCLEFT    2 ;
#define D_NPCRIGHT   3 ;