#include "Heart.h"
#include"Torch.h"
#include"debug.h"
#include"Ground.h"
void Heart::Render()
{
	if (this->isHiding)
	{
		return;
	}
	animations[0]->Render(DIRECTION::DEFAULT, x, y);

}

void Heart::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (this->isDestroyed) {
		l = t = r = b = 0;
		return;
	}
	l = x;
	t = y;
	r = l + 24;
	b = t + 20;
}

void Heart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount()-wait_start> EFFECTS_LIFE_TIME)
	{
		this->isHiding = false;
	}
	if (this->isHiding)
	{
		return;
	}
	this->UpdateItem();
	if (this->setDestroy) {
		this->isDestroyed = true;
		return;
	}
	
	CGameObject::Update(dt);
	this->vy = HEART_MOVING_VY;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		y += dy;
		x = HEART_OX_HEIGHT * sin(y*HEART_MOVING_VX) + ox;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground *>(e->obj)) {
				this->isTourchGround = true;
				x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty * dy + ny * 0.1f;
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
			else {
				if (!this->isTourchGround)
				{
					y += dy;
					x = HEART_OX_HEIGHT * sin(y*HEART_MOVING_VX) + ox;
				}
			
			}
		}
	}
	// clean up collision events
	for (std::size_t i = 0; i < coEvents.size(); i++) delete coEvents[i];
}



Heart::Heart() :Item()
{
	AddAnimation("HEART_ANI_SMALL");
}

Heart::Heart(float ox): Item()
{
	AddAnimation("HEART_ANI_SMALL");
	this->ox = ox;
	this->heart = 1;
}


Heart::~Heart()
{
}
