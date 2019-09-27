#include "HandleSpawnEnemy.h"

#include"Zombie.h"
#include"Fishman.h"
#include"SceneManagement.h"


HandleSpawnEnemy * HandleSpawnEnemy::__instance = NULL;



void HandleSpawnEnemy::SpawnEnemy(int enemyDef, int num, DWORD respawntime,float x,float y)
{
	switch (enemyDef)
	{
	case EDZOMBIE:
	{
		for (size_t i = 0; i < num; i++)
		{
			enemy = new Zombie();
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

	}
}

HandleSpawnEnemy *HandleSpawnEnemy::GetInstance()
{
	if (__instance == NULL) __instance = new HandleSpawnEnemy();
	return __instance;
}
HandleSpawnEnemy::HandleSpawnEnemy()
{
}


HandleSpawnEnemy::~HandleSpawnEnemy()
{
}
