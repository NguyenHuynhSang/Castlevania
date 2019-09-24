#pragma once
#include"Item.h"
#include"define.h"

#define HEART_MOVING_VX 0.15f
#define HEART_MOVING_VY 0.05f
#define HEART_OX_HEIGHT 20 // Độ cao sóng sin theo trục x
class Heart:public Item
{
	float ox;// tọa độ trục ox
	bool isTourchGround = false;
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	Heart() ;
	Heart(float ox);
	~Heart();
};

