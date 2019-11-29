#pragma once
#include"Item.h"
#define MONEYBAG_BBOX_HEIGHT 30
#define MONEYBAG_BBOX_WIDTH 31

#define MONEYBAG_STATE_FULLCOLOR 0
#define MONEYBAG_STATE_WHITE 100
#define MONEYBAG_STATE_BLUE 200
#define MONEYBAG_STATE_RED 300

#define MONEYBAG_ANI_COLOR 0
#define MONEYBAG_ANI_BLUE 1
#define MONEYBAG_ANI_RED 2
#define MONEYBAG_ANI_WHITE 3


class MoneyBag :public Item
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void SetState(int state);
	MoneyBag();
	~MoneyBag();
};

