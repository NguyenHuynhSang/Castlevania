#pragma once
#include"StaticObjects.h"
class Ground:public StaticObject
{
public:
	virtual void Render();
	Ground();
	~Ground();
};

