#pragma once
#include"BBoxObjects.h"
class Ground:public BBoxObject
{
	bool isColliceMoneyBag = false;
	bool isCollicePlayer = false;
public:
	virtual void Render();
	bool CheckIsCollicePlayer() {
		return isCollicePlayer;
	}
	void SetCollicePlayer(bool flag) { this->isCollicePlayer = flag; };
	void SetFlagCollice() {
		this->isColliceMoneyBag = true;
	}
	bool CheckFlagCollice() {
		return this->isColliceMoneyBag;
	}
	Ground();
	~Ground();
};

