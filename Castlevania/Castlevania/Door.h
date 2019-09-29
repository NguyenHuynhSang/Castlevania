#pragma once
#include"GameObject.h"

#define DOOR_CLOSE_BBOX_WIDTH 16
#define DOOR_CLOSE_BBOX_HEIGHT 96

#define DOOR_STATE_CLOSE 0
#define DOOR_STATE_OPEN 100

#define DOOR_ANI_CLOSE 0
#define DOOR_ANI_OPEN 1





class Door:public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void GetSpriteBox(float& width, float& height) {
	};
	Door();
	~Door();
};

