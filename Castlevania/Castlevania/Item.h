﻿#pragma once
#ifndef _ITEM_CLASS
#define _ITEM_CLASS
#include"GameObject.h"

#define ITEM_LIFE_TIME 5000
class Item :public CGameObject
{

protected:
	unsigned int score;
	unsigned int heart;
	DWORD lifetime_start;
	DWORD wait_start;
	bool isHiding = true;
	bool isTorchGround = false;

public:
	int GetScore() { return this->score; }
	virtual void GetSpriteBox(float& _width, float& _height) {

	};
	void UpdateItem() {
		if (GetTickCount() - this->lifetime_start > ITEM_LIFE_TIME) {
			this->DestroyImmediate();
		}
	}

	bool CheckisHiding() {
		return this->isHiding;
	}
	void SetIsHiding(bool flag) {
		this->isHiding = flag;
	}

	int GetHeartPoint() {
		return this->heart;
	}
	Item() :CGameObject(), score(0), heart(0) {
		this->lifetime_start = GetTickCount();
		wait_start = GetTickCount();
	};
	~Item();
};
#endif
