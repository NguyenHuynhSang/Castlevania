#pragma once
#ifndef _SCENE_CLASS
#define _SCENE_CLASS
#include<Windows.h>
#include"define.h"
#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Simon.h"
#include "Brick.h"
#include "Ghoul.h"
#include"ResourceManagement.h"
#include "Whip.h"
#include"Ground.h"
#include"NextScene.h"
#include"CTileMap.h"
#include"define.h"
#include"Torch.h"
#include"BoundMap.h"
#include"Zombie.h"
#include"BlockingQueue.h"
#include"Effects.h"
#include"Item.h"
#include"Entry.h"
#include"MoneyBagTrigger.h"
class SceneManagement
{
private:
	CGame *game;
	CSimon *simon;
	Ghoul *goomba;
	Whip* whip;
	Torch * torch;
	Ground *ground;
	Entry* entry;
	NextScene * nextScene;
	BoundMap *bound;
	Zombie* zombie;
	MoneyBagTrigger* trigger;
	ResourceManagement * resource;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> items;
	vector<LPGAMEOBJECT> effects;
	CTileMap* cmap;
	static SceneManagement * __instance;
	bool isNextScene;
	void LoadResource();
	int currentScene;
	void HandleSpawningItem();
	
public:

	static SceneManagement * GetInstance();
	void OnCreate();
	CSimon* GetSimon() {
		return this->simon;
	};
	int GetCurrentScene() { return this->currentScene; };
	void Update(DWORD dt);
	void Render();
	void SceneUpdate();
	void ResetCam() {
		CGame::GetInstance()->SetCamPos(0, 0);
	}
	void LoadScene();
	void GoNextScene();
	bool CheckNextScene() {
		return this->isNextScene;
	}
	void SpawnItem(Item* item) {
		this->items.push_back(item);
	}
	void SpawnEffect(Effects* eff) {
		this->effects.push_back(eff);
	}
	void LoadObjects(int currentScene);
	SceneManagement();
	~SceneManagement();
};

#endif