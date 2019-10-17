#include "SpawnZone.h"
#include"HandleSpawnEnemy.h"
#include"Camera.h"



void SpawnZone::Render()
{
	RenderBoundingBox();
}

void SpawnZone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (stopSpawn)
	{
		return;
	}
	if (!this->isSpawn)
	{
		float camx, camy;
		Camera::GetInstance()->GetCamera(camx, camy);
		if (CGameObject::AABB(this->x, this->y, this->x + this->width, this->y + this->height,
			camx, camy, camx + SCREEN_WIDTH, camy + SCREEN_HEIGHT))
		{
			if (spawn_start == 0)
			{
				spawn_start = GetTickCount();
			}
			if (this->x > camx + SCREEN_WIDTH)
			{
				nx = -1;
			}
			else if (this->x + this->width < camx)
			{
				nx = 1;
			}
		}
		else
		{
			this->spawn_start = 0;
			this->spawnPanther = false;
		}
		if (this->spawn_start != 0 && GetTickCount() - this->spawn_start > this->defaultTime)
		{
			this->isSpawn = true;

		}
	}
	else
	{
		if (this->enemyDef == EDPANTHER)
		{
			if (!this->spawnPanther)
			{
				HandleSpawnEnemy::GetInstance()->SpawnEnemy(this->enemyDef, this->num
					, this->defaultTime, this->x, this->y, this->nx, this->y);
				this->spawnPanther = true;
			}

		}
		else
		{
			HandleSpawnEnemy::GetInstance()->SpawnEnemy(this->enemyDef, this->num
				, this->defaultTime, this->x, this->y + this->height - 68, this->nx, this->y);
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
	if (this->enemyDef == EDPANTHER)
		isSpawn = false; // nếu là panther thì k spawn frame đầu 
	else
		isSpawn = true;
	spawn_start = 0;
	this->nx = -1;
}


SpawnZone::~SpawnZone()
{
}
