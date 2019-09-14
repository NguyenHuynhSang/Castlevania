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
	bool reSpawn;
	float respawnX;
	float respawnY;
	float enermyBBoxWidth; // dùng để tính toán aabb với cambox từng loại enemy
	float enermyBBoxHeight;
public:
	void UpdateEnemy();

	bool GetRespawn() {
		return this->reSpawn;
	}
	void StartRespawn() {
		this->reSpawn = true;
		this->spawn_start = GetTickCount();
		this->x = this->respawnX;
		this->y = this->respawnY;
		this->vx = 0;
		this->vy = 0;
		DebugOut(L"respawn x= %f, y=%f \n",x,y);
	};
	void ResetSpawnStart() {
		this->spawn_start = GetTickCount();
	}
	void SetRespawnPosition(float x,float y) {
		this->respawnX = x;
		this->respawnY = y;
	}
	Enemy() :CGameObject() {
		score = hp = 0;
		spawn_start = 0;
		reSpawn = false;
		spawn_start = 0;
	}
	~Enemy();
};

