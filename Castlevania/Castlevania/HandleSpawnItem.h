#pragma once
#include<utility>
#include<Windows.h>
#include"Item.h"
class SceneManager;
class HandleSpawnItem
{
	static HandleSpawnItem * __instance;
	SceneManager* scene;
public:
	void SpawnItem(int itemDef,float x,float y,bool isHiding=true);
	void SpawnRandomItem(float x, float y, bool isHiding = true);
	HandleSpawnItem();
	void Init(SceneManager* scene) {
		this->scene = scene;
	}
	~HandleSpawnItem();
	static HandleSpawnItem * GetInstance();
};

