#include "Fishman.h"
#include"Ground.h"
#include"Water.h"
#include"HandleSpawnEffects.h"
#include"HandleSpawnEnemy.h"
void Fishman::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y + 5;
	right = x + FISHMAN_BBOX_WIDTH;
	bottom = y + FISHMAN_BBOX_HEIGHT;
}

void Fishman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (this->isDestroyed) return;
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
	//	if (reSpawn) return;
		//DebugOut(L"update \n");
	CGameObject::Update(dt);

	if (state == FISHMAN_ANI_WALKING)
	{
		if (this->walking_start != 0
			&& GetTickCount() - walking_start > FISHMAN_SHOOT_BULLES_TIME)
		{
			SetState(FISHMAN_STATE_SHOOTING);
			this->walking_start = 0;
		}
	}
	if (state == FISHMAN_STATE_SHOOTING)
	{
		if (this->shooting_start != 0
			&& GetTickCount() - shooting_start > FISHMAN_SHOOT_BULLES_TIME)
		{
			if ((rand() % 2) + 1 == 2)
				this->nx = DIRECTION::RIGHT;
			else
				this->nx = DIRECTION::LEFT;
			SetState(FISHMAN_ANI_WALKING);
			this->shooting_start = 0;
		}
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	vy += FISHMAN_GRAVITY * dt;


	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.2f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.2f;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground*>(e->obj)) {


				if (e->ny != 0)
				{
					if (e->ny == -1)
					{
						if (nx != 0) vx = 0;
						if (ny != 0) vy = 0;
						if (!this->isSetWalking)
						{
							SetState(FISHMAN_STATE_WALKING);
							this->isSetWalking = true;
							DebugOut(L"Set state \n");
						}


					}
					else {
						x += dx;
						y += dy;

					}

				}
				if (e->nx != 0)
				{
					x += dx;

				}

			}
			else if (dynamic_cast<Water*>(e->obj))
			{
				x += dx;
				y += dy;
				HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_BUBBLE, this->x, this->y);

			}
			else {
				if (e->nx != 0)
					x += dx;
				else if (e->ny != 0) {
					y += dy;
				}

			}
		}


	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Fishman::Render()
{
	int ani = 0;
	if (state == FISHMAN_STATE_JUMP)
	{
		ani = FISHMAN_ANI_JUMP;
	}
	else if (state == FISHMAN_STATE_WALKING)
	{

		ani = FISHMAN_ANI_WALKING;
	}
	else
	{
		ani = FISHMAN_ANI_SHOOTING;
	
	}
	animations[ani]->Render(nx, x, y);
}

void Fishman::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case FISHMAN_STATE_JUMP:
	{
		this->vx = 0;
		this->vy = -FISHMAN_JUMP_VY;
		break;
	}
	case FISHMAN_STATE_WALKING:
	{
		walking_start = GetTickCount();
		if (nx == DIRECTION::RIGHT)
			this->vx = FISHMAN_WALKING_SPEED;
		else if(nx== DIRECTION::LEFT)
			this->vx = -FISHMAN_WALKING_SPEED;
		break;
	}
	case FISHMAN_STATE_SHOOTING:
	{
		this->shooting_start = GetTickCount();
		this->vx = 0;
		this->vy = 0;
		HandleSpawnEnemy::GetInstance()->SpawnEnemy(EDFIREBALL, 1, 0, this->x, this->y + 5, this->nx);
		break;
	}

	}
}

Fishman::Fishman() :Enemy()
{
	AddAnimation("FISHMAN_ANI_JUMP");
	AddAnimation("FISHMAN_ANI_WALKING");
	AddAnimation("FISHMAN_ANI_SHOOTING");
	this->SetState(FISHMAN_STATE_JUMP);
	this->hp = 1;
	this->score = 300;
}




Fishman::~Fishman()
{
}
