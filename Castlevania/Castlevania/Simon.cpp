﻿#include <algorithm>
#include "debug.h"
#include "Simon.h"
#include "Game.h"
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
#include"SpawnZone.h"
#include "Candle.h"
#include"DaggerItem.h"
#include"Brick.h"
#include"Water.h"
#include"HandleSpawnEffects.h"
#include"Door.h"
#include"AxeItem.h"
#include"IStopWatch.h"
#include"HandleSpawnSubWeapon.h"
CSimon::CSimon() :CGameObject()
{
	this->hp_ = 16;
	this->score_ = 0;
	this->enery_ = 5;
	untouchable = 0;
	whip = new Whip();
	this->AddAnimation("SIMON_ANI_IDLE");		// idle right big 0
	this->AddAnimation("SIMON_ANI_WALKING");		// walk right big  1
	this->AddAnimation("SIMON_ANI_SITTING");       // sit   2
	this->AddAnimation("SIMON_ANI_STAND_ATTACK", false);       // stand attack   3
	this->AddAnimation("SIMON_ANI_SIT_ATTACK", false);       // sit attack   4
	this->AddAnimation("SIMON_ANI_DEFLECT");    //5
	this->AddAnimation("SIMON_ANI_IDLE_UPWHIP");    //6
	this->AddAnimation("SIMON_ANI_IDLE_UPSTAIR");    //7
	this->AddAnimation("SIMON_ANI_STEP_UPSTAIR");    //8
	this->AddAnimation("SIMON_ANI_IDLE_DOWNSTAIR");    //9
	this->AddAnimation("SIMON_ANI_STEP_DOWNSTAIR");    //10
	this->AddAnimation("SIMON_ANI_UPSTAIR_ATTACK", false);    //11
	this->AddAnimation("SIMON_ANI_DOWNSTAIR_ATTACK", false); //12
	//this->animations[SIMON_ANI_STAND_ATTACK]->SetAnimationLoop(false);
}

