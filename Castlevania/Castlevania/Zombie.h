#pragma once
#include"Enemy.h"
#define ZOMBIE_BBOX_WIDTH 32
#define ZOMBIE_BBOX_HEIGHT 60

#define ZOMBIE_GRAVITY			0.002f
#define ZOMBIE_WALKING_SPEED			0.10f
class Zombie:public Enemy
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void GetSpriteBox(float& _width, float& _height) {
		_width = ZOMBIE_BBOX_WIDTH;
		_height = ZOMBIE_BBOX_HEIGHT;
	};
public:

	Zombie() :Enemy() {
		AddAnimation("ZOMBIE_ANI_WALKING");
		nx = -1;
		this->hp = 1;
		this->score = 100;

	};
	~Zombie();
};

