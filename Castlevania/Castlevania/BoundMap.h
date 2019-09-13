#pragma once
#include"StaticObjects.h"
class BoundMap:public StaticObject
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	BoundMap();
	~BoundMap();
};

