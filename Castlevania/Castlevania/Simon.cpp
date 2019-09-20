﻿#include <algorithm>
#include "debug.h"
#include "Simon.h"
#include "Game.h"
#include "Ghoul.h"
#include"Brick.h"
#include"Ground.h"
#include"Torch.h"
#include"Item.h"
#include"Entry.h"
#include"NextScene.h"
#include"SceneManagement.h"
#include"MoneyBagTrigger.h"
#include"Enemy.h"
#include"StairTrigger.h"
#include"MorningStar.h"
void CSimon::Renderer(int ani)
{
	int alpha = 255;
	if (untouchable) alpha = 128;
	animations[ani]->Render(nx, x, y, alpha);

	RenderBoundingBox();
	//RenderSpriteBox();// = tọa độ simon trong world game để tính vị trí so với các object khác
}

void CSimon::HandleFirstStepOnStair()
{
	if (this->nx == 1) {
		if (stairPos.x - this->x >= SIMON_UPSTAIR_OFFSET) {
			this->isAutoWalk = true;
			return;
		}
		else {
			this->isAutoWalk = false;
			this->isOnStair = true;
			this->isFirstStepOnStair = true;
			this->LastStepOnStairPos = { floor(this->x),floor(this->y) };
			DebugOut(L"Step x=%f y=%f \n", this->LastStepOnStairPos.x, this->LastStepOnStairPos.y);
			this->SetState(SIMON_STATE_UPSTAIR_STEPUP);
		}
	}
}




