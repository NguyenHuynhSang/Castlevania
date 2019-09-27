#include "HandleSpawnEffects.h"
#include"SceneManagement.h"
#include"Flame.h"
#include"DebrisBrick.h"
#include"Bubble.h"


HandleSpawnEffects * HandleSpawnEffects::__instance = NULL;


void HandleSpawnEffects::SpawnEffect(int effectDef, float x, float y)
{

	switch (effectDef)
	{
		case EFD_FLAME : 
		{
			effect = new Flame();
			effect->SetPositionInWorld(x , y);
			SceneManagement::GetInstance()->SpawnEffect(effect);
			break;
		}
		case EFD_DEBRIS:
		{
			for (size_t i = 0; i < 4; i++)
			{
				//rank tu -0.1->0.2
				float vx = (float)(-100 + rand() % 200) / 1000;
				float vy = (float)(-100 + rand() % 200) / 1000;
				effect = new DebrisBrick(vx, vy);
				effect->SetPositionInWorld(x, y);
				SceneManagement::GetInstance()->SpawnEffect(effect);
			}
			break;
		}
		case EFD_BUBBLE:
		{
			for (size_t i = 0; i < 4; i++)
			{
				//rank tu -0.1->0.2
				float vx = (float)(-100 + rand() % 200) / 1000;
				float vy = (float)(-100 + rand() % 200) / 1000;
				effect = new Bubble(vx, vy);
				effect->SetPositionInWorld(x,y);
				SceneManagement::GetInstance()->SpawnEffect(effect);
			}
			break;
		}
	}
	
}

HandleSpawnEffects::HandleSpawnEffects()
{
}

HandleSpawnEffects * HandleSpawnEffects::GetInstance()
{
	if (__instance == NULL) __instance = new HandleSpawnEffects();
	return __instance;
}


HandleSpawnEffects::~HandleSpawnEffects()
{
	delete effect;
}
