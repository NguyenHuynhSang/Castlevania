﻿#include "Bat.h"
#include"Camera.h"


void Bat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + BAT_BBOX_WIDTH;
	bottom = top + BAT_BBOX_HEIGHT;
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroyed)
	{
		return;
	}
	if (this->setDestroy)
	{
		this->UpdateEnemy();
		this->isDestroyed = true;
		return;
	}
	if (this->isFreeze)
	{
		return;
	}
	if (nx == DIRECTION::RIGHT) vx = BAT_FLY_SPEED_X;
	else if (nx == DIRECTION::LEFT) vx = -BAT_FLY_SPEED_X;

	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y = BAT_OY_HEIGHT * sin(x * BAT_FLY_SPEED_Y) + oy;
	}
	else
	{
		x += dx;
		y = BAT_OY_HEIGHT * sin(x * BAT_FLY_SPEED_Y) + oy;
	}
	// clean up collision events
	for (std::size_t i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Bat::Render()
{
	animations[0]->Render(nx, x, y);
}

Bat::Bat() :Enemy()
{
	AddAnimation("BAT_ANI_FLYING");
	AddAnimation("BAT_ANI_IDLE");
}

Bat::Bat(float oy) :Enemy()
{
	AddAnimation("BAT_ANI_FLYING");
	AddAnimation("BAT_ANI_IDLE");
	this->oy = oy;
	this->hp = 1;
	this->score = 200;
}


Bat::~Bat()
{
}
