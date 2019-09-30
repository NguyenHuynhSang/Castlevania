#pragma once
#include"GameObject.h"
#define ENEMY_SPWAWN_TIME 2000
#include"Game.h"
#include"Debug.h"
class Enemy:public CGameObject
{
protected:
	unsigned int score;
	unsigned int hp;
	DWORD spawn_start;
	bool isFreeze = false;
public:
	void UpdateEnemy();
	void SetFreeze() {
		this->isFreeze = true;
	}

	void ResetSpawnStart() {
		this->spawn_start = GetTickCount();
	}

	Enemy() :CGameObject() {
		score = hp = 0;
		spawn_start = 0;
		
	}
	~Enemy();
};

