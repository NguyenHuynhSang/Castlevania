#include "SpawnZone.h"
#include"Enemy.h"
#include"Zombie.h"
#include"SceneManagement.h"



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
			this->isSpawn = true;

		}
	}
	else
	{
		DebugOut(L"Spawn \n");
		switch (this->enemyDef)
		{
		case EDZOMBIE:
		{
			for (size_t i = 0; i < this->num; i++)
			{
				Enemy * enemy = new Zombie();
				enemy->SetPositionInWorld(this->x + i*50+34, this->y);
				SceneManagement::GetInstance()->SpawnEnemy(enemy);
			}
		}

		}
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