CSimon::~CSimon()
{
	delete whip;
}
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
	//reset vx vy remain from last state
	this->vx = 0;
	this->vy = 0;
	DebugOut(L"HandleFirstStepOnStair \n");
	//up right first step
	if (onStairDirection == STAIRDIRECTION::DEFAULT) return;
	else if (onStairDirection == STAIRDIRECTION::UPRIGHT) {
		DebugOut(L"Simon x=%f y=%f \n", this->x, this->y);

		if (stairPos.x - this->x > SIMON_UPSTAIR_RIGHT_OFFSET) {
			this->isAutoWalk = true;
			SetState(SIMON_STATE_WALKING_RIGHT);
			return;
		}
		else if (stairPos.x - this->x < SIMON_UPSTAIR_RIGHT_OFFSET - 5) {
			this->isAutoWalk = true;
			SetState(SIMON_STATE_WALKING_LEFT);
			return;
		}
		else {
			if (state == SIMON_STATE_WALKING_LEFT) {
				if (nx == DIRECTION::LEFT) nx = DIRECTION::RIGHT;
				else if (nx == DIRECTION::RIGHT) nx = DIRECTION::LEFT;
			}
			this->isAutoWalk = false;
			this->isOnStair = true;
			this->isFirstStepOnStair = true;
			this->LastStepOnStairPos = { floor(this->x),floor(this->y) };
			DebugOut(L"Step x=%f y=%f \n", this->LastStepOnStairPos.x, this->LastStepOnStairPos.y);
			this->SetState(SIMON_STATE_UPSTAIR_RIGHT);
		}
	}
	else if (onStairDirection == STAIRDIRECTION::UPLEFT) {
		DebugOut(L"Simon x=%f y=%f \n", this->x, this->y);

		if (stairPos.x - this->x < SIMON_UPSTAIR_LEFT_OFFSET) {
			this->isAutoWalk = true;
			SetState(SIMON_STATE_WALKING_LEFT);
			return;
		}
		else if (stairPos.x - this->x > SIMON_UPSTAIR_LEFT_OFFSET + 5) {
			this->isAutoWalk = true;
			SetState(SIMON_STATE_WALKING_RIGHT);
			return;
		}
		else {
			if (state == SIMON_STATE_WALKING_RIGHT) {
				if (nx == DIRECTION::LEFT) nx = DIRECTION::RIGHT;
				else if (nx == DIRECTION::RIGHT) nx = DIRECTION::LEFT;
			}
			this->isAutoWalk = false;
			this->isOnStair = true;
			this->isFirstStepOnStair = true;
			this->LastStepOnStairPos = { floor(this->x),floor(this->y) };
			DebugOut(L"Step x=%f y=%f \n", this->LastStepOnStairPos.x, this->LastStepOnStairPos.y);
			this->SetState(SIMON_STATE_UPSTAIR_RIGHT);
		}
	}
	else if (onStairDirection == STAIRDIRECTION::DOWNLEFT)
	{
		if (stairPos.x - this->x < SIMON_DOWNSTAIR_LEFT_OFFSET) {
			this->isAutoWalk = true;
			SetState(SIMON_STATE_WALKING_LEFT);
			return;
		}
		else if (stairPos.x - this->x > SIMON_DOWNSTAIR_LEFT_OFFSET + 5) {
			this->isAutoWalk = true;
			SetState(SIMON_STATE_WALKING_RIGHT);
			return;
		}
		else {
			if (state == SIMON_STATE_WALKING_RIGHT) {
				if (nx == DIRECTION::LEFT) nx = DIRECTION::RIGHT;
				else if (nx == DIRECTION::RIGHT) nx = DIRECTION::LEFT;
			}
			this->isAutoWalk = false;
			this->isOnStair = true;
			this->isFirstStepOnStair = true;
			this->LastStepOnStairPos = { floor(this->x),floor(this->y) };
			DebugOut(L"First Step x=%f y=%f \n", this->LastStepOnStairPos.x, this->LastStepOnStairPos.y);
			this->SetState(SIMON_STATE_DOWNSTAIR_LEFT);
		}
	}
	else if (onStairDirection == STAIRDIRECTION::DOWNRIGHT)
	{
		if (stairPos.x - this->x > SIMON_DOWNSTAIR_RIGHT_OFFET) {
			this->isAutoWalk = true;
			SetState(SIMON_STATE_WALKING_RIGHT);
			return;
		}
		else if (stairPos.x - this->x < SIMON_DOWNSTAIR_RIGHT_OFFET - 5) {
			this->isAutoWalk = true;
			SetState(SIMON_STATE_WALKING_LEFT);
			return;
		}
		else {
			if (state == SIMON_STATE_WALKING_LEFT) {
				if (nx == DIRECTION::LEFT) nx = DIRECTION::RIGHT;
				else if (nx == DIRECTION::RIGHT) nx = DIRECTION::LEFT;
			}
			this->isAutoWalk = false;
			this->isOnStair = true;
			this->isFirstStepOnStair = true;
			this->LastStepOnStairPos = { floor(this->x),floor(this->y) };
			DebugOut(L"First Step x=%f y=%f \n", this->LastStepOnStairPos.x, this->LastStepOnStairPos.y);
			this->SetState(SIMON_STATE_DOWNSTAIR_RIGHT);
		}
	}
}

void CSimon::HandlePerStepOnStair()
{
	if (this->state == SIMON_STATE_UPSTAIR_RIGHT) {
		DebugOut(L"Up right \n ");
		if (this->x - LastStepOnStairPos.x > SIMON_ONSTAIR_DISTANCE_X) {
			if (LastStepOnStairPos.y - this->y > SIMON_ONSTAIR_DISTANCE_Y) {
				this->y = LastStepOnStairPos.y - SIMON_ONSTAIR_DISTANCE_Y;
				this->x = LastStepOnStairPos.x + SIMON_ONSTAIR_DISTANCE_X;
				SetState(SIMON_STATE_UPSTAIR_IDLE);
				this->isOnStair = true;
				DebugOut(L"Up right \n ");
			}

		}
	}
	else if (this->state == SIMON_STATE_UPSTAIR_LEFT) {
		if (this->x - LastStepOnStairPos.x < SIMON_ONSTAIR_DISTANCE_X) {
			if (LastStepOnStairPos.y - this->y > SIMON_ONSTAIR_DISTANCE_Y) {
				this->y = LastStepOnStairPos.y - SIMON_ONSTAIR_DISTANCE_Y;
				this->x = LastStepOnStairPos.x - SIMON_ONSTAIR_DISTANCE_X;
				SetState(SIMON_STATE_UPSTAIR_IDLE);
				this->isOnStair = true;
				//	DebugOut(L" x=%f y=%f \n", this->x, this->y);
			}

		}
	}
	else if (this->state == SIMON_STATE_DOWNSTAIR_LEFT)
	{
		if (LastStepOnStairPos.x - this->x > SIMON_ONSTAIR_DISTANCE_X) {
			if (LastStepOnStairPos.y - this->y < SIMON_ONSTAIR_DISTANCE_Y) {
				this->y = LastStepOnStairPos.y + SIMON_ONSTAIR_DISTANCE_Y;
				this->x = LastStepOnStairPos.x - SIMON_ONSTAIR_DISTANCE_X;
				SetState(SIMON_STATE_DOWNSTAIR_IDLE);
				this->isOnStair = true;
				DebugOut(L" DOWN left x=%f y=%f \n", this->x, this->y);
			}

		}
	}
	else if (this->state == SIMON_STATE_DOWNSTAIR_RIGHT)
	{
		if (this->x - LastStepOnStairPos.x > SIMON_ONSTAIR_DISTANCE_X) {
			if (LastStepOnStairPos.y - this->y < SIMON_ONSTAIR_DISTANCE_Y) {
				this->y = LastStepOnStairPos.y + SIMON_ONSTAIR_DISTANCE_Y;
				this->x = LastStepOnStairPos.x + SIMON_ONSTAIR_DISTANCE_X;
				SetState(SIMON_STATE_DOWNSTAIR_IDLE);
				this->isOnStair = true;
				DebugOut(L" DOWN Right x=%f y=%f \n", this->x, this->y);
			}

		}
	}
}

