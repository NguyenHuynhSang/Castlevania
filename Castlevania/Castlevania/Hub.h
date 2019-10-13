#pragma once
#include<string>
#include"Game.h"
class SceneManagement;
class CSprite;
class Hub
{
	CGame* game;
	SceneManagement* scene;
	int score;
	int playerHP;
	int playerEnery;
	int bossHP;
	int gameTime;
	int currentWeapon;
	int state;
	RECT bound;
	std::string  _UIinfor;
public:
	void Update();
	void Render();
	Hub(SceneManagement* scene);
	~Hub();
};