void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	// Calculate dx, dy 
	CGameObject::Update(dt);

	if (this->isAutoWalk) {

		vx = SIMON_AUTOWALKING_SPEED;
	}
	//DebugOut(L"x=%f y=%f \n", this->x, floor(this->y));
	if (this->startOnStair) {
		if(!this->isFirstStepOnStair)
			HandleFirstStepOnStair();
		else {
			SetState(SIMON_STATE_UPSTAIR_STEPUP);
		}
	}
	if (this->state == SIMON_STATE_UPSTAIR_STEPUP) {
		if (this->x - LastStepOnStairPos.x > SIMON_UPSTAIR_DISTANCE_X) {
			if (LastStepOnStairPos.y - this->y > SIMON_UPSTAIR_DISTANCE_Y) {
				this->y = LastStepOnStairPos.y - SIMON_UPSTAIR_DISTANCE_Y;
				this->x = LastStepOnStairPos.x + SIMON_UPSTAIR_DISTANCE_X;
				SetState(SIMON_STATE_UPSTAIR_IDLE);
				this->isOnStair = true;
				DebugOut(L" x=%f y=%f \n", this->x, this->y);
			}

		}
	}
	// Simple fall down
	if (!this->startOnStair &&state != SIMON_STATE_UPSTAIR_IDLE)
		vy += SIMON_GRAVITY * dt;
	if (this->isActack) {
		if (whip->CheckLastFrame()) {

			//DebugOut(L"Time count =%d \n", GetTickCount() - actack_start);
			this->isActack = false;
			SetState(SIMON_STATE_IDLE);
			whip->ResetLastFrame();
			ResetSpriteFrame();
			ResetActack_Time();
			this->animations[SIMON_ANI_STAND_ATTACK]->ResetLastFrame();
		}
		whip->Update(dt, coObjects);
	}



	// Bỏ những object không cần check va chạm với simon
	for (vector<LPGAMEOBJECT>::iterator it = coObjects->begin(); it != coObjects->end(); ) {

		if (dynamic_cast<Torch *>((*it)))
		{
			it = coObjects->erase(it);
		}
		else {
			++it;
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

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

		// block 
		x += min_tx * dx + nx * 0.2f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.2f;

		//if (nx != 0) vx = 0;
		//if (ny != 0) vy = 0;
		//	DebugOut(L"SIMON ny=%f", ny);
			// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground *>(e->obj)) {
				if (e->ny < 0) {
					if (this->state == SIMON_STATE_DEFLECT && this->vy > 0) {
						this->state = SIMON_STATE_IDLE;
					}
					else {
						this->isJumping = false;
						if (this->untouchable_start == 0) {

							if (ny != 0) vy = 0;
							if (nx != 0) vx = 0;
						}

						if (this->isActack) { // còn đang đánh thì dừng lại
							vx = 0;
						}
					}
				}
				else if (e->ny > 0 && this->vy < 0) {
					y += dy;
					if (nx != 0) vx = 0;

				}
				if (e->nx != 0 && this->startOnStair) {
					x += dx;
					y += dy;
				}

			}
			else if (dynamic_cast<StairTrigger *>(e->obj)) {
				/*if (this->startOnStair) {
					SetState(SIMON_STATE_IDLE);
					this->startOnStair = false;

				}*/
				if (e->nx != 0)
					x += dx;
				else if (e->ny != 0)
					y += dy;
			}
			else if (dynamic_cast<Enemy *>(e->obj)) {
				if (untouchable_start == 0) {
					Enemy *enemy = dynamic_cast<Enemy *>(e->obj);

					this->SetState(SIMON_STATE_DEFLECT);
					if (untouchable != 1)
						StartUntouchable();

					DebugOut(L"Va cham vy=%f vx=%f \n", this->vy, this->vx);

				}
				else if (e->nx == 0) {
					y += dy;
				}


			}
			//else if (dynamic_cast<Ghoul *>(e->obj)) // if e->obj is Goomba 
			//{
			//	Ghoul *ghoul = dynamic_cast<Ghoul *>(e->obj);
			//	//DebugOut(L"[col] SIMON ->Goomba \n");
			//	// jump on top >> kill Goomba and deflect a bit 
			//	if (e->ny < 0)
			//	{
			//		if (ghoul->GetState() != GHOUL_STATE_DIE)
			//		{
			//			//	goomba->SetState(GOOMBA_STATE_DIE);
			//			vy = -SIMON_DEFLECT_SPEED_X;
			//		}
			//		if (untouchable == 0)
			//		{
			//			if (ghoul->GetState() != GHOUL_STATE_DIE)
			//			{
			//				if (level > SIMON_LEVEL_SMALL)
			//				{
			//					level = SIMON_LEVEL_SMALL;
			//					StartUntouchable();
			//				}
			//				else
			//					SetState(SIMON_STATE_DIE);
			//			}
			//		}
			//	}
			//	else if (e->nx != 0)
			//	{

			//		if (untouchable == 0)
			//		{
			//			if (ghoul->GetState() != GHOUL_STATE_DIE)
			//			{
			//				if (level > SIMON_LEVEL_SMALL)
			//				{
			//					level = SIMON_LEVEL_SMALL;
			//					StartUntouchable();
			//				}
			//				else
			//					SetState(SIMON_STATE_DIE);
			//			}
			//		}
			//	}
			//}
			else if (dynamic_cast<Item *>(e->obj)) {
				if (dynamic_cast<MorningStar *>(e->obj)) {
					DebugOut(L"Morning star logic \n");
					SetState(SIMON_STATE_POWERUP);
					if (isActack) {
						ResetActack_Time();
						isActack = false;
					}
					StartPowerUp();
				}
				Item *item = dynamic_cast<Item *>(e->obj);
				item->SetDestroy();
			}
			else if (dynamic_cast<Entry *>(e->obj)) {
				DebugOut(L"Entry \n");
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;

				(e->obj)->isDestroyed = true;

				this->SetAutoWalk(true);
			}
			else if (dynamic_cast<MoneyBagTrigger *>(e->obj)) {
				DebugOut(L"Money bag \n");
				MoneyBagTrigger *trigger = dynamic_cast<MoneyBagTrigger *>(e->obj);
				trigger->isDestroyed = true;
				if (this->isAutoWalk) return;
				if (e->ny != 0) vy = 0;
				x += dx;
				trigger->SpawnMoneyBag();
				DebugOut(L"spawn money bag");

			}
			else if (dynamic_cast<NextScene*>(e->obj)) {
				if (this->isAutoWalk) {
					(e->obj)->SetDestroy();
					// clean up collision events
					SceneManagement::GetInstance()->GoNextScene();
				}



			}

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


	for (std::size_t i = 0; i < coObjects->size(); i++)
	{

		LPGAMEOBJECT e = coObjects->at(i);
		if (dynamic_cast<Item *>(e))
		{
			Item * f = dynamic_cast<Item*> (e);

			if (CGameObject::IsColliding(this, f))
			{
				if (dynamic_cast<MorningStar *>(e)) {
					DebugOut(L"Morning star logic \n");
					SetState(SIMON_STATE_POWERUP);
					if (isActack) {
						ResetActack_Time();
						isActack = false;
					}
					StartPowerUp();
				}
				//DebugOut(L"aabb \n");
				if (!f->CheckDestroyed()) {
					f->SetDestroy();
				}

			}

		}
		else if (dynamic_cast<StairTrigger*>(e)) {
			StairTrigger * f = dynamic_cast<StairTrigger*> (e);

			if (CGameObject::IsColliding(this, f))
			{
				if (!this->isColliceWithStair) {
					if (this->isOnStair) {
						SetState(SIMON_STATE_IDLE);
						this->isOnStair = false;
						this->startOnStair = false;
						this->isFirstStepOnStair = false;
						return;
					}
					this->isColliceWithStair = true;
					DebugOut(L"ColliceWithStair \n");
					this->stairPos = { f->x,f->y };
					f->SetActive(true);
					return;
				}
			}
			else if (f->CheckActive())
			{
				f->SetActive(false);
				this->isColliceWithStair = false;
				DebugOut(L"stop collice \n");
			}
		}
	}

}

