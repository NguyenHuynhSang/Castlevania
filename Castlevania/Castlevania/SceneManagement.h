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
#include"ResourceManagement.h"
#include"Ground.h"
#include"NextScene.h"
#include"CTileMap.h"
#include"define.h"
#include"Torch.h"
#include"BoundMap.h"
#include"BlockingQueue.h"
#include"Effects.h"
#include"Item.h"
#include"Entry.h"
#include"MoneyBagTrigger.h"
#include"Panther.h"
#include"VampieBat.h"
#include"StairTrigger.h"
#include"SpawnZone.h"
#include"Candle.h"
#include"SubWeapon.h"
class SceneManagement
{
private:
	CGame *game;
	CSimon *simon;
	Whip* whip;
	Torch * torch;
	Ground *ground;
	Entry* entry;
	Panther *panther;
	NextScene * nextScene;
	BoundMap *bound;
	MoneyBagTrigger* trigger;
	StairTrigger *stair;
	CBrick * brick;
	Candle * candle;
	SpawnZone *spawnZone;
	ResourceManagement * resource;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> items;
	vector<LPGAMEOBJECT> effects;
	vector<LPGAMEOBJECT> enemies;
	vector<LPGAMEOBJECT> subWeapon;
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
	void JumpToState(int state);
	bool CheckNextScene() {
		return this->isNextScene;
	}
	void SpawnItem(Item* item) {
		this->items.push_back(item);
	}
	void SpawnEnemy(Enemy* enemy) {
		this->enemies.push_back(enemy);
	}
	void SpawnEffect(Effects* eff) {
		this->effects.push_back(eff);
	}
	void SpawnSubWeapon(SubWeapon* subW) {
		this->subWeapon.push_back(subW);
	}
	void LoadObjects(int currentScene);
	SceneManagement();
	~SceneManagement();
};

#endif