void CSimon::HandleUseSubWeapon()
{

}

bool CSimon::SimonAutoWalkaStep(float step)
{
	if (this->x > step)
	{
		this->SetState(SIMON_STATE_IDLE);
		return true;
	}
	return false;

}



void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	if (this->isActack &&!this->isAutoWalk) {
		DebugOut(L"\n ATTACK");
		if (whip->CheckLastFrame()) {
			//DebugOut(L"Time count =%d \n", GetTickCount() - actack_start);
			this->isActack = false;
			if (this->isOnStair)
			{
				if (this->onStairDirection == STAIRDIRECTION::UPLEFT
					|| this->onStairDirection == STAIRDIRECTION::UPRIGHT)
				{
					this->lastState = SIMON_STATE_UPSTAIR_ATTACK;
					SetState(SIMON_STATE_UPSTAIR_IDLE);
				}
				else if (this->onStairDirection == STAIRDIRECTION::DOWNLEFT
					|| this->onStairDirection == STAIRDIRECTION::DOWNRIGHT)
				{
					this->lastState = SIMON_STATE_DOWNSTAIR_ATTACK;
					SetState(SIMON_STATE_DOWNSTAIR_IDLE);
				}
			}
			else {
				this->state = SIMON_STATE_IDLE;
			}
			whip->ResetLastFrame();
			ResetSpriteFrame();
			ResetActack_Time();
			this->animations[SIMON_ANI_STAND_ATTACK]->ResetAnimation();
			this->animations[SIMON_ANI_SIT_ATTACK]->ResetAnimation();
			this->animations[SIMON_ANI_UPSTAIR_ATTACK]->ResetAnimation();
			this->animations[SIMON_ANI_DOWNSTAIR_ATTACK]->ResetAnimation();
		}
		whip->Update(dt, coObjects);
		whip->SetDirection(nx);
	}
	if (this->startOnStair) {
		if (!this->isFirstStepOnStair)
			HandleFirstStepOnStair();
		else {
			if (this->onStairDirection == STAIRDIRECTION::UPRIGHT)
				SetState(SIMON_STATE_UPSTAIR_RIGHT);
			else if (this->onStairDirection == STAIRDIRECTION::UPLEFT)
			{
				SetState(SIMON_STATE_UPSTAIR_LEFT);
			}
			else if (this->onStairDirection == STAIRDIRECTION::DOWNLEFT)
			{
				SetState(SIMON_STATE_DOWNSTAIR_LEFT);
			}
			else if (this->onStairDirection == STAIRDIRECTION::DOWNRIGHT)
			{
				SetState(SIMON_STATE_DOWNSTAIR_RIGHT);
			}
		}
	}
	this->HandlePerStepOnStair();
	// Simple fall down
	if (!this->startOnStair
		&& !this->isOnStair
		&& state != SIMON_STATE_UPSTAIR_IDLE
		&& state != SIMON_STATE_DOWNSTAIR_IDLE
		&& state != SIMON_STATE_UPSTAIR_ATTACK
		&& state != SIMON_STATE_DOWNSTAIR_ATTACK)
	{
		vy += SIMON_GRAVITY * dt;
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
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		if (ny <= 0) // ny lớn hơn 0 simon overlap với ground trong trường hợp simon va chạm heart theo ny
			y += min_ty * dy + ny * 0.4f;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground*>(e->obj)) {
				if (e->ny < 0) {
					if (this->isOnStair) {
						x += dx;
						y += dy;

					}
					else
						if (this->state == SIMON_STATE_DEFLECT) {
							this->state = SIMON_STATE_IDLE;
							DebugOut(L"Reset ground SIMON_STATE_IDLE \n ");
						}
						else {
							this->isJumping = false;
							if (ny != 0) vy = 0;
							if (this->isActack || this->isUseSubWeapon) { // còn đang đánh thì dừng lại
								vx = 0;
							}
						}
				}
				else if (e->ny > 0 && this->vy < 0) {
					y += dy;
					if (nx != 0) vx = 0;
				}
				else if (e->nx != 0) {
					if (this->startOnStair || this->isOnStair)
					{
						x += dx;
						y += dy;
					}
					else {

						//if (nx != 0) vx = 0;
						if (ny != 0) vy = 0;
					}
				}
			}
			else if (dynamic_cast<Water*>(e->obj)) {
				if (e->nx != 0)
				{
					x += dx;
				}
				else if (e->ny != 0)
				{
					y += dy;
				}
				HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_BUBBLE, this->x, this->y);
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->nx != 0)
				{
					if (nx != 0)
						this->vx = 0;
					else if (ny != 0)
						this->vy = 0;
				}
				else if (e->ny == -1)
				{
					this->isJumping = false;
					if (ny != 0)
						this->vy = 0;
				}
				else if (e->ny == 1)
				{
					if (nx != 0)
						this->vx = 0;
					y += dy;
				}
			}
			else if (dynamic_cast<Torch*>(e->obj)) {
				if (e->nx != 0)
					x += dx;
				else if (e->ny != 0)
					y += dy;
			}
			else if (dynamic_cast<Candle*>(e->obj)) {
				if (e->nx != 0)
					x += dx;
				else if (e->ny != 0)
					y += dy;
			}
			else if (dynamic_cast<SpawnZone*>(e->obj))
			{
				if (e->nx != 0)
					x += dx;
				else if (e->ny != 0)
					y += dy;
			}
			else if (dynamic_cast<StairTrigger*>(e->obj)) {
				if (e->nx != 0)
					x += dx;
				else if (e->ny != 0) {
					if (e->ny < 0)
					{
						this->vy = 0.1f;
						this->dy = this->vy * dt;
					}
					y += dy;
				}

			}
			else if (dynamic_cast<Door*>(e->obj))
			{
				Door* door = dynamic_cast<Door*>(e->obj);
				if (door->GetState() == DOOR_STATE_CLOSE && !this->isJumping)
				{
					this->isHitDoor = true;
				}

			}
			else if (dynamic_cast<Enemy*>(e->obj)) {
				if (untouchable_start == 0) {
					Enemy* enemy = dynamic_cast<Enemy*>(e->obj);
					if (!this->isOnStair)
					{
						this->SetState(SIMON_STATE_DEFLECT);
						x += dx;
						y += dy;
					}
					if (untouchable != 1) {
						StartUntouchable();
						break; // không xét tiếp va chạm khi defect
					}
				}
				else {
					if (e->nx != 0)
					{
						x += dx;
					}
					if (e->ny != 0)
					{
						if (this->isJumping)
						{
							y += dy;
						}
					}
				}
			}
			else if (dynamic_cast<Item*>(e->obj)) {
				Item* item = dynamic_cast<Item*>(e->obj);
				if (item->CheckisHiding())
				{
					if (e->nx != 0)
						x += dx;
					else if (e->ny != 0)
						y += dy;
				}
				else {
					this->AddEnery(item->GetHeartPoint());
					if (dynamic_cast<MorningStar*>(e->obj)) {
						DebugOut(L"Morning star logic \n");
						SetState(SIMON_STATE_POWERUP);
						if (isActack) {
							ResetActack_Time();
							isActack = false;
						}
						StartPowerUp();
					}
					else if (dynamic_cast<DaggerItem*>(e->obj))
					{
						this->subWeaponDef = SWDDAGGER;
					}
					else if (dynamic_cast<AxeItem*>(e->obj))
					{
						this->subWeaponDef = SWDAXE;
					}
					else if (dynamic_cast<IStopWatch*>(e->obj))
					{
						this->subWeaponDef = SWDSTOPWATCH;
					}

					if (!item->isDestroyed)
					{
						item->SetDestroy();
					}
				}
			}
			else if (dynamic_cast<Entry*>(e->obj)) {
				DebugOut(L"Entry \n");
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;

				(e->obj)->isDestroyed = true;
				this->isActack = false; // còn đánh thì dừng để k bị lock control
				ResetSpriteFrame();
				ResetActack_Time();
				this->SetAutoWalk(true);
				SetState(SIMON_STATE_WALKING_RIGHT);
				break; // khong xet tiep va cham voi cac object khac
			}
			else if (dynamic_cast<MoneyBagTrigger*>(e->obj)) {
				DebugOut(L"Money bag \n");
				MoneyBagTrigger* trigger = dynamic_cast<MoneyBagTrigger*>(e->obj);
				trigger->isDestroyed = true;
				if (this->isAutoWalk) return;
				if (e->ny != 0) vy = 0;
				x += dx;
				trigger->SpawnMoneyBag();
				DebugOut(L"spawn money bag");

			}
			else if (dynamic_cast<NextScene*>(e->obj)) {
				NextScene* nextscene = dynamic_cast<NextScene*>(e->obj);
				nextscene->SetColliceWithPlayer(true);
			}
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	for (std::size_t i = 0; i < coObjects->size(); i++)
	{

		LPGAMEOBJECT e = coObjects->at(i);
		if (dynamic_cast<Item*>(e))
		{

			Item* f = dynamic_cast<Item*> (e);

			if (!f->CheckisHiding())
			{
				if (CGameObject::IsColliding(this, f))
				{
					if (!f->CheckisHiding())
					{
						this->AddEnery(f->GetHeartPoint());
					}
					if (dynamic_cast<MorningStar*>(e)) {
						SetState(SIMON_STATE_POWERUP);
						if (isActack) {
							ResetActack_Time();
							isActack = false;
						}
						StartPowerUp();
					}
					else if (dynamic_cast<DaggerItem*>(e))
					{
						this->subWeaponDef = SWDDAGGER;
					}
					else if (dynamic_cast<AxeItem*>(e))
					{
						this->subWeaponDef = SWDAXE;
					}
					else if (dynamic_cast<IStopWatch*>(e))
					{
						this->subWeaponDef = SWDSTOPWATCH;
					}

					//DebugOut(L"aabb \n");
					if (!f->CheckDestroyed()) {
						f->SetDestroy();
					}

				}
			}


		}
		else if (dynamic_cast<StairTrigger*>(e)) {
			StairTrigger* f = dynamic_cast<StairTrigger*> (e);

			if (CGameObject::IsColliding(this, f))
			{
				if (!this->isColliceWithStair) {
					if (this->isOnStair) {

						SetState(SIMON_STATE_IDLE);
						this->isOnStair = false;
						this->startOnStair = false;
						this->isFirstStepOnStair = false;
						this->isActack = false;
						return;


					}
					this->isColliceWithStair = true;
					this->onStairDirection = static_cast<STAIRDIRECTION>(f->GetDirection());
					DebugOut(L"ColliceWithStair \n");
					DebugOut(L"stepOnStairDirection=%d \n", this->onStairDirection);
					this->stairPos = { f->x,f->y };
					f->SetActive(true);
					return;
				}
			}
			else if (f->CheckActive())
			{
				f->SetActive(false);
				this->isColliceWithStair = false;
				if (!this->isOnStair)
					this->onStairDirection = STAIRDIRECTION::DEFAULT; //reset
				DebugOut(L"stop collice \n");
			}
		}
		else if (dynamic_cast<Enemy*>(e))
		{
			Enemy* f = dynamic_cast<Enemy*>(e);
			if (CGameObject::IsColliding(this, f))
			{
				if (untouchable_start == 0) {

					DebugOut(L"Collice with enemy \n", this->vy, this->vx);
					if (!this->isOnStair)
					{
						this->SetState(SIMON_STATE_DEFLECT);
						CGameObject::Update(dt); // cap nhat lai dx dy
						x += dx;
						y += dy;
					}
					if (untouchable != 1)
						StartUntouchable();

					DebugOut(L"Va cham vy=%f vx=%f \n", this->vy, this->vx);

				}
				else if (e->nx == DIRECTION::DEFAULT) {
					y += dy;
				}
			}
		}
	}


	if (state == SIMON_STATE_STAND_ATTACK
		|| state == SIMON_STATE_UPSTAIR_ATTACK
		|| state == SIMON_STATE_DOWNSTAIR_ATTACK) {

		whip->SetWhipPosition(x - 1.5 * SIMON_SPRITE_BOX_WIDTH, y);
	}

	else if (state == SIMON_STATE_SIT_ATTACK)
	{
		whip->SetWhipPosition(x - 1.5 * SIMON_SPRITE_BOX_WIDTH, y + SIMON_SPRITE_BOX_HEIGHT / 4);
	}

	if (this->isUseSubWeapon)
	{
		if (!this->isSpawnSubWeapon)
		{
			if (this->subWeaponDef == SWDSTOPWATCH)
			{
				this->AddEnery(-5);
			}
			else
			{
				this->AddEnery(-1);
			}
			HandleSpawnSubWeapon::GetInstance()->SpawnSubWeapon(this->subWeaponDef, this->x, this->y, this->nx);
			this->isSpawnSubWeapon = true;
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
	else if (state == SIMON_STATE_DOWNSTAIR_IDLE) {
		ani = SIMON_ANI_IDLE_DOWNSTAIR;
		Renderer(ani);
		return;
	}
	else if (state == SIMON_STATE_DOWNSTAIR_RIGHT || state == SIMON_STATE_DOWNSTAIR_LEFT) {
		ani = SIMON_ANI_STEP_DOWNSTAIR;
		Renderer(ani);
		return;
	}
	else if (state == SIMON_STATE_UPSTAIR_RIGHT || state == SIMON_STATE_UPSTAIR_LEFT) {
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
		if (!this->isUseSubWeapon)
		{
			whip->Render();
		}

		Renderer(ani);
		return;
	}
	else if (state == SIMON_STATE_UPSTAIR_ATTACK) {
		ani = SIMON_ANI_UPSTAIR_ATTACK;
		if (!this->isUseSubWeapon)
		{
			whip->Render();
		}

		Renderer(ani);
		return;
	}
	else if (state == SIMON_STATE_DOWNSTAIR_ATTACK) {
		ani = SIMON_ANI_DOWNSTAIR_ATTACK;
		if (!this->isUseSubWeapon)
		{
			whip->Render();
		}

		Renderer(ani);
		return;
	}
	else if (state == SIMON_STATE_SIT_ATTACK) {

		ani = SIMON_ANI_SIT_ATTACK;
		if (!this->isUseSubWeapon)
		{
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
		ani = 0;
	else
	{
		if (vx == 0)
		{
			if (nx == DIRECTION::RIGHT) ani = SIMON_ANI_IDLE;
			else if (nx == DIRECTION::LEFT)ani = SIMON_ANI_IDLE;
		}
		else if (vx > 0)
			ani = SIMON_ANI_WALKING;
		else ani = SIMON_ANI_WALKING;
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
		if (this->isAutoWalk) {
			vx = SIMON_AUTOWALKING_SPEED;
		}
		else
			vx = SIMON_WALKING_SPEED;
		nx = DIRECTION::RIGHT;
		break;
	case SIMON_STATE_WALKING_LEFT:
		if (this->isAutoWalk) {
			vx = -SIMON_AUTOWALKING_SPEED;
		}
		else
			vx = -SIMON_WALKING_SPEED;
		nx = DIRECTION::LEFT;
		break;
	case SIMON_STATE_JUMP:
	{
		vy = -SIMON_JUMP_SPEED_Y;
		isJumping = true;
		break;
	}
	case SIMON_STATE_UPSTAIR_RIGHT: {
		vy = -SIMON_UPSTAIR_VELOCITY;
		vx = SIMON_UPSTAIR_VELOCITY;
		nx = DIRECTION::RIGHT;
		break;
	}
	case SIMON_STATE_DOWNSTAIR_RIGHT: {
		vy = SIMON_UPSTAIR_VELOCITY;
		vx = SIMON_UPSTAIR_VELOCITY;
		nx = DIRECTION::RIGHT;
		break;
	}
	case SIMON_STATE_UPSTAIR_LEFT: {
		nx = DIRECTION::LEFT;
		vy = -SIMON_UPSTAIR_VELOCITY;
		vx = -SIMON_UPSTAIR_VELOCITY;
		break;
	}
	case SIMON_STATE_DOWNSTAIR_LEFT: {
		DebugOut(L"State SIMON_STATE_DOWNSTAIR_LEFT \n");
		nx = DIRECTION::LEFT;
		vy = SIMON_UPSTAIR_VELOCITY;
		vx = -SIMON_UPSTAIR_VELOCITY;
		break;
	}
	case SIMON_STATE_DOWNSTAIR_IDLE:
	{
		DebugOut(L"State SIMON_STATE_DOWNSTAIR_IDLE \n");
		this->isActack = false;
		this->isOnStair = true;
		this->isFirstStepOnStair = true; // dung` khi set state mac dinh cua simon
		this->startOnStair = false; // cho phép nhấn tiếp
		if (nx == DIRECTION::RIGHT)
		{
			this->onStairDirection = STAIRDIRECTION::DOWNRIGHT;
		}
		else if (nx == DIRECTION::LEFT)
		{
			this->onStairDirection = STAIRDIRECTION::DOWNLEFT;
		}
		if (this->lastState != SIMON_STATE_UPSTAIR_ATTACK
			&& this->lastState != SIMON_STATE_DOWNSTAIR_ATTACK)
		{
			this->LastStepOnStairPos = { floor(this->x),floor(this->y) };
		}
		else
		{
			this->lastState = -1;
		}
		vx = 0;
		vy = 0;
		break;
	}
	case SIMON_STATE_UPSTAIR_IDLE: {
		this->isActack = false;
		this->isOnStair = true;
		this->isFirstStepOnStair = true; // dung` khi set state mac dinh cua simon
		this->startOnStair = false; // cho phép nhấn tiếp
		//tránh trường hợp khi simon attack y thay đổi làm floor
		// làm tròn xuống 1px
		if (nx == DIRECTION::RIGHT)
		{
			this->onStairDirection = STAIRDIRECTION::UPRIGHT;
		}
		else if (nx == DIRECTION::LEFT)
		{
			this->onStairDirection = STAIRDIRECTION::UPLEFT;
		}
		if (this->lastState != SIMON_STATE_DOWNSTAIR_ATTACK
			&& this->lastState != SIMON_STATE_UPSTAIR_ATTACK)
		{
			this->LastStepOnStairPos = { floor(this->x),floor(this->y) };
		}
		else
		{
			this->lastState = -1;
		}

		DebugOut(L" LastStepOnStairPos x=%f y=%f", LastStepOnStairPos.x, LastStepOnStairPos.y);
		vx = 0;
		vy = 0;
		break;
	}

	case SIMON_STATE_POWERUP: {
		vx = 0;
		vy = 0;
		if (this->isActack)
		{
			this->isActack = false;
			ResetSpriteFrame();
			ResetActack_Time();
		}
		break;
	}
	case SIMON_STATE_STAND_ATTACK:
	{
		if (!this->isJumping) vx = 0;
		break;
	}
	case SIMON_STATE_UPSTAIR_ATTACK:
	{
		this->isOnStair = true;
		this->isFirstStepOnStair = true; // dung` khi set state mac dinh cua simon
		this->vx = 0;
		this->vy = 0;

		break;
	}
	case SIMON_STATE_DOWNSTAIR_ATTACK: {
		this->isOnStair = true;
		this->isFirstStepOnStair = true; // dung` khi set state mac dinh cua simon
		this->vx = 0;
		this->vy = 0;
		break;
	}
	case SIMON_STATE_DEFLECT:
	{
		DebugOut(L"Simon start DEFLECT \n");
		if (this->isActack)
		{
			this->isActack = false;
			ResetSpriteFrame();
			ResetActack_Time();
		}
		this->vy = -SIMON_DEFLECT_SPEED_Y;
		this->vx = -SIMON_DEFLECT_SPEED_X;

		break;
	}
	case SIMON_STATE_SIT_ATTACK:
	case SIMON_STATE_SIT:
	case SIMON_STATE_IDLE:
		this->vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;

	}
}

void CSimon::SimonUseSubWeapon()
{


}

void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 13;
	top = y;
	right = left + SIMON_BIG_BBOX_WIDTH - 2;
	bottom = top + SIMON_BIG_BBOX_HEIGHT;
}

