#include "Dagger.h"
#include"Enemy.h"
#include"Torch.h"
#include"Candle.h"
#include"Zombie.h"
#include"Dagger.h"
#include"Brick.h"
#include"Fireball.h"
void Dagger::Render()
{
	animations[0]->Render(nx, x, y);
	RenderBoundingBox();
}

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

	CGameObject::Update(dt);
	this->vx = DAGGER_SPEED_X * nx;

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
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Torch *>(e->obj)) {

				Torch *torch = dynamic_cast<Torch *>(e->obj);
				if (!torch->isDestroyed)
				{
					torch->SetDestroy();
				}
				this->SetDestroy();
			}
			else if (dynamic_cast<CBrick *>(e->obj)) {

				CBrick *brick = dynamic_cast<CBrick *>(e->obj);
				if (!brick->isDestroyed)
				{
					brick->SetDestroy();
				}
				this->SetDestroy();
			}
			else if (dynamic_cast<Fireball *>(e->obj)) {

				Fireball *fireball = dynamic_cast<Fireball *>(e->obj);
				if (!fireball->isDestroyed)
				{
					fireball->SetDestroy();
				}
				this->SetDestroy();
			}
			else if (dynamic_cast<Candle *> (e->obj)) {
				this->SetDestroy();
				Candle *candle = dynamic_cast<Candle *>(e->obj);
				if (!candle->isDestroyed)
				{
					candle->SetDestroy();
				}
			}
			else if (dynamic_cast<Enemy *>(e->obj)) {

				Enemy *z = dynamic_cast<Enemy  *>(e->obj);
				if (!z->isDestroyed)
				{
					z->SetDestroy();
				}
				this->SetDestroy();
			}
			else {
				if (nx != 0)
					x += dx;
				else if (nx != 0)
					y += dy;
			}
		}
	}

}

void Dagger::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + DAGGER_BBOX_WIDTH;
	b = t + DAGGER_BBOX_HEIGHT;
}

Dagger::Dagger() :SubWeapon()
{
	this->damage = 1;
	this->heartCostPerUse = 1;
	AddAnimation("DAGGER_ITEM_ANI");

}


Dagger::~Dagger()
{
}
