#pragma once
#include"BBoxObjects.h"
class NextScene:public BBoxObject
{
	int sceneDef;
public:
	void SetSceneDef(int sd) {
		this->sceneDef = sd;
	}
	int CheckSceneDef() {
		return this->sceneDef;
	}
	virtual void Render() {
		RenderBoundingBox();
	};
	NextScene();
	~NextScene();
};

