#pragma once
#include"BBoxObjects.h"
class Ground:public BBoxObject
{
public:
	virtual void Render();
	Ground();
	~Ground();
};

