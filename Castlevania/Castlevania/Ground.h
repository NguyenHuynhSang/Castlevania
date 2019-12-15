#pragma once
#include"BBoxObjects.h"
class Ground:public BBoxObject
{
	bool isColliceMoneyBag = false;
public:
	virtual void Render();
	void SetFlagCollice() {
		this->isColliceMoneyBag = true;
	}
	bool CheckFlagCollice() {
		return this->isColliceMoneyBag;
	}
	Ground();
	~Ground();
};

