#pragma once
#include"Item.h"

#define IHOLYWATER_BBOX_HEIGHT 32
#define IHOLYWATER_BBOX_WEIGHT 32


#define IHOLY_WATER_ANI_JAV 0

class IHolyWater:public Item
{

public:

	virtual void Render();
	virtual void  GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

	IHolyWater();
	~IHolyWater();
};

