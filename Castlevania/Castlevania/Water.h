#pragma once
#include"BBoxObjects.h"
class Water:public BBoxObject
{
public:
	virtual void Render();
	Water();
	~Water();
};

