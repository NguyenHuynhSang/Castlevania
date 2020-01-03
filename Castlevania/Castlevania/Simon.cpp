#include <algorithm>
#include "debug.h"
#include "Simon.h"
#include "Game.h"
#include"Brick.h"
#include"Ground.h"
#include"Torch.h"
#include"Item.h"
#include"Entry.h"
#include"NextScene.h"
#include"PlayScene.h"
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
#include"Cross.h"
#include"HandleSpawnSubWeapon.h"
#include"PhantomBat.h"
#include"IHolyWater.h"
#include"PorkChop.h"
#include"MultiplyShotItem.h"
#include"BossZone.h"
#include"InvisibilityPotion.h"
#include "MoneyBag.h"
#include"Crystal.h"
#include"Sound.h"
CSimon::CSimon() :CGameObject()
{
	this->hp_ = 16;
	CSimon::score_ = 0;
	this->enery_ = 5;
	untouchable = 0;
	shotState = ShotState::NORMALSHOT;
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
	this->AddAnimation("SIMON_ANI_DIE", false); //13


}


int CSimon::score_ = 0;

CSimon::~CSimon()
{
	delete whip;
}
void CSimon::Renderer(int ani)
{
	int alpha = 255;
	if (untouchable) alpha = 128;
	animations[ani]->Render(nx, x, y, alpha);

	//	RenderBoundingBox();

}

