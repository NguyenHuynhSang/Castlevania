#include "HandleSpawnEnemy.h"
#include"SceneManagement.h"
#include"Zombie.h"
#include"Fishman.h"
#include"Fireball.h"
#include"VampieBat.h"
#include"Camera.h"

HandleSpawnEnemy * HandleSpawnEnemy::__instance = NULL;



void HandleSpawnEnemy::SpawnEnemy(int enemyDef, int num, DWORD respawntime, float x, float y, int nx, float oy)
{
	float cx, cy;
	float px, py;
	Camera::GetInstance()->GetCamera(cx, cy);
	scene->GetPlayerPosition(px, py);
	if (stopSpawn)
	{
		return;
	}
	switch (enemyDef)
	{
	case EDZOMBIE:
	{
		for (size_t i = 0; i < num; i++)
		{
			enemy = new Zombie();
			enemy->SetNx(nx);
			int rank = rand() % 2;
			if (rank == 1)
			{
				enemy->SetPositionInWorld(cx + SCREEN_WIDTH + i * 50 + 34, y);
				enemy->SetNx(-1);
			}
			else
			{
				enemy->SetPositionInWorld(cx - i * 50 - 34, y);
				enemy->SetNx(1);

			}
			scene->SpawnEnemy(enemy);

		}
		break;
	}
	case EDFISHMAN: {
		if (scene->CheckNumOfFishMan() >= 2)
		{
			return;
		}
		for (size_t i = 0; i < num; i++)
		{
			enemy = new Fishman();
			enemy->SetNx(1);
			enemy->SetPositionInWorld(x + i * 150 + 150, y);
			scene->SpawnEnemy(enemy);

		}
		break;
	}
	case EDFIREBALL: {
		enemy = new Fireball(nx);
		enemy->SetPositionInWorld(x, y);
		scene->SpawnEnemy(enemy);
		break;
	}
	case EDBAT: {
		enemy = new VampieBat(oy);
		for (size_t i = 0; i < num; i++)
		{
			int rank = rand() % 2;
			if (rank == 1)
			{
				enemy->SetPositionInWorld(cx + SCREEN_WIDTH + i * 50 + 34, y);
				enemy->SetNx(-1);
			}
			else
			{
				enemy->SetPositionInWorld(cx - i * 50 - 34, y);
				enemy->SetNx(1);

			}
		}
		scene->SpawnEnemy(enemy);
		break;
	}
	case EDPANTHER: {
		enemy = new Panther();
		enemy->SetPositionInWorld(x,y);
		if (x>px)
			enemy->SetNx(-1); 
		else
			enemy->SetNx(1); 
		
		DebugOut(L"Spawn Panther \n");
		scene->SpawnEnemy(enemy);
		break;
	}
	}
}

HandleSpawnEnemy *HandleSpawnEnemy::GetInstance()
{
	if (__instance == NULL) __instance = new HandleSpawnEnemy();
	return __instance;
}
void HandleSpawnEnemy::FreezeEnemy(bool flag)
{
	this->stopSpawn = flag;
	scene->FreezeEnemy(this->stopSpawn);
}
void HandleSpawnEnemy::Init(SceneManagement * scene)
{
	this->scene = scene;
}
HandleSpawnEnemy::HandleSpawnEnemy()
{
	
}


HandleSpawnEnemy::~HandleSpawnEnemy()
{
	delete scene;
}
