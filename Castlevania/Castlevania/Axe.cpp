#include "Axe.h"
#include"Enemy.h"
#include"Fireball.h"
#include"Brick.h"
#include"Torch.h"
#include"Candle.h"


void Axe::Render()
{
	animations[0]->Render(nx, x, y);
}

void Axe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
	this->vx = AXE_SPEED_VX*nx;
	vy += AXE_GRAVITY * dt;

	CGameObject::Update(dt);

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

				x += dx;

				y += dy;
			}
		}
	}

}

void Axe::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + AXE_BBOX_WIDTH;
	b = y + AXE_BBOX_HEIGHT;
}

Axe::Axe() :SubWeapon()
{
	this->damage = 1;
	this->heartCostPerUse = 1;
	AddAnimation("AXE_SUBWEAPON_ANI");
	this->vx = AXE_SPEED_VX;
	this->vy = -AXE_SPEED_VY;
}


Axe::~Axe()
{
}
