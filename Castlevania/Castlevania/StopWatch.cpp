#include "StopWatch.h"
#include"HandleSpawnEnemy.h"

void StopWatch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroyed)
	{
		return;
	}
	if (this->stopwatch_start!=0)
	{
		HandleSpawnEnemy::GetInstance()->FreezeEnemy(true);
	}
	if (GetTickCount()-this->stopwatch_start>STOPWATCH_FREEZE_TIME)
	{
		HandleSpawnEnemy::GetInstance()->FreezeEnemy(false);
		this->stopwatch_start = 0;
		this->DestroyImmediate();
	}
}


StopWatch::StopWatch() :SubWeapon()
{
	this->stopwatch_start = GetTickCount();
	this->damage = 0;
	this->heartCostPerUse = 5;
}


StopWatch::~StopWatch()
{
}
