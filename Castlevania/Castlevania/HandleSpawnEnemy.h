#pragma once
#include<d3dx9.h>
#include <utility> 
#include<string>
#include"Enemy.h"

class SceneManagement;
class HandleSpawnEnemy
{
	Enemy * enemy;
	bool stopSpawn=false;
	SceneManagement* scene;
	static HandleSpawnEnemy * __instance;
public:
	void SpawnEnemy(int enemydef, int num,DWORD respawntime,float x,float y, DIRECTION nx = DIRECTION::RIGHT,float oy=0);
	static HandleSpawnEnemy * GetInstance();
	void FreezeEnemy(bool flag);
	void Init(SceneManagement * scene);
	HandleSpawnEnemy();
	~HandleSpawnEnemy();
};

