#pragma once
#include"Item.h"

#define CRYSTALL_BBOX_WIDTH 28
#define CRYSTALL_BBOX_HEIGHT 32

class Crystal:public Item
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	Crystal();
	~Crystal();
};

