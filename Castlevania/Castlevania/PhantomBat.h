#pragma once
#include"Enemy.h"



#define VAMPIREBAT_STATE_SLEEP 0
#define VAMPIREBAT_STATE_IDLE 100
#define VAMPIREBAT_STATE_FLY_SLOW 1000
#define VAMPIREBAT_STATE_FLY_FAST 800

#define VAMPIREBAT_FLYBACK_VX 0.15f
#define VAMPIREBAT_ANI_SLEEP 0
#define VAMPIREBAT_ANI_FLYING 1

#define VAMPIREBAT_IDLE_TIME_LONG 800
#define VAMPIREBAT_IDLE_TIME_SHORT 400

#define VAMPIREBAT_ATTACK_TIME 1000

#define VAMPIREBAT_FLY_BACK_TIME 1200






#define VAMPIREBAT_SPRITE_BBOX_HEIGHT 46
#define VAMPIREBAT_SPRITE_BBOX_WIDTH 100


#define VAMPIREBAT_BBOX_HEIGHT 46
#define VAMPIREBAT_BBOX_WIDTH 30


#define VAMPIREBAT_BBOX_SLOWACTACK 200
#define VAMPIREBAT_BBOX_FASTACTACK 550



class PhantomBat:public Enemy
{
private:
	D3DXVECTOR2*  tagerPosition;
	bool awake = false;
	bool intro = false;
	bool outOfArea=false;
	bool hitBoder = false;
	bool flyToRamdomTager = false;
	RECT activeArea;
	DWORD attack_start;
	DWORD flyback_start;
	DWORD flyrandom_start;
	DWORD waiting_start;


	DWORD flyback_time;
	unsigned int attack_time;
	unsigned int waiting_time;
	RECT slowAttackArea;
	RECT bossAttackArea;
public:
	void SetActiveArea(RECT r) { this->activeArea = r; }
	RECT GetActiveArea() { return this->activeArea; }
	void StartAwake() { this->awake = true; };
	bool CheckAwake() {
		return this->awake;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetSpriteBox(float& _width, float& _height) {
	};

	PhantomBat();
	~PhantomBat();

};

