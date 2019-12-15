#pragma once
#include<utility>
#include<Windows.h>
#include"Item.h"
class PlayScene;
class HandleSpawnItem
{
	static HandleSpawnItem * __instance;
	PlayScene* scene;
public:
	void SpawnItem(int itemDef,float x,float y,bool isHiding=true);
	void SpawnRandomItem(float x, float y, bool isHiding = true);
	HandleSpawnItem();
	void Init(PlayScene* scene) {
		this->scene = scene;
	}
	~HandleSpawnItem();
	static HandleSpawnItem * GetInstance();
};

