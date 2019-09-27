#include "LargeHeart.h"



void LargeHeart::Render()
{
	if (this->isHiding)
	{
		return;
	}
	animations[0]->Render(0,x,y);
}

void LargeHeart::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + LARGEHEART_BBOX_WIDTH;
	b = t + LARGEHEART_BBOX_HEIGHT;
}

void LargeHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount() - wait_start > EFFECTS_LIFE_TIME)
	{
		this->isHiding = false;
	}
	if (this->isHiding)
	{
		return;
	}
	if (this->isDestroyed)
	{
		return;
	}
	this->UpdateItem();
	if (this->setDestroy) {
		this->TurnOffCollision();
		this->isDestroyed = true;
		return;
	}

	CGameObject::Update(dt);

	vy += HEART_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		y += min_ty * dy + ny * 0.1f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

LargeHeart::LargeHeart() :Item()
{
	AddAnimation("HEART_ANI_BIG");
}


LargeHeart::~LargeHeart()
{
}
