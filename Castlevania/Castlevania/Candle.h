#pragma once
#include"GameObject.h"

#define CANDLE_BBOX_WIDTH  16
#define CANDLE_BBOX_HEIGHT 32
class Candle:public CGameObject
{
public:
	Candle();
	~Candle();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void GetSpriteBox(float& width, float& height) {
		width = CANDLE_BBOX_WIDTH;
		height = CANDLE_BBOX_HEIGHT;
	};
};

