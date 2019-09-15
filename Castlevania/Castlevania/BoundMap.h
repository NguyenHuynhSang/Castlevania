#pragma once
#include"BBoxObjects.h"
class BoundMap:public BBoxObject
{
public:
	virtual void Render();
	BoundMap();
	~BoundMap();
};

