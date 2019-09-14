#pragma once

#include"Effects.h"
class Spark:public Effects
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	Spark();
	~Spark();
};

