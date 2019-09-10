#pragma once
#include "GameObject.h"

#define WHIP_STATE_LV1 0
#define WHIP_STATE_LV1 100
#define WHIP_STATE_LV1 200

#define WHIP_ANI_LV1 0


class Whip:public CGameObject
{
private:
	UINT  damage=1;
public:
	void SetDamage(int damage) { this->damage = damage; }
	UINT GetDamage() { return damage; }
	virtual void Render(){
	
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void RenderWhip(int nx);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void GetSpriteBox(float& width, float& height) {
		width =66;
		height = 20;
	};
	
	Whip();
	~Whip();
};

