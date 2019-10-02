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
	if (this->stopwatch_start!=0)
	{
		HandleSpawnEnemy::GetInstance()->FreezeEnemy(true);
	}
	if (GetTickCount()-this->stopwatch_start>STOPWATCH_FREEZE_TIME)
	{
		HandleSpawnEnemy::GetInstance()->FreezeEnemy(false);
		this->stopwatch_start = 0;
		
	}
}


StopWatch::StopWatch()
{
	this->stopwatch_start = GetTickCount();
}


StopWatch::~StopWatch()
{
}
