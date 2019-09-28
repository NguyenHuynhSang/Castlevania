#pragma once
#include<d3dx9.h>
#include <utility> 
#include<string>
#include"Enemy.h"
class HandleSpawnEnemy
{
	Enemy * enemy;
	static HandleSpawnEnemy * __instance;
public:
	void SpawnEnemy(int enemydef, int num,DWORD respawntime,float x,float y,int nx=1);
	static HandleSpawnEnemy * GetInstance();
	HandleSpawnEnemy();
	~HandleSpawnEnemy();
};

