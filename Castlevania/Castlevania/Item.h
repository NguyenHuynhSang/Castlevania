#pragma once
#include"GameObject.h"
class Item:public CGameObject
{
protected:
	unsigned int score;
	unsigned int heart	;
	bool isDestroy = false;
public:
	virtual void GetSpriteBox(float& _width, float& _height) {
		
	};
	void SetDestroy() {
		this->isDestroy = true;
	}
	Item() :score(0), heart(0) {};
	~Item();
};

