#pragma once
#include"Item.h"

#define ISTOPWATCH_BBOX_WIDTH 30
#define ISTOPWATCH_BBOX_HEIGHT 32
class IStopWatch:public Item
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	IStopWatch();
	~IStopWatch();
};

