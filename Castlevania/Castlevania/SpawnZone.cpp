#include "SpawnZone.h"
#include"HandleSpawnEnemy.h"


bool SpawnZone::CheckInCam()
{
	return false;
}

void SpawnZone::Render()
{
	RenderBoundingBox();
}

void SpawnZone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!this->isSpawn)
	{
		if (this->spawn_start!=0 && GetTickCount()- this->spawn_start>this->defaultTime)
		{
			DebugOut(L"true \n");
			this->isSpawn = true;

		}
	}
	else
	{
		DebugOut(L"Spawn \n");
		HandleSpawnEnemy::GetInstance()->SpawnEnemy(this->enemyDef, this->num
			, this->defaultTime, this->x, this->y);
		this->isSpawn = false;
		spawn_start = GetTickCount();
	}

}

SpawnZone::SpawnZone()
{
}

SpawnZone::SpawnZone(int enemyDef, int num, int time)
{
	this->enemyDef = enemyDef;
	if (num == -1)
	{
		this->num = 0;
	}
	else
	{
		this->num = num;
	}
	this->defaultTime = time;
	isSpawn = true;
	spawn_start = 0;
}


SpawnZone::~SpawnZone()
{
}
