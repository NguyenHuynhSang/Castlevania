#pragma once
#include"BBoxObjects.h"
class NextScene:public BBoxObject
{
	int playerAction;
	int nextSceneID;
	bool isColliceWithPlayer;
public:

	bool CheckIsColliceWithPlayer() {
		return this->isColliceWithPlayer;
	};

	void Reset() {
		this->isColliceWithPlayer = false;
	}
	void SetColliceWithPlayer(bool flag) {
		this->isColliceWithPlayer = flag;
	}

	int GetPlayerAction() {
		return this->playerAction;
	}

	int GetNextSceneID() {
		return this->nextSceneID;
	}

	virtual void Render() {
		RenderBoundingBox();
	};
	NextScene(int playerAction,int nextSceneID) :nextSceneID(nextSceneID), playerAction(playerAction) {
		this->isColliceWithPlayer = false;
	}
	~NextScene();
};

