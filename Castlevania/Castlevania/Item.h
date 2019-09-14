#pragma once
#ifndef _ITEM_CLASS
#define _ITEM_CLASS
#include"GameObject.h"
class Item:public CGameObject
{
protected:
	unsigned int score;
	unsigned int heart	;
public:
	virtual void GetSpriteBox(float& _width, float& _height) {
		
	};
	Item() :score(0), heart(0) {};
	~Item();
};
#endif
