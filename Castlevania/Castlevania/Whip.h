#pragma once
#include "GameObject.h"

#define WHIP_STATE_NORMAL      0
#define WHIP_STATE_CHAIN       1
#define WHIP_STATE_MORNINGSTAR 2

#define WHIP_ANI_NORMAL      0
#define WHIP_ANI_CHAIN       1
#define WHIP_ANI_MORNINGSTAR 2

#define WHIP_BBOX_NORMAL_WIDTH 55
#define WHIP_BBOX_NORMAL_HEIGHT 20

#define WHIP_BBOX_CHAIN_WIDTH 55
#define WHIP_BBOX_CHAIN_HEIGHT 20

#define WHIP_BBOX_MORNINGSTAR_WIDTH 85
#define WHIP_BBOX_MORNINGSTAR_HEIGHT 20

class Whip :public CGameObject
{
private:
	UINT  damage = 1;
	int currentAnimation = 0;
	bool collideOneTime = false;
public:
	void StartCalculatorCollice() {
		this->collideOneTime = false;
	}
	void SetDamage(int damage) { this->damage = damage; }
	UINT GetDamage() { return damage; }
	void SetDirection(DIRECTION nx) { this->nx = nx; }
	void UpWhip() {
		this->state++;
		//this->state = WHIP_STATE_CHAIN;
		if (this->state >= 2) {
			this->state = WHIP_STATE_MORNINGSTAR;
		}
		DebugOut(L"Whip state=%d", this->state);
	}
	void SetWhipPosition(float x, float y) { this->x = x; this->y = y; }
	virtual void Update(DWORD dt, int score_, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetVelocity(float vx,float vy) {
		this->vx = vx;
		this->vy = vy;
	
	};
	bool CheckLastFrame();
	void ResetLastFrame() {
		animations[currentAnimation]->ResetLastFrame();
	}
	void ResetAnimationFrame() {
		animations[currentAnimation]->ResetAnimation();
	}
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void GetSpriteBox(float& width, float& height) {
		width =240;
		height = 66;
	};
	
	Whip();
	~Whip();	
};

