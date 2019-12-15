#pragma once
#include<string>
#include"Game.h"
class PlayScene;
class CSprite;
class Hud
{
	CGame* game;
	PlayScene* scene;
	int score;
	int playerHP;
	int playerEnery;
	static int bossHP;
	int gameTime;
	int currentWeapon;
	int state;
	RECT bound;
	std::string  _UIinfor;
public:
	static void SetBossHp(int hp) { bossHP = hp; }
	void Update();
	void Render();
	Hud(PlayScene* scene);
	~Hud();
};

