#pragma once
#include"Item.h"
#define DOUBLE_SHOT 100

#define MULTIPLYSHOTITEM_BBOX_WIDTH 32
#define MULTIPLYSHOTITEM_BBOX_HEIGHT 32
class MultiplyShotItem:public Item
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	MultiplyShotItem();
	~MultiplyShotItem();
};

