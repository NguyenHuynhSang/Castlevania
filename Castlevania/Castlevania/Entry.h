#pragma once
#include"BBoxObjects.h"
class Entry:public BBoxObject
{
public:
	virtual void Render() {
		RenderBoundingBox();
	};
	Entry();
	~Entry();
};

