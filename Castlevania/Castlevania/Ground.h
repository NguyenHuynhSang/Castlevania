#pragma once
#include"TileObjects.h"
class Ground:public TileObjects
{
public:
	virtual void Render();
	Ground();
	~Ground();
};

