#pragma once
#include<d3dx9.h>
#include <utility> 
#include<string>
#include"Enemy.h"


class HandleSpawnEnemy
{
	Enemy * enemy;
	bool stopSpawn=false;
	static HandleSpawnEnemy * __instance;
public:
	void SpawnEnemy(int enemydef, int num,DWORD respawntime,float x,float y,int nx=1,float oy=0);
	static HandleSpawnEnemy * GetInstance();
	void FreezeEnemy(bool flag);
	HandleSpawnEnemy();
	~HandleSpawnEnemy();
};

