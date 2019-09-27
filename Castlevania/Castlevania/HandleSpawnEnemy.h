#pragma once
#include<d3dx9.h>
#include <utility> 
#include<string>
class HandleSpawnEnemy
{
	static HandleSpawnEnemy * __instance;
public:
	void SpawnEnemy(int enemydef, int num,DWORD respawntime,float x,float y);
	static HandleSpawnEnemy * GetInstance();
	HandleSpawnEnemy();
	~HandleSpawnEnemy();
};

