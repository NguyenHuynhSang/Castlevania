#pragma once
#include"Item.h"
class MorningStar:public Item
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	MorningStar();
	~MorningStar();
};

