#include "PhantomBat.h"

void PhantomBat::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	
	if (this->state==VAMPIREBAT_STATE_SLEEP)
	{
		l = x+120;
		b = t + 250;// for test
	}
	else
	{
		b = t + VAMPIREBAT_BBOX_HEIGHT;
	}
	r = l + VAMPIREBAT_BBOX_WIDTH;
}

void PhantomBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (awake)
	{
		this->SetState(VAMPIREBAT_STATE_IDLE);
	}
}

void PhantomBat::Render()
{
	int ani = 0;
	if (state==VAMPIREBAT_STATE_SLEEP)
	{
		ani = VAMPIREBAT_ANI_SLEEP;
	}else {
		ani = VAMPIREBAT_ANI_FLYING;
	}
	animations[ani]->Render(DIRECTION::DEFAULT, x, y);
	RenderBoundingBox();
}

PhantomBat::PhantomBat() :Enemy()
{
	AddAnimation("VAMPIREBAT_ANI_SLEEP");
	AddAnimation("VAMPIREBAT_ANI_FLYING");
	this->state = VAMPIREBAT_STATE_SLEEP;
}

PhantomBat::~PhantomBat()
{
}
