#pragma once
#include"Item.h"

#define LARGEHEART_BBOX_WIDTH 24
#define LARGEHEART_BBOX_HEIGHT 20
class LargeHeart:public Item
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	LargeHeart();
	~LargeHeart();
};

