#pragma once
#include"Effects.h"
class PlayScene;
class HandleSpawnEffects
{
	
	static HandleSpawnEffects * __instance;
	PlayScene* scene;
public:
	void SpawnEffect(int effectDef,float x,float y);
	HandleSpawnEffects();
	void Init(PlayScene* scene);
	static HandleSpawnEffects * GetInstance();
	~HandleSpawnEffects();
};

