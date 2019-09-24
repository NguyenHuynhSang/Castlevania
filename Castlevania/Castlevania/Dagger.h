#pragma once
#include"SubWeapon.h"


#define DAGGER_BBOX_WIDTH 32
#define DAGGER_BBOX_HEIGHT 18

#define DAGGER_SPEED_X 0.5f



class Dagger:public SubWeapon
{
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);

	Dagger();
	~Dagger();
};

