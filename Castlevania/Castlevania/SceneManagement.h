﻿#pragma once
#ifndef _SCENE_CLASS
#define _SCENE_CLASS
#include<Windows.h>
#include"define.h"
#include "debug.h"
#include "Game.h"
#include"Camera.h"
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
#include"Water.h"
#include"Door.h"
#include"Hud.h"
#include"Grid.h"
#include"InputController.h"
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
	Water* water;
	Door* door;
	Hud* hud;
	Grid * grid;
	std::vector<Unit*> listUnit;
	RECT sceneBox;
	ResourceManagement * resource;
	vector<LPGAMEOBJECT> objects;

	// luôn update
	vector<LPGAMEOBJECT> groundObjects;
	vector<LPGAMEOBJECT> spawnObjects;

	// list các loại object dùng để quản lý và truy xuất nhanh
	vector<LPGAMEOBJECT> items;
	vector<LPGAMEOBJECT> effects;
	vector<LPGAMEOBJECT> enemies;
	vector<LPGAMEOBJECT> subWeapon;


	std::queue<Enemy*> qEnemy;
	std::queue<Item*> qItem;
	std::queue<SubWeapon *> qSubWeapon;


	CTileMap* cmap;
	bool isNextScene;
	bool isAutoScrollCam = false;		
	void LoadResource();
	int currentScene;
	void HandleSpawningItem();
	void CamUpdate(DWORD dt);
	void GetListUnitFromGrid();
	void UpdateGrid();
public:

	void OnCreate();
	int CheckNumOfFishMan();
	CSimon* GetSimon() {
		return this->simon;
	};
	int GetCurrentScene() { return this->currentScene; };
	void Update(DWORD dt);
	void Render();
	void SceneUpdate();

	void GetPlayerPosition(float &x, float &y) {
		simon->GetPosition(x, y);
	}
	void ResetCam() {
		Camera::GetInstance()->SetCamera(0, 0);
		
	}
	
	void GetCoObjects(LPGAMEOBJECT obj, vector<LPGAMEOBJECT>& coObjects);
	void FreezeEnemy(bool flag);
	void KillAllEnemy();
	void LoadScene();
	void GoNextScene();
	void JumpToState(int state);
	bool CheckNextScene() {
		return this->isNextScene;
	}
	void SpawnItem(Item* item) {
	
		this->items.push_back(item);
		qItem.push(item);
		
	}
	void SpawnEnemy(Enemy* enemy) {
		this->enemies.push_back(enemy);
		qEnemy.push(enemy);
	}
	void SpawnEffect(Effects* eff) {
		this->effects.push_back(eff);
	}
	void SpawnSubWeapon(SubWeapon* subW) {
		this->subWeapon.push_back(subW);
		qSubWeapon.push(subW);
	}
	void LoadObjects(int currentScene);
	SceneManagement();
	~SceneManagement();
};

#endif