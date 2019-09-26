#pragma once
#include"Effects.h"

#define DEBRIS_GRAVITY 0.0004f
#define DEBRIS_VY_HIGHT 0.6f
#define DEBRIS_VY_LOW   0.2f
#define DEBRIS_VX_FAST 0.4f
#define DEBRIS_VX_SLOW 0.2f



class DebrisBrick:public Effects
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	DebrisBrick();
	DebrisBrick(float vx,float vy);
	~DebrisBrick();
};

