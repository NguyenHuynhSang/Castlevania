#pragma once
#include"Item.h"

#define AXEITEM_BBOX_WIDTH 30
#define AXEITEM_BBOX_HEIGHT 28
class AxeItem:public Item
{
public:

	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	AxeItem();
	~AxeItem();
};

