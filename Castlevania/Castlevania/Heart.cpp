#include "Heart.h"
#include"Torch.h"
#include"debug.h"

void Heart::Render()
{
	if (this->isDestroy) return;
	int ani;
	if (state == ITEM_STATE_HIDING) {
		return;
	}

	ani = HEART_ANI_BIG;
	animations[ani]->Render(0, x, y);

}

void Heart::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (this->isDestroy) {
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
	if (this->isDestroy) return;
	// Bỏ những object không cần check va chạm với simon
	for (vector<LPGAMEOBJECT>::iterator it = coObjects->begin(); it != coObjects->end(); ) {

		if (dynamic_cast<Torch *>((*it)))
		{
			it = coObjects->erase(it);
		}
		else {
			++it;
		}
	}
	CGameObject::Update(dt);
	if (state == HEART_STATE_BIGHEART) {
		// Simple fall down
		vy += HEART_GRAVITY * dt;
	}
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

		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		
	}
}



Heart::Heart()
{
	AddAnimation("HEART_ANI_BIG");
	AddAnimation("HEART_ANI_SMALL");
}

Heart::Heart(int state)
{
	SetState(state);
}


Heart::~Heart()
{
}
