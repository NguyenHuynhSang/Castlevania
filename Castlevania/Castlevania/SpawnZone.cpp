#include "SpawnZone.h"
#include"HandleSpawnEnemy.h"
#include"Camera.h"

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
	DebugOut(L"nx=%d \n",this->nx);
	if (!this->isSpawn)
	{
		float camx, camy;
		Camera::GetInstance()->GetCamera(camx, camy);
		if (CGameObject::AABB(this->x,this->y,this->x+this->width,this->y+this->height,
							camx,camy,camx+SCREEN_WIDTH,camy+SCREEN_HEIGHT))
		{
			DebugOut(L"INCAM \n");
			this->spawn_start = 0;
		}
		else
		{
			if (spawn_start==0)
			{
				spawn_start = GetTickCount();
			}
			if (this->x>camx+ SCREEN_WIDTH)
			{
				nx = -1;
			}
			else if (this->x+this->width<camx)
			{
				nx = 1;
			}
		}
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
			, this->defaultTime, this->x, this->y,this->nx,this->y);
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
	this->nx = -1;
}


SpawnZone::~SpawnZone()
{
}
