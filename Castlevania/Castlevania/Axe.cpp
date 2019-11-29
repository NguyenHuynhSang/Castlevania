#include "Axe.h"
#include"Enemy.h"
#include"Fireball.h"
#include"Brick.h"
#include"Torch.h"
#include"Candle.h"
#include"HandleSpawnEffects.h"
#include "Simon.h"

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
	if (nx== DIRECTION::RIGHT)
	{
		this->vx = AXE_SPEED_VX;
	}
	else if (nx == DIRECTION::LEFT) {
		this->vx = -AXE_SPEED_VX;
	}
	
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
		
			}
			else if (dynamic_cast<CBrick *>(e->obj)) {

				CBrick *brick = dynamic_cast<CBrick *>(e->obj);
				if (!brick->isDestroyed)
				{
					brick->SetDestroy();
				}
				this->SetDestroy();
			}

			else if (dynamic_cast<Candle *> (e->obj)) {
				
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
					float l, t, r, b;
					z->GetBoundingBox(l, t, r, b);
					if (e->nx==-1)
					{
						HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_SPARK, l, t);
					}
					else if (e->nx==1)
					{
						HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_SPARK, r, t);
					}
					else if (e->ny==1)
					{
						HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_SPARK, l, t);
					}
					else if (e->ny==-1)
					{
						HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_SPARK, l, t);
					}
					
					
					DebugOut(L"Axe damage enemy \n");
					z->SubtractHP(this->damage);
					if (z->GetHp() == 0)
					{
				
						CSimon::AddScore(z->GetScore());
						
						z->SetDestroy();
					}
				}
			
				x += dx;
				y += dy;
			}
			else {

				x += dx;

				y += dy;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
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
	this->damage = 2;
	this->heartCostPerUse = 1;
	AddAnimation("AXE_SUBWEAPON_ANI");
	this->vx = AXE_SPEED_VX;
	this->vy = -AXE_SPEED_VY;
}


Axe::~Axe()
{
}
