#pragma once
#include"GameObject.h"
class SubWeapon:public CGameObject
{
protected:
	unsigned int damage;
	unsigned int heartCostPerUse;
public:
	SubWeapon();
	void SetNx(DIRECTION nx) {
		this->nx = nx;
	}
	virtual void GetSpriteBox(float& _width, float& _height) {

	};
	unsigned int GetDamege() {
		return this->damage;
	};
	unsigned int GetHeartCostPerUse() {
		return this->heartCostPerUse;
	};
	~SubWeapon();
};

