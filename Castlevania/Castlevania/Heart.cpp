#include "Heart.h"
#include"Torch.h"
#include"debug.h"

void Heart::Render()
{
	if (this->isDestroyed) return;
	int ani;
	if (state == ITEM_STATE_HIDING) {
		return;
	}

	ani = HEART_ANI_BIG;
	animations[ani]->Render(0, x, y);

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
	if (this->setDestroy ) {
		this->TurnOffCollision();
		this->isDestroyed = true;
		return;
	}
	// Bỏ những object không cần check va chạm với simon
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
}



Heart::Heart()
{
	AddAnimation("HEART_ANI_BIG");
	AddAnimation("HEART_ANI_SMALL");
	SetState(HEART_BIG);
}

Heart::Heart(int state)
{
	SetState(state);
}


Heart::~Heart()
{
}
