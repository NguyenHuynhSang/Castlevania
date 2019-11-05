﻿#include "Whip.h"
#include"debug.h"
#include"Torch.h"
#include"Candle.h"
#include"Enemy.h"
#include"Brick.h"
#include"SceneManager.h"	






void Whip::Update(DWORD dt,int* _score, vector<LPGAMEOBJECT>* colliable_objects)
{

	// Calculate dx, dy 
	if (animations[currentAnimation]->GetCurrentFrame()
		!= animations[currentAnimation]->GetLastFrame()) {
		return;
	}
	
	CGameObject::Update(dt);
	if (!collideOneTime)
	{
		for (std::size_t i = 0; i < colliable_objects->size(); i++)
		{

			LPGAMEOBJECT e = colliable_objects->at(i);
			if (dynamic_cast<Torch*>(e))
			{
				Torch* f = dynamic_cast<Torch*> (e);
				if (CGameObject::IsColliding(this, f))
				{
					if (!f->CheckDestroyed()) {
						f->SetDestroy();
						//	DebugOut(L"Set destroy object \n");
					}

				}

			}
			else if (dynamic_cast<CBrick*>(e))
			{
				CBrick* f = dynamic_cast<CBrick*> (e);
				if (CGameObject::IsColliding(this, f))
				{
					if (!f->CheckDestroyed()) {
						f->SetDestroy();
						//	DebugOut(L"Set destroy object \n");
					}

				}
			}
			else if (dynamic_cast<Candle*>(e))
			{
				Candle* f = dynamic_cast<Candle*> (e);
				if (CGameObject::IsColliding(this, f))
				{
					if (!f->CheckDestroyed()) {
						f->SetDestroy();
						//	DebugOut(L"Set destroy object \n");
					}

				}

			}
			else if (dynamic_cast<Enemy*>(e)) {
				Enemy* f = dynamic_cast<Enemy*> (e);
				if (CGameObject::IsColliding(this, f)) {
					if (!f->isDestroyed)
					{
						f->SubtractHP(this->damage);
						if (f->GetHp() == 0)
						{
							f->SetDestroy();
							*_score += f->GetScore();
						}

					}
					this->SetDestroy();
					DebugOut(L"Collice \n");
				}

			}
		}
	}	
	this->collideOneTime = true;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	CalcPotentialCollisions(colliable_objects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		/*x += dx;
		y += dy;*/
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Torch*>(e->obj)) {

				Torch* torch = dynamic_cast<Torch*>(e->obj);
				if (!torch->isDestroyed)
				{
					torch->SetDestroy();
				}
				this->SetDestroy();
			}
			else if (dynamic_cast<CBrick*>(e->obj)) {

				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (!brick->isDestroyed)
				{
					brick->SetDestroy();
				}
				this->SetDestroy();
			}

			else if (dynamic_cast<Candle*> (e->obj)) {
				this->SetDestroy();
				Candle* candle = dynamic_cast<Candle*>(e->obj);
				if (!candle->isDestroyed)
				{
					candle->SetDestroy();
				}
			}
			else if (dynamic_cast<Enemy*>(e->obj)) {

				Enemy* z = dynamic_cast<Enemy*>(e->obj);
				if (!z->isDestroyed)
				{

					z->SubtractHP(this->damage);
					if (z->GetHp() == 0)
					{
						z->SetDestroy();
					}
				}
				this->SetDestroy();
			}
			else {

				x += dx;

				y += dy;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}




void Whip::Render()
{
	switch (this->state)
	{
	case WHIP_STATE_NORMAL: {
		currentAnimation = WHIP_ANI_NORMAL;
		break;
	}
	case WHIP_STATE_CHAIN: {
		currentAnimation = WHIP_ANI_CHAIN;
		break;

	}
	case WHIP_STATE_MORNINGSTAR: {
		currentAnimation = WHIP_ANI_MORNINGSTAR;
		break;
	}
	}
	animations[currentAnimation]->Render(nx, x, y);
	if (animations[currentAnimation]->GetCurrentFrame() == animations[currentAnimation]->GetLastFrame())
		RenderBoundingBox();
	return;
}

bool Whip::CheckLastFrame()
{
	return animations[currentAnimation]->CheckAnimationDone();
}



void Whip::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (nx == DIRECTION::RIGHT) {
		l = x + 60 * 2 + 12;
		t = y + 12;
	}
	else if (nx == DIRECTION::LEFT) {
		if (state != WHIP_STATE_MORNINGSTAR)
			l = x + 55 - 4;
		else
			l = x + 55 - 30;
		t = y + 12;
	}


	switch (this->state)
	{
	case WHIP_STATE_NORMAL: {
		r = l + WHIP_BBOX_NORMAL_WIDTH;
		b = t + WHIP_BBOX_NORMAL_HEIGHT;
		break;
	}
	case WHIP_STATE_CHAIN: {
		r = l + WHIP_BBOX_CHAIN_WIDTH;
		b = t + WHIP_BBOX_CHAIN_HEIGHT;
		break;

	}
	case WHIP_STATE_MORNINGSTAR: {
		r = l + WHIP_BBOX_MORNINGSTAR_WIDTH;
		b = t + WHIP_BBOX_MORNINGSTAR_HEIGHT;
		break;
	}
	}

}

Whip::Whip()
{
	AddAnimation("WHIP_ANI_NORMAL", false);
	AddAnimation("WHIP_ANI_CHAIN", false);
	AddAnimation("WHIP_ANI_MORNINGSTAR", false);

}


Whip::~Whip()
{
}
