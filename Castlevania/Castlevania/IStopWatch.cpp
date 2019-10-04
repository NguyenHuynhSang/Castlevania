#include "IStopWatch.h"
#include"Ground.h"


void IStopWatch::Render()
{
	animations[0]->Render(0, x, y);
}

void IStopWatch::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + ISTOPWATCH_BBOX_WIDTH;
	b = t + ISTOPWATCH_BBOX_HEIGHT;
}

void IStopWatch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

	if (this->isTorchGround)
	{
		return;
	}

	CGameObject::Update(dt);

	vy += ITEM_GRAVITY * dt;

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
		if (ny <= 0)
			y += min_ty * dy + ny * 0.4f;


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground *>(e->obj)) {
				this->isTorchGround = true;
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
			else
			{
				if (e->nx != 0)
					x += dx;
				else if (e->ny != 0)
					y += dy;
			}
		}

	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

IStopWatch::IStopWatch() :Item()
{
	AddAnimation("STOPWATCH_ITEM_ANI");
}


IStopWatch::~IStopWatch()
{
}
