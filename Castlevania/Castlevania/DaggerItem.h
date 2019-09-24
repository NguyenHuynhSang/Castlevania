#pragma once
#include"Item.h"
#define IDAGGER_BBOX_WIDTH 32
#define IDAGGER_BBOX_HEIGHT 18
class DaggerItem:public  Item
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	DaggerItem();
	~DaggerItem();
};

