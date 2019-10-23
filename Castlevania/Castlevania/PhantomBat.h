#pragma once
#include"Enemy.h"




#define VAMPIREBAT_SLOW_FLYING 0.2f
#define VAMPIREBAT_FAST_FLYING 0.3f


#define VAMPIREBAT_STATE_SLEEP 0
#define VAMPIREBAT_STATE_IDLE 100
#define VAMPIREBAT_STATE_FLY_SLOW 200
#define VAMPIREBAT_STATE_FLY_FAST 300

#define VAMPIREBAT_ANI_SLEEP 0
#define VAMPIREBAT_ANI_FLYING 1







#define VAMPIREBAT_BBOX_HEIGHT 46
#define VAMPIREBAT_BBOX_WIDTH 100



class PhantomBat:public Enemy
{
private:
	D3DXVECTOR2*  tagerPosition;
	bool awake = false;
public:
	void StartAwake() { this->awake = true; };
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetSpriteBox(float& _width, float& _height) {
	};
	PhantomBat();
	~PhantomBat();

};

