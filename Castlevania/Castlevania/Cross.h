#pragma once
#include"Item.h"


#define CROSS_BBOX_WIDTH 32
#define CROSS_BBOX_HEIGHT 32
class Cross:public Item
{
private:
public:
	virtual void Render();
	virtual void  GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	Cross();
	~Cross();
};

