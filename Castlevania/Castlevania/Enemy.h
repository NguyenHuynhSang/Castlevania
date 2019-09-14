#pragma once
#include"GameObject.h"
#define ENEMY_SPWAWN_TIME 5000
#include"Game.h"
#include"Debug.h"
class Enemy:public CGameObject
{
protected:
	unsigned int score;
	unsigned int hp;
	DWORD spawn_start;
	bool reSpawn;
	float respawnX;
	float respawnY;

public:
	virtual void Update();
	
	bool GetRespawn() {
		return this->reSpawn;
	}
	void StartRespawn() {
		this->reSpawn = true;
		this->spawn_start = GetTickCount();
	};
	void ResetSpawnStart() {
		this->spawn_start = 0;
	}
	void SetRespawnPosition(float x,float y) {
		this->respawnX = x;
		this->respawnY = y;
	}
	Enemy() :CGameObject() {
		score = hp = 0;
		spawn_start = 0;
		reSpawn = false;
	}
	~Enemy();
};

