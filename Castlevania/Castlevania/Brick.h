#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void GetSpriteBox(float& width, float& height) {
		width = BRICK_BBOX_WIDTH;
		height = BRICK_BBOX_HEIGHT;
	};
};