#pragma once
#include<utility>
#include<Windows.h>
#include"Item.h"
class HandleSpawnItem
{
	static HandleSpawnItem * __instance;
public:
	void SpawnItem(int itemDef,float x,float y,bool isHiding=true);
	void SpawnRandomItem(float x, float y, bool isHiding = true);
	HandleSpawnItem();
	~HandleSpawnItem();
	static HandleSpawnItem * GetInstance();
};

