#include "HolyWater.h"
#include"Enemy.h"
#include"Brick.h"
#include"Ground.h"
#include "Simon.h"
void HolyWater::Render()
{
	int ani;
	if (state == HOLYWATER_STATE_JAR)
	{
		ani = SWHOLYWATER_ANI_JAR;
	}
	else
	{
		ani = SWHOLYWATER_ANI_BURNING;
	}

	animations[ani]->Render(nx, x, y);

}

void HolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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



	vy += HOLYWATER_GRAVITY * dt;

	CGameObject::Update(dt);

	if (this->burning_start == 0)
	{
		if (this->state == HOLYWATER_STATE_BURNING)
		{
			this->burning_start = GetTickCount64();
		}

	}
	else if (GetTickCount64() - burning_start > HOLYWATER_BURNING_TIME) {

		this->DestroyImmediate();
		return;

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

		x += min_tx * dx + nx * 0.4f;
		if (ny <= 0)
			y += min_ty * dy + ny * 0.4f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground*>(e->obj)) {

				this->SetState(HOLYWATER_STATE_BURNING);
			}
			else if (dynamic_cast<Enemy*>(e->obj)) {

				Enemy* z = dynamic_cast<Enemy*>(e->obj);
				if (!z->isDestroyed)
				{

					z->SubtractHP(this->damage);
					if (z->GetHp() == 0)
					{
						CSimon::AddScore(z->GetScore());
						z->SetDestroy();
					}
				}
			}
			else {
				if (e->nx != 0)
					x += dx;
				if (e->ny != 0)
					y += dy;
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}

}

void HolyWater::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + HOLYWATER_BBOX_WIDTH;
	b = t + HOLYWATER_BBOX_HEIGHT;

}

void HolyWater::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case HOLYWATER_STATE_JAR:

		if (nx == DIRECTION::RIGHT)
		{
			this->vx = HOLYWATER_FALLING_VX;
		}
		else if (nx == DIRECTION::LEFT) {
			this->vx = -HOLYWATER_FALLING_VX;
		}

		this->vy = -HOLYWATER_FALLING_VY;
		break;
	case HOLYWATER_STATE_BURNING:
	{
		this->vx = 0;
		this->vy = 0;

	}
	}



}

HolyWater::HolyWater(DIRECTION nx) :SubWeapon()
{
	this->nx = nx;
	AddAnimation("SWHOLYWATER_ANI_JAR");
	AddAnimation("SWHOLYWATER_ANI_BURNING");
	this->SetState(HOLYWATER_STATE_JAR);
	this->damage = 1;
}

HolyWater::~HolyWater()
{
}
