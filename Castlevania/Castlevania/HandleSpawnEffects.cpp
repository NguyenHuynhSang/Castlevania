#include "HandleSpawnEffects.h"
#include"SceneManager.h"
#include"Flame.h"
#include"DebrisBrick.h"
#include"Bubble.h"
#include"ScoreText.h"
#include"Spark.h"
#include"BossDead.h"
HandleSpawnEffects * HandleSpawnEffects::__instance = NULL;


void HandleSpawnEffects::SpawnEffect(int effectDef, float x, float y)
{
	Effects* effect;
	switch (effectDef)
	{
		case EFD_FLAME : 
		{
			effect = new Flame();
			effect->SetPositionInWorld(x , y);
			scene->SpawnEffect(effect);
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
				scene->SpawnEffect(effect);
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
				scene->SpawnEffect(effect);
			}
			break;
		}
		case EFD_ST100: {
			effect = new ScoreText(SCORETEXT_STATE_100);
			effect->SetPositionInWorld(x, y);
			scene->SpawnEffect(effect);
			break;
		}
		case EFD_ST400: {
			effect = new ScoreText(SCORETEXT_STATE_400);
			effect->SetPositionInWorld(x, y);
			scene->SpawnEffect(effect);
			break;
		}
		case EFD_ST700: {
			effect = new ScoreText(SCORETEXT_STATE_700);
			effect->SetPositionInWorld(x, y);
			scene->SpawnEffect(effect);
			break;
		}
		case EFD_ST1000: {
			effect = new ScoreText(SCORETEXT_STATE_1000);
			effect->SetPositionInWorld(x, y);
			scene->SpawnEffect(effect);
			break;
		}
		case EFD_SPARK: {
			effect = new Spark();
			effect->SetPositionInWorld(x, y);
			scene->SpawnEffect(effect);
			break;
		}
		case EFD_BOSSDEAD: {
			effect = new BossDead();
			effect->SetPositionInWorld(x, y);
			scene->SpawnEffect(effect);
			break;
		}
					  
	}
	
}

HandleSpawnEffects::HandleSpawnEffects()
{
}

void HandleSpawnEffects::Init(SceneManager* scene)
{
	this->scene = scene;
}

HandleSpawnEffects * HandleSpawnEffects::GetInstance()
{
	if (__instance == NULL) __instance = new HandleSpawnEffects();
	return __instance;
}


HandleSpawnEffects::~HandleSpawnEffects()
{
	delete scene;
}
