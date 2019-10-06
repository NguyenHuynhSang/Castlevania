#include "HandleSpawnEnemy.h"
#include"SceneManagement.h"
#include"Zombie.h"
#include"Fishman.h"
#include"Fireball.h"
#include"VampieBat.h"



HandleSpawnEnemy * HandleSpawnEnemy::__instance = NULL;



void HandleSpawnEnemy::SpawnEnemy(int enemyDef, int num, DWORD respawntime,float x,float y,int nx,float oy)
{
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
			enemy->SetPositionInWorld(x + i * 50 + 34, y);
			SceneManagement::GetInstance()->SpawnEnemy(enemy);

		}
		break;
	}
	case EDFISHMAN: {
		if (SceneManagement::GetInstance()->CheckNumOfFishMan()>=2)
		{
			return;
		}
		for (size_t i = 0; i < num; i++)
		{
			enemy = new Fishman();
			enemy->SetPositionInWorld(x + i * 150 + 150, y);
			SceneManagement::GetInstance()->SpawnEnemy(enemy);

		}
		break;
	}
	case EDFIREBALL: {
		enemy = new Fireball(nx);
		enemy->SetPositionInWorld(x , y);
		SceneManagement::GetInstance()->SpawnEnemy(enemy);
		break;
	}
	case EDBAT: {
		enemy = new VampieBat(oy);
		enemy->SetPositionInWorld(x, y);
		enemy->SetNx(nx);
		SceneManagement::GetInstance()->SpawnEnemy(enemy);
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
	SceneManagement::GetInstance()->FreezeEnemy(this->stopSpawn);
}
HandleSpawnEnemy::HandleSpawnEnemy()
{
}


HandleSpawnEnemy::~HandleSpawnEnemy()
{
}
