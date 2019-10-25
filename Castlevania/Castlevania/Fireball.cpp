#include "Fireball.h"



void Fireball::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BULLET_BBOX_WIDTH;
	bottom = y + BULLET_BBOX_HEIGHT;
}

void Fireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
	CGameObject::Update(dt);

	if (nx == DIRECTION::RIGHT) this->vx = BULLET_SPEED_VX;
	else if (nx == DIRECTION::LEFT) this->vx = -BULLET_SPEED_VX;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			if (nx != 0)
				x += dx;
			else if (nx != 0)
				y += dy;

		}
	}
}

void Fireball::Render()
{
	animations[0]->Render(nx, x, y);
}

Fireball::Fireball() :Enemy()
{
	AddAnimation("FIREBALL_ANI");
}

Fireball::Fireball(float vx, float vy)
{
}

Fireball::Fireball(DIRECTION nx) : Enemy()
{
	AddAnimation("FIREBALL_ANI");
	this->nx = nx;
	this->hp = 1;
	this->score = 100;
}



Fireball::~Fireball()
{
}
