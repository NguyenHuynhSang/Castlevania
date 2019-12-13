#pragma once
#include"BBoxObjects.h"
class NextScene:public BBoxObject
{
	int nextMapID;
	int nextEntry;
	int playerAction;
	bool isColliceWithPlayer;
public:
	void SetSceneDef(int sd) {
		this->nextMapID = sd;
	}

	bool CheckIsColliceWithPlayer() {
		return this->isColliceWithPlayer;
	};

	void Reset() {
		this->isColliceWithPlayer = false;
	}
	void SetColliceWithPlayer(bool flag) {
		this->isColliceWithPlayer = flag;
	}
	int GetMapID() {
		return this->nextMapID;
	}
	int GetNextEntryID() {
		return this->nextEntry;
	}
	int GetPlayerAction() {
		return this->playerAction;
	}

	virtual void Render() {
		RenderBoundingBox();
	};
	NextScene(int nextMapID, int nextEntry, int playerAction) :nextMapID(nextMapID), nextEntry(nextEntry), playerAction(playerAction) {
		this->isColliceWithPlayer = false;
	}
	~NextScene();
};

