#include "IHolyWater.h"
#include"Ground.h"
void IHolyWater::Render()
{
	if (this->isHiding)
	{
		return;
	}
	animations[0]->Render(DIRECTION::DEFAULT, x, y);
}

void IHolyWater::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + IHOLYWATER_BBOX_WEIGHT;
	b = t + IHOLYWATER_BBOX_HEIGHT;
}

void IHolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
		this->isDestroyed = true;
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
			if (dynamic_cast<Ground*>(e->obj)) {
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

IHolyWater::IHolyWater():Item()
{
	AddAnimation("IHOLY_WATER_ANI_JAV");

}

IHolyWater::~IHolyWater()
{
}
