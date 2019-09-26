#pragma once
#ifndef _EFFECT_CLASS
#define _EFFECT_CLASS
#define EFFECTS_LIFE_TIME 500
#include"GameObject.h"
#include"define.h"
class Effects :public CGameObject
{
protected:
	int itemDef=-1; // hiện item khi effect kết thúc
	float objectPosX; // lấy vị trí object để spawn effects
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
	void AddItemDef(int itemName) {
		this->itemDef = itemName;
	}
	Effects();
	~Effects();
};

#endif