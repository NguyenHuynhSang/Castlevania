#pragma once
#include"Enemy.h"
#define PANTHER_GRAVITY 0.001f
#define PANTHER_RUNNING_SPEED 0.3f
#define PANTHER_JUMPING_SPEED 0.2f

#define PANTHER_STATE_LIEDOWN 0
#define PANTHER_STATE_JUMP 100
#define PANTHER_STATE_RUNNING 200

#define PANTHER_ANI_LIEDOWN 0
#define PANTHER_ANI_JUMP 1
#define PANTHER_ANI_RUNNING 2

#define PANTHER_BBOX_WIDTH 64
#define PANTHER_BBOX_HEIGHT 32
class Panther:public Enemy
{
	bool isJumping = false;
	bool isActive;
public:
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	 void SetState(int state);
	virtual void GetSpriteBox(float& _width, float& _height) {
		_width = PANTHER_BBOX_WIDTH;
		_height = PANTHER_BBOX_HEIGHT;
	};
	Panther():Enemy() {
		AddAnimation("PANTHER_ANI_LIEDOWN");
		AddAnimation("PANTHER_ANI_JUMP");
		AddAnimation("PANTHER_ANI_RUNNING");
		this->isActive = false;
		this->hp = 1;
		this->score = 200;
	};
	~Panther();
};

