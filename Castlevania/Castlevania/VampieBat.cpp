#include "VampieBat.h"
#include"Game.h"


void VampieBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + BAT_BBOX_WIDTH;
	bottom = top + BAT_BBOX_HEIGHT;
}

void VampieBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroyed)
	{
		return;
	}
	if (this->setDestroy)
	{
		this->isDestroyed = true;
		return;
	}
	if (this->x > CGame::GetInstance()->GetCamera().left + SCREEN_WIDTH / 2) {
		return;
	}
	vx = -nx* BAT_FLY_SPEED_X;
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y = BAT_OY_HEIGHT * sin(x*BAT_FLY_SPEED_Y) + oy;
	}
	else
	{
		x += dx;
		y = BAT_OY_HEIGHT * sin(x*BAT_FLY_SPEED_Y) + oy; 
	}
	// clean up collision events
	for (std::size_t i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void VampieBat::Render()
{
	animations[0]->Render(0, x, y);
}

VampieBat::VampieBat():Enemy()
{
	AddAnimation("BAT_ANI_FLYING");
	AddAnimation("BAT_ANI_IDLE");
}


VampieBat::~VampieBat()
{
}
