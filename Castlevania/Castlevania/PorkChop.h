#pragma once
#include"Item.h"

#define ROAST_BBOX_WIDTH 32
#define ROAST_BBOX_HEIGHT 26
class PorkChop:public Item
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	PorkChop();
	~PorkChop();
};

