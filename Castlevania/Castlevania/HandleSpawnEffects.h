#pragma once
#include"Effects.h"
class SceneManagement;
class HandleSpawnEffects
{
	
	static HandleSpawnEffects * __instance;
	SceneManagement* scene;
public:
	void SpawnEffect(int effectDef,float x,float y);
	HandleSpawnEffects();
	void Init(SceneManagement* scene);
	static HandleSpawnEffects * GetInstance();
	~HandleSpawnEffects();
};

