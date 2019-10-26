#pragma once
#include"Enemy.h"



#define VAMPIREBAT_STATE_SLEEP 0
#define VAMPIREBAT_STATE_IDLE 100
#define VAMPIREBAT_STATE_FLY_SLOW 1000
#define VAMPIREBAT_STATE_FLY_FAST 800

#define VAMPIREBAT_ANI_SLEEP 0
#define VAMPIREBAT_ANI_FLYING 1

#define VAMPIREBAT_IDLE_TIME_LONG 1500
#define VAMPIREBAT_IDLE_TIME_SHORT 800

#define VAMPIREBAT_ATTACKSLOW_TIME 1000
#define VAMPIREBAT_ATTACKFAST_TIME 700

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
	RECT activeArea;
	DWORD attack_start;
	DWORD flyback_start;
	DWORD waiting_start;
	unsigned int attack_time;
	unsigned int waiting_time;
	RECT slowAttackArea;
	RECT fastAttackArea;
public:
	void SetActiveArea(RECT r) { this->activeArea = r; }
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

