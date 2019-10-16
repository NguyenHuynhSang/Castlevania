#pragma once
#include"BBoxObjects.h"
class NextScene:public BBoxObject
{
	int sceneDef;
	bool isColliceWithPlayer;
public:
	void SetSceneDef(int sd) {
		this->sceneDef = sd;
	}

	bool CheckIsColliceWithPlayer() {
		return this->isColliceWithPlayer;
	};


	void SetColliceWithPlayer(bool flag) {
		this->isColliceWithPlayer = flag;
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

