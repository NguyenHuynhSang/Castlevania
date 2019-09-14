#pragma once
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
#include"CTileMap.h"
#include"define.h"
#include"Torch.h"
#include"BoundMap.h"
#include"Heart.h"
#include"Zombie.h"
#include"BlockingQueue.h"
class SceneManagement
{
private:
	CGame *game;
	CSimon *simon;
	Ghoul *goomba;
	Whip* whip;
	Torch * torch;
	Ground *ground;
	BoundMap *bound;
	Zombie* zombie;
	ResourceManagement * resource;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> items;
	Queue<LPGAMEOBJECT> itemtoSpawn;
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
	void LoadScene();
	void SpawnItem(Item* item) {
		this->items.push_back(item);
	}
	void LoadObjects(int currentScene);
	void SetScene(int currentScene);
	SceneManagement();
	~SceneManagement();
};

