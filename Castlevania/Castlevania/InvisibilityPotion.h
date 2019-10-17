#pragma once
#include"Item.h"

#define INVISIBILITYPOTION_BBOX_WIDTH 33
#define INVISIBILITYPOTION_BBOX_HEIGHT 40
class InvisibilityPotion:public Item
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	InvisibilityPotion();
	~InvisibilityPotion();
};

