#pragma once
#include "GameObject.h"

#define GHOUL_WALKING_SPEED 0.05f;

#define GHOUL_BBOX_WIDTH 16
#define GHOUL_BBOX_HEIGHT 15
#define GHOUL_BBOX_HEIGHT_DIE 9

#define GHOUL_STATE_WALKING 100
#define GHOUL_STATE_DIE 200

#define GHOUL_ANI_WALKING 0
#define GHOUL_ANI_DIE 1
#define GHOUL_GRAVITY 0.002f
class Ghoul : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();


public: 	
	virtual void SetState(int state);
	virtual void GetSpriteBox(float& width, float& height) {
		width = GHOUL_BBOX_WIDTH;
		height = GHOUL_BBOX_HEIGHT;
	};
	
};