#pragma once

#include"Effects.h"
class Flame:public Effects
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	Flame();
	~Flame();
};

