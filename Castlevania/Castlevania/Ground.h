#pragma once
#include"BBoxObjects.h"
class Ground:public BBoxObject
{
	bool flagCollice = false;
public:
	virtual void Render();
	void SetFlagCollice() {
		this->flagCollice = true;
	}
	bool CheckFlagCollice() {
		return this->flagCollice;
	}
	Ground();
	~Ground();
};

