#pragma once
#include"Effects.h"
class HandleSpawnEffects
{
	Effects* effect;
	static HandleSpawnEffects * __instance;
public:
	void SpawnEffect(int effectDef,float x,float y);
	HandleSpawnEffects();
	static HandleSpawnEffects * GetInstance();
	~HandleSpawnEffects();
};

