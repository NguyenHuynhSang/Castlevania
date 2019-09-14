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
	CTileMap* cmap;
	static SceneManagement * __instance;
	bool isNextScene;
	void LoadResource();
	int currentScene;
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
	void LoadObjects(int currentScene);
	void SetScene(int currentScene);
	SceneManagement();
	~SceneManagement();
};

