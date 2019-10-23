#pragma once
#include"SubWeapon.h"


#define HOLYWATER_GRAVITY 0.0015f
#define HOLYWATER_FALLING_VX 0.25f
#define HOLYWATER_FALLING_VY 0.2f

#define HOLYWATER_BURNING_TIME 1000
#define HOLYWATER_BURNING_ATTACK_TIME 200 // damege enemy 1 times per 200ms

#define HOLYWATER_STATE_JAR 0
#define HOLYWATER_STATE_BURNING 100

#define SWHOLYWATER_ANI_JAR 0
#define SWHOLYWATER_ANI_BURNING 1



#define HOLYWATER_BBOX_WIDTH 32
#define HOLYWATER_BBOX_HEIGHT 28

class HolyWater:public SubWeapon
{
private:
	DWORD burning_start;
	DWORD burningAttack_start;
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetState(int state);
	HolyWater(DIRECTION nx);
	~HolyWater();
};

