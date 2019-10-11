#pragma once
#include"BBoxObjects.h"
class SpawnZone:public BBoxObject
{
private:
	int enemyDef;
	int num;
	DWORD spawn_start;
	int defaultTime;
	bool isSpawn = false;
	bool spawnPanther = false;
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	SpawnZone();
	SpawnZone(int enemyDef, int num, int time) ;
	~SpawnZone();
};

