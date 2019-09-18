#pragma once
#include "GameObject.h"
#include"Enemy.h"
#define WHIP_STATE_LV1 0
#define WHIP_STATE_LV2 100
#define WHIP_STATE_LV3 200

#define WHIP_ANI_LV1 0


class Whip:public CGameObject
{
private:
	static Whip * __instance;
	UINT  damage=1;
public:
	void SetDamage(int damage) { this->damage = damage; }
	UINT GetDamage() { return damage; }
	void SetDirection(int nx) { this->nx = nx; }
	void SetWhipPosition(float x, float y) { this->x = x; this->y = y; }
	static Whip * GetInstance();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void GetSpriteBox(float& width, float& height) {
		width =240;
		height = 66;
	};
	
	Whip();
	~Whip();	
};

