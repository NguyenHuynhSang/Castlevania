#pragma once
#include"Enemy.h"
#define BULLET_SPEED_VX 0.2f

#define BULLET_BBOX_WIDTH 14
#define BULLET_BBOX_HEIGHT 12
class Fireball:public Enemy
{
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void GetSpriteBox(float& _width, float& _height) {
	};
	Fireball();
	Fireball(DIRECTION nx,float vy);
	Fireball(DIRECTION nx);
	~Fireball();
};

