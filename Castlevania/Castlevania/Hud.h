#pragma once
#include<string>
#include"Game.h"
class SceneManagement;
class CSprite;
class Hud
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
	Hud(SceneManagement* scene);
	~Hud();
};

