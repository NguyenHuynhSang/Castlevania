#include "StopWatch.h"
#include"HandleSpawnEnemy.h"

StopWatch * StopWatch::__instance = NULL;

StopWatch *StopWatch::GetInstance()
{
	if (__instance == NULL) __instance = new StopWatch();
	return __instance;
}
void StopWatch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroyed)
	{
		return;
	}
	if (GetTickCount()-this->stopwatch_start>STOPWATCH_FREEZE_TIME)
	{
		HandleSpawnEnemy::GetInstance()->FreezeEnemy(false);
		this->isDestroyed = true;
	}
}


StopWatch::StopWatch()
{
	this->stopwatch_start = GetTickCount();
	HandleSpawnEnemy::GetInstance()->FreezeEnemy(true);
}


StopWatch::~StopWatch()
{
}
