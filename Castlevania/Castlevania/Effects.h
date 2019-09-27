#pragma once
#ifndef _EFFECT_CLASS
#define _EFFECT_CLASS

#include"GameObject.h"
#include"define.h"
class Effects :public CGameObject
{
protected:

	DWORD lifetime_start;
public:
	void UpdateEffect() {
		if (GetTickCount() - this->lifetime_start > EFFECTS_LIFE_TIME) {
			this->SetDestroy();
		}
	}
	virtual void GetSpriteBox(float& _width, float& _height) {
	};
	Effects();
	~Effects();
};

#endif