#pragma once
#ifndef _EFFECT_CLASS
#define _EFFECT_CLASS
#define EFFECTS_LIFE_TIME 500
#include"GameObject.h"
class Effects :public CGameObject
{
protected:
	string itemName; // hiện item khi effect kết thúc
	float objectPosX;
	float objectPosY;
	void SpawnItem();
	DWORD lifetime_start;
public:
	void UpdateEffect() {
		if (GetTickCount() - this->lifetime_start > EFFECTS_LIFE_TIME) {
			this->SetDestroy();
		}
	}
	virtual void GetSpriteBox(float& _width, float& _height) {
	};
	void SetObjectPosition(float x,float y) {
		this->objectPosX = x;
		this->objectPosY = y;
	}
	void AddItemDef(string itemName) {
		this->itemName = itemName;
	}
	Effects();
	~Effects();
};

#endif