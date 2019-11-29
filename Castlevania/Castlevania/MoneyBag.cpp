#include "MoneyBag.h"
#include"Ground.h"
#include"HandleSpawnEffects.h"
void MoneyBag::Render()
{
	if (this->isHiding)
	{
		return;
	}
	int ani = 0;
	if (state == MONEYBAG_STATE_FULLCOLOR)
	{
		ani = MONEYBAG_ANI_COLOR;
	}
	else if (state == MONEYBAG_STATE_BLUE)
	{
		ani = MONEYBAG_ANI_BLUE;
	}
	else if (state == MONEYBAG_STATE_RED)
	{
		ani = MONEYBAG_ANI_RED;
	}
	else
	{
		ani = MONEYBAG_ANI_WHITE;
	}
	animations[ani]->Render(DIRECTION::DEFAULT, x, y);
}

void MoneyBag::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + MONEYBAG_BBOX_WIDTH;
	b = t + MONEYBAG_BBOX_HEIGHT;
}

void MoneyBag::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state != MONEYBAG_STATE_FULLCOLOR)
		this->UpdateItem();
	if (GetTickCount() - wait_start > EFFECTS_LIFE_TIME)
	{
		this->isHiding = false;
	}
	if (this->isHiding)
	{
		return;
	}

	if (this->isDestroyed)
	{
		return;
	}
	if (this->setDestroy) {
		switch (this->state)
		{
		case MONEYBAG_STATE_FULLCOLOR: {
			HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_ST1000, this->x, this->y);
			break;
		}
		case MONEYBAG_STATE_WHITE: {
			HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_ST100, this->x, this->y);
			break;
		}
		case MONEYBAG_STATE_RED: {
			HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_ST400, this->x, this->y);
			break;
		}
		case MONEYBAG_STATE_BLUE: {
			HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_ST700, this->x, this->y);
			break;
		}
		}
		this->isDestroyed = true;
		return;
	}

	CGameObject::Update(dt);
	if (state != MONEYBAG_STATE_FULLCOLOR)
		vy += ITEM_GRAVITY * dt;
	else {
		vy -= ITEM_GRAVITY * dt;
		y += dy;
		x += dx;
	}


	if (state != MONEYBAG_STATE_FULLCOLOR)
	{

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
			if (ny <= 0)
				y += min_ty * dy + ny * 0.4f;


			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<Ground *>(e->obj)) {
					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
				}
				else
				{
					if (e->nx != 0)
						x += dx;
					else if (e->ny != 0)
						
						y += dy;
				}
			}

		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	else
		for (std::size_t i = 0; i < coObjects->size(); i++) {
			{
				if (dynamic_cast<Ground *>(coObjects->at(i)))
				{
					Ground * f = dynamic_cast<Ground*> (coObjects->at(i));
					if (this->IsColliding(this, f)) {
						f->SetFlagCollice();
						break;
					}
					else
					{
						if (f->CheckFlagCollice())
						{
							vy = 0;
							vx = 0;
						}
					}
				}

			}
		}

}

void MoneyBag::SetState(int state)
{
	this->state = state;
	switch (this->state)
	{
	case MONEYBAG_STATE_FULLCOLOR: {
		this->score = 1000;
		break;
	}
	case MONEYBAG_STATE_WHITE: {
		this->score = 100;
		break;
	}
	case MONEYBAG_STATE_RED: {
		this->score = 400;
		break;
	}
	case MONEYBAG_STATE_BLUE: {
		this->score = 700;
		break;
	}
	}
}

MoneyBag::MoneyBag() :Item()
{
	AddAnimation("MONEYBAG_ANI_COLOR");
	AddAnimation("MONEYBAG_ANI_BLUE");
	AddAnimation("MONEYBAG_ANI_RED");
	AddAnimation("MONEYBAG_ANI_WHITE");
}


MoneyBag::~MoneyBag()
{
}
