#include "PhantomBat.h"
#include"Simon.h"
#include"HandleSpawnEnemy.h"
void PhantomBat::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x+35;
	t = y;

	if (this->state == VAMPIREBAT_STATE_SLEEP)
	{
		l = x + 120;
		b = t + 250;// for test
	}
	else
	{
		b = t + VAMPIREBAT_BBOX_HEIGHT;
	}
	r = l + VAMPIREBAT_BBOX_WIDTH;
}

void PhantomBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (awake)
	{
		if (!this->intro)
		{
			this->SetState(VAMPIREBAT_STATE_IDLE);
			DebugOut(L"awake \n");
			if (attack_start ==0)
			{
				attack_start = GetTickCount();
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
		this->attack_start = 0;
		float targetX = this->activeArea.left + rand() % (this->activeArea.right - this->activeArea.left);
		float tagetY = this->activeArea.top + rand() % (this->activeArea.bottom - this->activeArea.top-100);

		this->vx = (targetX - x) / VAMPIREBAT_FLY_BACK_TIME;
		this->vy = (tagetY - y) / VAMPIREBAT_FLY_BACK_TIME;


	}

	if (waiting_start != 0 && GetTickCount() - waiting_start > this->waiting_time)
	{
	
		this->waiting_start = 0;
	}
	else if (waiting_start != 0)
	{
		if (this->outOfArea)
		{
			DIRECTION nx;
			float fireBall_vy = ((t+(b-t)/2) - y) / 1000;
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

	this->slowAttackArea.left = x - (VAMPIREBAT_BBOX_SLOWACTACK - VAMPIREBAT_SPRITE_BBOX_WIDTH) / 2;
	this->slowAttackArea.top = y - (VAMPIREBAT_BBOX_SLOWACTACK - VAMPIREBAT_SPRITE_BBOX_HEIGHT) / 2;
	this->slowAttackArea.right = this->slowAttackArea.left + VAMPIREBAT_BBOX_SLOWACTACK;
	this->slowAttackArea.bottom = this->slowAttackArea.top + VAMPIREBAT_BBOX_SLOWACTACK;
	this->fastAttackArea.left = x - (VAMPIREBAT_BBOX_FASTACTACK - VAMPIREBAT_SPRITE_BBOX_WIDTH) / 2;
	this->fastAttackArea.top = y - (VAMPIREBAT_BBOX_FASTACTACK - VAMPIREBAT_SPRITE_BBOX_HEIGHT) / 2;
	this->fastAttackArea.right = this->fastAttackArea.left + VAMPIREBAT_BBOX_FASTACTACK;
	this->fastAttackArea.bottom = this->fastAttackArea.top + VAMPIREBAT_BBOX_FASTACTACK;
	if (this->attack_start==0 &&this->flyback_start==0 && this->flyback_start==0)
	{
		if (CGameObject::AABB(l, t, r, b, this->slowAttackArea.left, this->slowAttackArea.top, this->slowAttackArea.right, this->slowAttackArea.bottom))
		{
			this->vx = -(this->x - l) / VAMPIREBAT_ATTACKSLOW_TIME;
			this->vy = -(this->y - t) / VAMPIREBAT_ATTACKSLOW_TIME;
			targer = { (long)l,(long)t,(long)r,(long)b };
			this->attack_start = GetTickCount();
			this->attack_time = VAMPIREBAT_ATTACKSLOW_TIME;
		}
		else  if (CGameObject::AABB(l, t, r, b, this->fastAttackArea.left, this->fastAttackArea.top, this->fastAttackArea.right, this->fastAttackArea.bottom))
		{
			this->vx = -(this->x - l) / VAMPIREBAT_ATTACKFAST_TIME;
			this->vy = -(this->y - t) / VAMPIREBAT_ATTACKFAST_TIME;
			targer = { (long)l,(long)t,(long)r,(long)b };
			this->attack_start = GetTickCount();
			this->attack_time = VAMPIREBAT_ATTACKFAST_TIME;
		}
		else
		{
			this->attack_start = GetTickCount();
			this->outOfArea = true;
		}
	}
	if (this->attack_start != 0 && GetTickCount() - this->attack_start > this->attack_time)
	{

		this->attack_start = 0;
		if (this->flyback_start == 0)
		{
			this->flyback_start = GetTickCount();
		}
	
		float tagetY = this->activeArea.top + rand() % (this->activeArea.bottom - this->activeArea.top-80);
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
	RenderActiveBox(this->slowAttackArea, MYCOLOR::BLUE, 100);
	RenderActiveBox(this->fastAttackArea, MYCOLOR::RED);
}

PhantomBat::PhantomBat() :Enemy()
{
	AddAnimation("VAMPIREBAT_ANI_SLEEP");
	AddAnimation("VAMPIREBAT_ANI_FLYING");
	this->state = VAMPIREBAT_STATE_SLEEP;
	this->attack_time = VAMPIREBAT_ATTACKSLOW_TIME;
	this->waiting_start = 0;
	this->attack_start = 0;
	this->flyback_start = 0;
	this->hp = DEFAULT_HP;
}

PhantomBat::~PhantomBat()
{
}
