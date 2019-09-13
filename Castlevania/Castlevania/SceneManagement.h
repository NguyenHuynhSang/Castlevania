#pragma once
#include<Windows.h>
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
	ResourceManagement * resource;
	vector<LPGAMEOBJECT> objects;
	CTileMap* cmap;
	static SceneManagement * __instance;
	bool isNextScene;
	void LoadResource();
public:
	static SceneManagement * GetInstance();
	void OnCreate();
	CSimon* GetSimon() {
		return this->simon;
	};
	void Update(DWORD dt);
	void Render();
	void LoadScene();
	SceneManagement();
	~SceneManagement();
};

