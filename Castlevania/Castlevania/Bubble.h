#pragma once
#include"Effects.h"
#define BUBBLE_GRAVITY 0.0005f 
class Bubble:public Effects
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	Bubble();
	Bubble(float vx,float vy);
	~Bubble();
};

