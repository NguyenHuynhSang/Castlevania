#pragma once
#include"StaticObjects.h"
class Ground:public StaticObject
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	Ground();
	~Ground();
};
