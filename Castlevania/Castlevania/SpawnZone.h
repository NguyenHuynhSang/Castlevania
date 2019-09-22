#pragma once
#include"BBoxObjects.h"
class SpawnZone:public BBoxObject
{
private:
	int enemyDef;
	int num;
	DWORD spawn_start;
	int defaultTime;
	bool CheckInCam();
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	SpawnZone();
	SpawnZone(int enemyDef, int num, int time) :enemyDef(enemyDef), num(num), defaultTime(time) {};
	~SpawnZone();
};