void CSimon::HandleFirstStepOnStair()
{
	if (onStairDirection == STAIRDIRECTION::DEFAULT) {
		DebugOut(L"Return \n");
		return;
	}
	//reset vx vy remain from last state
	this->vx = 0;
	this->vy = 0;
	if (state == SIMON_STATE_WALKING_LEFT)
	{
		int a = 2;
	}
	DebugOut(L"HandleFirstStepOnStair \n");
	//up right first step

	if (onStairDirection == STAIRDIRECTION::UPRIGHT) {
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
	

	if (this->state == SIMON_STATE_DIE)
	{
		return;
	}


	// Calculate dx, dy 
	CGameObject::Update(dt);


	
	if (this->isActack && !this->isAutoWalk) {

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
				this->state = SIMON_STATE_IDLE; // use set state insteal of SetState() prevent set vx=0
			}
			whip->ResetLastFrame();
			ResetSpriteFrame();
			ResetActack_Time();
			this->animations[SIMON_ANI_STAND_ATTACK]->ResetAnimation();
			this->animations[SIMON_ANI_SIT_ATTACK]->ResetAnimation();
			this->animations[SIMON_ANI_UPSTAIR_ATTACK]->ResetAnimation();
			this->animations[SIMON_ANI_DOWNSTAIR_ATTACK]->ResetAnimation();

		}

		whip->SetVelocity(this->vx, this->vy);
		whip->SetDirection(this->nx);
		whip->Update(dt, CSimon::score_, coObjects);

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
		&& state != SIMON_STATE_DOWNSTAIR_ATTACK
		)
	{
		vy += SIMON_GRAVITY * dt;
	}
	if (isJumping == true && vy > 0.7f)
	{
		SetState(SIMON_STATE_FALL_DOWN);
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
	if (this->paralyze_start != 0) {
		if (GetTickCount() - paralyze_start > SIMON_PARALYZE_TIME)
		{
			this->SetState(SIMON_STATE_IDLE);
			this->paralyze_start = 0;
		}

	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{

		float min_tx, min_ty, nx = 0, ny=-1;

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
					if (this->hp_ == 0)
					{
						this->SetState(SIMON_STATE_DIE);
						this->isOnStair = false;
						break;
					}
					if (this->isOnStair) {
						x += dx;
						y += dy;

					}
					else
						if (this->state == SIMON_STATE_DEFLECT) {
							this->state = SIMON_STATE_IDLE;
							this->isJumping = false;
						}
						else {
						

							if (this->isActack || this->isUseSubWeapon) { // còn đang đánh thì dừng lại
								vx = 0;
							}
							if (state == SIMON_STATE_FALL_DOWN && this->paralyze_start == 0) {
								this->isActack = false; // còn đánh thì dừng để k bị lock control
								ResetSpriteFrame();
								ResetActack_Time();
								DebugOut(L"Simon vy=%f \n", this->vy);
								if (vy>1.0f || isJumping == true)								{
									this->paralyze_start = GetTickCount();
									Sound::GetInstance()->Play(eSound::soundFallDown);
									if (isActack)
									{
										isActack = false;
									}
								}
								else if (isJumping==false)
								{
									SetState(SIMON_STATE_IDLE);
									isActack = false;
								}	
							};
							this->isJumping = false;
							if (ny != 0) vy = 0;
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

				
				HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_BUBBLE, this->x, this->y);
				this->vy = 10.0f;
				CGameObject::Update(dt); // cap nhat lai dx dy theo van toc moi
			
				this->SetState(SIMON_STATE_DIE);
				Sound::GetInstance()->Play(eSound::soundFallingDownWaterSurface);
				if (e->nx != 0)
				{
					x += dx;
				}
				else if (e->ny != 0)
				{
					y += dy;
				}
				break;
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
					if (this->hp_ == 0)
					{
						this->SetState(SIMON_STATE_DIE);
						this->isOnStair = false;
						break;
					}
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
			else if (dynamic_cast<Door*>(e->obj))
			{


				if (e->nx < 0)
				{
					Door* door = dynamic_cast<Door*>(e->obj);
					if (door->GetState() == DOOR_STATE_CLOSE && !this->isJumping)
					{
						door->SetIsColicePlayer(true);
						this->SetState(SIMON_STATE_IDLE);
						this->isHitDoor = true;
						this->lockControl = true;
					}
				}


			}
			else if (dynamic_cast<BossZone*>(e->obj)) {
				BossZone* bossZone = dynamic_cast<BossZone*>(e->obj);
				bossZone->DestroyImmediate();
				this->isFightWithBoss = true;

			}
			else if (dynamic_cast<Enemy*>(e->obj)) {
				Enemy* enemy = dynamic_cast<Enemy*>(e->obj);
				if (dynamic_cast<Bat*> (e->obj))
				{
					Bat* bat = dynamic_cast<Bat*> (e->obj);
					bat->SubtractHP(1);
					if (bat->GetHp() == 0)
					{
						bat->SetDestroy();
					}
				}


				if (untouchable_start == 0) {

					if (!this->isOnStair)
					{
						this->SetState(SIMON_STATE_DEFLECT);
						x += dx;
						y += dy;
					}
					if (untouchable != 1) {
						StartUntouchable();
						this->AddHP(-2); //TEST
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
						y += dy;
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
						
						SetState(SIMON_STATE_POWERUP);
						if (isActack) {
							ResetActack_Time();
							isActack = false;
						}
						StartPowerUp();
					}
					else
					{
						Sound::GetInstance()->Play(eSound::soundCollectItem);
						if (dynamic_cast<DaggerItem*>(e->obj))
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
						else if (dynamic_cast<Cross*>(e->obj)) {
							this->getCross = true;
						}
						else if (dynamic_cast<IHolyWater*>(e->obj)) {
							this->subWeaponDef = SWDHOLLYWATER;
						}
						else if (dynamic_cast<PorkChop*>(e->obj)) {
							AddHP(4);
						}
						else if (dynamic_cast<MultiplyShotItem*>(e->obj)) {
							shotState = ShotState::DOUBLESHOT;
						}
						else if (dynamic_cast<InvisibilityPotion*>(e->obj)) {
							StartUntouchable();
							DebugOut(L"start untouchh swepaabb \n");
						}
						else if (dynamic_cast<MoneyBag*>(e->obj)) {
							score_ += item->GetScore();
						}
						else if (dynamic_cast<Crystal*>(e->obj)) {
							Sound::GetInstance()->StopAll();
							Sound::GetInstance()->Play(eSound::musicStateClear);

						}
					}
					if (!item->isDestroyed)
					{
						item->SetDestroy();
					}
				}
			}
			else if (dynamic_cast<Entry*>(e->obj)) {
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
				MoneyBagTrigger* trigger = dynamic_cast<MoneyBagTrigger*>(e->obj);
				trigger->isDestroyed = true;
				if (this->isAutoWalk) return;
				if (e->ny != 0) vy = 0;
				x += dx;
				trigger->SpawnMoneyBag();

			}
			else if (dynamic_cast<NextScene*>(e->obj)) {
				NextScene* nextscene = dynamic_cast<NextScene*>(e->obj);
				nextscene->SetColliceWithPlayer(true);
			}
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


	bool flagOnGround = false;
	for (std::size_t i = 0; i < coObjects->size(); i++)
	{

		LPGAMEOBJECT e = coObjects->at(i);
		if (dynamic_cast<Ground*>(e) && !flagOnGround) // BUG khi đứng lên brick
		{
			Ground* f = dynamic_cast<Ground*> (e);

			float l, t, r, b, el, et, er, eb;
			this->GetBoundingBox(l, t, r, b);
			b = b + 15; // hehehe offset 5pixel
			f->GetBoundingBox(el, et, er, eb);
			if (CGameObject::AABB(l, t, r, b, el, et, er, eb))
			{
				flagOnGround = true;
			}
		}
		if (dynamic_cast<CBrick*>(e) && !flagOnGround) // BUG khi đứng lên brick
		{
			CBrick* f = dynamic_cast<CBrick*> (e);

			float l, t, r, b, el, et, er, eb;
			this->GetBoundingBox(l, t, r, b);
			b = b + 15; // hehehe offset 5pixel
			f->GetBoundingBox(el, et, er, eb);
			if (CGameObject::AABB(l, t, r, b, el, et, er, eb))
			{
				flagOnGround = true;

			}
		}
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
					else
					{
						if (Sound::GetInstance()->isPlaying(soundCollectItem))
						{
							Sound::GetInstance()->Stop(soundCollectItem);
						}
						Sound::GetInstance()->Play(eSound::soundCollectItem);
						if (dynamic_cast<DaggerItem*>(e))
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
						else if (dynamic_cast<Cross*>(e)) {
							this->getCross = true;
						}
						else if (dynamic_cast<IHolyWater*>(e)) {
							this->subWeaponDef = SWDHOLLYWATER;
						}
						else if (dynamic_cast<InvisibilityPotion*>(e)) {
							StartUntouchable();
						}
						else if (dynamic_cast<PorkChop*>(e)) {
							AddHP(4);
						}
						else if (dynamic_cast<MoneyBag*>(e)) {
							score_ += f->GetScore();
						}
						else if (dynamic_cast<MultiplyShotItem*>(e)) {
							shotState = ShotState::DOUBLESHOT;
						}
						else if (dynamic_cast<Crystal*>(e)) {
							Sound::GetInstance()->StopAll();
							Sound::GetInstance()->Play(eSound::musicStateClear);
						}
					}

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
			}
		}
		else if (dynamic_cast<Enemy*>(e))
		{
			Enemy* f = dynamic_cast<Enemy*>(e);
			if (CGameObject::IsColliding(this, f))
			{
				if (dynamic_cast<Bat*> (e))
				{
					Bat* bat = dynamic_cast<Bat*> (e);
					bat->SubtractHP(1);
					if (bat->GetHp() == 0)
					{
						bat->SetDestroy();
					}
				}

				if (untouchable_start == 0) {

					DebugOut(L"Collice with enemy \n", this->vy, this->vx);
					if (!this->isOnStair)
					{
						this->SetState(SIMON_STATE_DEFLECT);
						x += dx;
						y += dy;
					}
					if (untouchable != 1) {
						StartUntouchable();
						this->AddHP(-2); //TEST
					}
				}
				else if (e->nx == DIRECTION::DEFAULT) {
					y += dy;
				}
			}
		}


	}


	if (!flagOnGround)
	{
		if (!isJumping && !isFirstStepOnStair && !isOnStair 
			&& this->state != SIMON_STATE_DEFLECT
			&& this->state != SIMON_STATE_DIE
			&& this->state != SIMON_STATE_FALL_DOWN) {
			SetState(SIMON_STATE_FALL_DOWN);

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
	else if (state == SIMON_STATE_SIT || state == SIMON_STATE_JUMP || state == SIMON_STATE_FALL_DOWN) {
		ani = SIMON_ANI_SITTING;
		Renderer(ani);
		return;
	}
	else if (state == SIMON_STATE_DIE) {
		ani = SIMON_ANI_DIE;
		Renderer(ani);
		return;
	}

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



void CSimon::SetState(int state, bool chanegSimonattribute)
{
	this->paralyze_start = 0;
	CGameObject::SetState(state);
	if (!chanegSimonattribute)
	{
		return;
	}
	switch (state)
	{
	case SIMON_STATE_DIE:
		Sound::GetInstance()->Play(eSound::musicLifeLost);
		this->vx = 0;
		this->vy = 0;
		break;
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

		//DebugOut(L" LastStepOnStairPos x=%f y=%f", LastStepOnStairPos.x, LastStepOnStairPos.y);
		vx = 0;
		vy = 0;
		break;
	}

	case SIMON_STATE_POWERUP: {
		vx = 0;
		Sound::GetInstance()->Play(eSound::soundCollectWeapon);
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
		whip->StartCalculatorCollice();
		break;
	}
	case SIMON_STATE_UPSTAIR_ATTACK:
	{
		this->isOnStair = true;
		this->isFirstStepOnStair = true; // dung` khi set state mac dinh cua simon
		this->vx = 0;
		this->vy = 0;
		whip->StartCalculatorCollice();
		break;
	}
	case SIMON_STATE_DOWNSTAIR_ATTACK: {
		this->isOnStair = true;
		this->isFirstStepOnStair = true; // dung` khi set state mac dinh cua simon
		this->vx = 0;
		whip->StartCalculatorCollice();
		this->vy = 0;
		break;
	}
	case SIMON_STATE_DEFLECT:
	{
		Sound::GetInstance()->Play(eSound::soundHurting);
		DebugOut(L"Simon start DEFLECT \n");
		if (this->isActack)
		{
			this->isActack = false;
			ResetSpriteFrame();
			ResetActack_Time();
		}
		this->vy = -SIMON_DEFLECT_SPEED_Y;
		if (nx == DIRECTION::LEFT)
		{
			this->vx = SIMON_DEFLECT_SPEED_X;
		}
		else
		{
			this->vx = -SIMON_DEFLECT_SPEED_X;
		}


		break;
	}
	case SIMON_STATE_SIT_ATTACK:
	{
		whip->StartCalculatorCollice();
		this->vx = 0;
		break;

	}
	case SIMON_STATE_FALL_DOWN: {
		this->vx = 0;
		this->vy = SIMON_FALLDOWN_VY;
		DebugOut(L"Simon falldown \n");
		break;
	}
	case SIMON_STATE_SIT:
	case SIMON_STATE_IDLE:
		this->vx = 0;
		break;
	}
}

void CSimon::SimonUseSubWeapon()
{


}

void CSimon::StartUseSubWeapon()
{

	if (this->subWeaponDef == SWDSTOPWATCH && this->enery_ < 5)
	{
		return;
	}
	else if (this->enery_ < 1)
	{
		return;
	}

	switch (shotState)
	{
	case NORMALSHOT:
		if (HandleSpawnSubWeapon::GetInstance()->CheckNumOfSubWeaponUsed() == 1)
		{
			return;
		}
		break;
	case DOUBLESHOT:
		if (HandleSpawnSubWeapon::GetInstance()->CheckNumOfSubWeaponUsed() == 2)
		{
			return;
		}
		break;
	case TRIPBLESHOT:
		break;
	default:
		break;
	}
	



	if (this->CheckIsOnStair())
	{
		if (this->state == SIMON_STATE_UPSTAIR_IDLE)
		{
			this->animations[SIMON_ANI_UPSTAIR_ATTACK]->ResetAnimation();
			this->animations[SIMON_ANI_DOWNSTAIR_ATTACK]->ResetAnimation();
			if (this->subWeaponDef != SWDSTOPWATCH)
			{
				SetState(SIMON_STATE_UPSTAIR_ATTACK);
			}
			this->attack_start = GetTickCount();
			this->isUseSubWeapon = true;

		}
		else if (this->state == SIMON_STATE_DOWNSTAIR_IDLE)
		{
			this->animations[SIMON_ANI_UPSTAIR_ATTACK]->ResetAnimation();
			this->animations[SIMON_ANI_DOWNSTAIR_ATTACK]->ResetAnimation();
			if (this->subWeaponDef != SWDSTOPWATCH)
			{
				SetState(SIMON_STATE_DOWNSTAIR_ATTACK);
			}
			this->attack_start = GetTickCount();
			this->isUseSubWeapon = true;
		}
	}
	else
	{
		if (this->subWeaponDef != SWDSTOPWATCH)
		{
			SetState(SIMON_STATE_STAND_ATTACK);
		}

		this->attack_start = GetTickCount();
		this->isUseSubWeapon = true;
	}


}

void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	top = y;
	if (isOnStair)
	{
		top = y + 2;

	}
	bottom = top + SIMON_BIG_BBOX_HEIGHT;
	left = x + 13;
	right = left + SIMON_BIG_BBOX_WIDTH - 2;
}

