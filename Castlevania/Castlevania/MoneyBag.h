#pragma once
#include"Item.h"
#define MONEYBAG_BBOX_HEIGHT 30
#define MONEYBAG_BBOX_WIDTH 31
class MoneyBag :public Item
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	MoneyBag();
	~MoneyBag();
};