void CSimon::Render()
{
	//DebugOut(L"Pos x=%f y=%f \n",x,y);
	int ani;
	if (state == SIMON_STATE_POWERUP) {
		ani = SIMON_ANI_IDLE_UPWHIP;
		Renderer(ani);
		return;
	}
	else if (state == SIMON_STATE_UPSTAIR_IDLE) {
		ani = SIMON_ANI_IDLE_UPSTAIR;
		Renderer(ani);
		return;
	}
	else if (state == SIMON_STATE_UPSTAIR_STEPUP) {
		ani = SIMON_ANI_STEP_UPSTAIR;
		Renderer(ani);
		return;
	}
	else if (state == SIMON_STATE_DEFLECT) {
		ani = SIMON_ANI_DEFLECT;
		Renderer(ani);
		return;
	}
	else if (state == SIMON_STATE_STAND_ATTACK) {

		ani = SIMON_ANI_STAND_ATTACK;
		whip->SetWhipPosition(x - 1.5*SIMON_SPRITE_BOX_WIDTH, y);

		whip->SetDirection(nx);
		whip->Render();


		Renderer(ani);
		return;
	}
	else if (state == SIMON_STATE_SIT_ATTACK) {

		ani = SIMON_ANI_SIT_ATTACK;
		whip->SetWhipPosition(x - 1.5*SIMON_SPRITE_BOX_WIDTH, y + SIMON_SPRITE_BOX_HEIGHT / 4);
		whip->SetDirection(nx);
		if (this->isActack) {
			whip->SetDirection(nx);
			whip->Render();
		}
		Renderer(ani);
		return;
	}
	else if (state == SIMON_STATE_SIT || state == SIMON_STATE_JUMP) {
		ani = SIMON_ANI_SITTING;
		Renderer(ani);
		return;
	}
	else if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else
		if (level == SIMON_LEVEL_BIG)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = SIMON_ANI_BIG_IDLE_RIGHT;
				else ani = SIMON_ANI_BIG_IDLE_RIGHT;
			}
			else if (vx > 0)
				ani = SIMON_ANI_BIG_WALKING_RIGHT;
			else ani = SIMON_ANI_BIG_WALKING_RIGHT;
		}
		else if (level == SIMON_LEVEL_SMALL)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = SIMON_ANI_BIG_IDLE_RIGHT;
				else ani = SIMON_ANI_BIG_IDLE_RIGHT;
			}
			else if (vx > 0)
				ani = SIMON_ANI_BIG_WALKING_RIGHT;
			else ani = SIMON_ANI_BIG_WALKING_RIGHT;
		}

	Renderer(ani);
	//DebugOut(L"ani=%d", ani);
	return;
}



void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
	{
		vy = -SIMON_JUMP_SPEED_Y;
		isJumping = true;
		break;
	}
	case SIMON_STATE_UPSTAIR_STEPUP: {
		vy = -SIMON_UPSTAIR_VELOCITY;
		vx = SIMON_UPSTAIR_VELOCITY;
		break;
	}
	case SIMON_STATE_UPSTAIR_IDLE: {
		this->startOnStair = false; // cho phép nhấn tiếp
		this->LastStepOnStairPos = { floor(this->x),floor(this->y) };
	}
	case SIMON_STATE_POWERUP: {
		vx = 0;
		vy = 0;
		break;
	}
	case SIMON_STATE_STAND_ATTACK:
	{
		if (!this->isJumping) vx = 0;
		break;
	}
	case SIMON_STATE_DEFLECT:
	{
		this->vy = -SIMON_DEFLECT_SPEED_X;
		this->vx = -SIMON_DEFLECT_SPEED_X;

		break;
	}
	case SIMON_STATE_SIT_ATTACK:
	case SIMON_STATE_SIT:
	case SIMON_STATE_IDLE:

		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;

	}
}

void CSimon::SimonUseSubWeapon()
{
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x + 10;
	this->body_x = left;
	top = y;

	right = left + SIMON_BIG_BBOX_WIDTH;
	bottom = top + SIMON_BIG_BBOX_HEIGHT;




	/*left += 10;
	top += 10;*/

	//	DebugOut(L"BBOX l=%f t=%f r=%f b=%f \n ",left, top,right,bottom);
}

