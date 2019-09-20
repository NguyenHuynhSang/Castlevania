#pragma once
#include"BBoxObjects.h"
class StairTrigger :public BBoxObject
{
	string direction;
	bool isActive=false; // dùng để đánh dấu simon đang va chạm trigger nào
public:
	virtual void Render();
	void SetActive(bool flag) {
		this->isActive = flag;
	}
	string GetDirecTion() {
		return this->direction;
	}
	bool CheckActive() {
		return this->isActive;
	}
	StairTrigger();
	~StairTrigger();
};

