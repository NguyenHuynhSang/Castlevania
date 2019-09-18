#pragma once
#include<d3dx9.h>
#include <utility> 
#include<string>
class HanleSpawnEnemy
{
	DWORD start_spawncounter;
	std::pair<std::string, D3DXVECTOR2> enemyToSpawn;
public:
	void StartSpawnCounter();
	HanleSpawnEnemy();
	~HanleSpawnEnemy();
};

