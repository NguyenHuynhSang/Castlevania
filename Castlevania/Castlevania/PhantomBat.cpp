#include "PhantomBat.h"
#include"Simon.h"
#include"HandleSpawnEnemy.h"
#include"HandleSpawnEffects.h"
void PhantomBat::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x+35;
	t = y;
	r = l + VAMPIREBAT_BBOX_WIDTH;
	b = t + VAMPIREBAT_BBOX_HEIGHT;
}

void PhantomBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroyed)
	{
		return;
	}
	if (this->setDestroy)
	{
		HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_BOSSDEAD, x, y);
		this->isDestroyed = true;
		return;
	}
	if (awake)
	{
		if (!this->intro)
		{
			this->SetState(VAMPIREBAT_STATE_IDLE);
			DebugOut(L"awake \n");
			if (fly_start ==0)
			{
				fly_start = GetTickCount();
				this->intro = true;
			}
		}
	
	}
	else
	{
		return;
	}

	RECT targer = { 0,0,0,0 };
	float l = 0, t = 0, r = 0, b = 0;
	for (size_t i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CSimon*>(coObjects->at(i)))
		{
			CSimon* simon = dynamic_cast<CSimon*>(coObjects->at(i));
			simon->GetBoundingBox(l, t, r, b);
		}

	}

	CGameObject::Update(dt);
	x += dx;
	y += dy;

	if (this->x<activeArea.left || (this->x + VAMPIREBAT_SPRITE_BBOX_WIDTH)>activeArea.right
		|| (this->y + VAMPIREBAT_SPRITE_BBOX_HEIGHT) > activeArea.bottom || this->y < activeArea.top)
	{

		if (this->flyback_start == 0)
		{
			this->flyback_start = GetTickCount();
		}
		this->fly_start = 0;


		//float targetX = this->activeArea.left + rand() % (this->activeArea.right - this->activeArea.left);
		float tagetY = this->activeArea.top + rand() % (this->activeArea.bottom - this->activeArea.top-100);

		this->vx = -this->vx;
		this->vy = (tagetY - y) / VAMPIREBAT_FLY_BACK_TIME;

		DebugOut(L"Boss fly reserve\n");
	}


	if (waiting_start != 0 && GetTickCount() - waiting_start > this->waiting_time)
	{
	
		this->waiting_start = 0;
	}
	else if (waiting_start != 0)
	{
		if (this->outOfArea) //bắn fireball
		{
			DIRECTION nx;
			float fireBall_vy = ((t+(b-t)/2) - y) / 1200;
			if ((x+35)>l+(r-l)/2)
			{
				nx = DIRECTION::LEFT;
			}
			else {
				nx = DIRECTION::RIGHT;
			}
			HandleSpawnEnemy::GetInstance()->SpawnFireBall(x+35, y, nx, fireBall_vy);
			this->outOfArea = false;

		}
		return;
	}


	this->bossAttackArea.left = x - (VAMPIREBAT_BBOX_FASTACTACK - VAMPIREBAT_SPRITE_BBOX_WIDTH) / 2;
	this->bossAttackArea.top = y - (VAMPIREBAT_BBOX_FASTACTACK - VAMPIREBAT_SPRITE_BBOX_HEIGHT) / 2;
	this->bossAttackArea.right = this->bossAttackArea.left + VAMPIREBAT_BBOX_FASTACTACK;
	this->bossAttackArea.bottom = this->bossAttackArea.top + VAMPIREBAT_BBOX_FASTACTACK;
	if (this->fly_start==0 &&this->flyback_start==0) // attack khi đang dừng
	{
		 if (CGameObject::AABB(l, t, r, b, this->bossAttackArea.left, this->bossAttackArea.top, this->bossAttackArea.right, this->bossAttackArea.bottom))
		{
			this->vx = (l-this->x) / VAMPIREBAT_ATTACK_TIME;
			this->vy = (t-this->y) / VAMPIREBAT_ATTACK_TIME;
			targer = { (long)l,(long)t,(long)r,(long)b };
			this->fly_start = GetTickCount();
			this->attack_time = VAMPIREBAT_ATTACK_TIME;

			DebugOut(L"Boss start attact \n");
		}
		else
		{
			this->fly_start = GetTickCount();
			this->outOfArea = true;
		}
	}
	if (this->fly_start != 0 && GetTickCount() - this->fly_start > this->attack_time)
	{
		DebugOut(L"Boss flyback \n");
		this->fly_start = 0;
		if (this->flyback_start == 0)
		{
			this->flyback_start = GetTickCount();
		}
	
		float tagetY = this->activeArea.top + rand() % (this->activeArea.bottom - this->activeArea.top-100);
		if (this->outOfArea)
		{
			float targetX = this->activeArea.left + rand() % (this->activeArea.right - this->activeArea.left);
			this->vx = (targetX - x) / VAMPIREBAT_FLY_BACK_TIME;
		}
		
		this->vy = (tagetY - y) / VAMPIREBAT_FLY_BACK_TIME;
	}
	if (this->flyback_start != 0 && GetTickCount() - this->flyback_start > VAMPIREBAT_FLY_BACK_TIME)
	{
	
		this->flyback_start = 0;
		DebugOut(L"Boss waiting\n");
		this->flyback_start = 0;
		if (this->waiting_start == 0)
		{

			waiting_start = GetTickCount();
			int rank = rand() % 2;
			if (rank == 1)
			{
				this->waiting_time = VAMPIREBAT_IDLE_TIME_LONG;
			}
			else
			{
				this->waiting_time = VAMPIREBAT_IDLE_TIME_SHORT;
			}
			this->vx = 0;
			this->vy = 0;
		}
	}
}

void PhantomBat::Render()
{
	int ani = 0;
	if (state == VAMPIREBAT_STATE_SLEEP)
	{
		ani = VAMPIREBAT_ANI_SLEEP;
	}
	else {
		ani = VAMPIREBAT_ANI_FLYING;
	}
	animations[ani]->Render(DIRECTION::DEFAULT, x, y);
	RenderBoundingBox();
	//RenderActiveBox(this->slowAttackArea, MYCOLOR::BLUE, 100);
	//RenderActiveBox(this->fastAttackArea, MYCOLOR::RED);
}

PhantomBat::PhantomBat() :Enemy()
{
	AddAnimation("VAMPIREBAT_ANI_SLEEP");
	AddAnimation("VAMPIREBAT_ANI_FLYING");
	this->state = VAMPIREBAT_STATE_SLEEP;
	this->attack_time = VAMPIREBAT_ATTACK_TIME;
	this->waiting_start = 0;
	this->fly_start = 0;
	this->flyback_start = 0;
	this->hp = DEFAULT_HP;
}

PhantomBat::~PhantomBat()
{
}
