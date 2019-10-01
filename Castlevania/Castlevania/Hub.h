#pragma once
#include<string>
#include"Game.h"
class Hub
{
	CGame* game;
	int score;
	int simonHP;
	int bossHP;
	int gameTime;
	int currentWeapon;
	int state;
	RECT bound;
	std::string  _UIinfor;
public:
	void Update();
	void Render();
	Hub();
	~Hub();
};

