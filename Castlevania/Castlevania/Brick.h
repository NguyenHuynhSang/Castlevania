#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32

#define BRICK_STATE_NORMAL 0
#define BRICK_STATE_BREAKINGBRICK 1

#define BRICK_ANI_NORMAL 0
#define	BRICK_ANI_BREAKING 1
class CBrick : public CGameObject
{
	int itemDef = -1;
public:
	CBrick();
	~CBrick();
	virtual void Render();
	void SetItemDef(int item) {
		this->itemDef = item;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void GetSpriteBox(float& width, float& height) {
		width = BRICK_BBOX_WIDTH;
		height = BRICK_BBOX_HEIGHT;
	};
};