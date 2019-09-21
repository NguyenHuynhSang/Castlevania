#pragma once
#include"BBoxObjects.h"
class StairTrigger :public BBoxObject
{
	int direction; // hướng của cầu thang
	bool isActive=false; // dùng để đánh dấu simon đang va chạm trigger nào
public:
	virtual void Render();
	void SetActive(bool flag) {
		this->isActive = flag;
	}
	int GetDirection() {
		return this->direction;
	}
	void SetDirection(int dir) {
		this->direction = dir;
	}
	bool CheckActive() {
		return this->isActive;
	}
	StairTrigger();
	~StairTrigger();
};

