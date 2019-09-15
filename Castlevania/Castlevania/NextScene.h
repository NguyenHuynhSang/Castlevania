#pragma once
#include"BBoxObjects.h"
class NextScene:public BBoxObject
{
public:
	virtual void Render() {
		RenderBoundingBox();
	};
	NextScene();
	~NextScene();
};

