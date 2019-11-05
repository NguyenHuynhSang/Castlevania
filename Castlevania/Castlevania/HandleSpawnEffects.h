#pragma once
#include"Effects.h"
class SceneManager;
class HandleSpawnEffects
{
	
	static HandleSpawnEffects * __instance;
	SceneManager* scene;
public:
	void SpawnEffect(int effectDef,float x,float y);
	HandleSpawnEffects();
	void Init(SceneManager* scene);
	static HandleSpawnEffects * GetInstance();
	~HandleSpawnEffects();
};

