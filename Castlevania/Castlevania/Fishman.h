#pragma once
#include"Enemy.h"
#define FISHMAN_BBOX_WIDTH 30
#define FISHMAN_BBOX_HEIGHT 64

#define FISHMAN_GRAVITY 0.0005f
#define FISHMAN_JUMP_VY 0.5f
#define FISHMAN_WALKING_SPEED 0.052f
#define FISHMAN_SHOOT_BULLES_TIME 2000


#define FISHMAN_STATE_JUMP 0
#define FISHMAN_STATE_WALKING 1
#define FISHMAN_STATE_SHOOTING 2

#define FISHMAN_ANI_JUMP 0
#define FISHMAN_ANI_WALKING 1
#define FISHMAN_ANI_SHOOTING 2

class Fishman:public Enemy
{
private:
	DWORD walking_start = 0;
	DWORD shooting_start = 0;
	bool isShooting = false;
	bool isSetWalking = false;
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void SetState(int state);
	virtual void GetSpriteBox(float& _width, float& _height) {
		_width = FISHMAN_BBOX_WIDTH;
		_height = FISHMAN_BBOX_HEIGHT;
	};
	Fishman();
	~Fishman();
};

