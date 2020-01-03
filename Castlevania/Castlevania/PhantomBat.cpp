#include "PhantomBat.h"
#include"Simon.h"
#include"HandleSpawnEnemy.h"
#include"HandleSpawnEffects.h"
#include"HandleSpawnItem.h"
#include"Hud.h"
void PhantomBat::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
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
	Hud::SetBossHp(this->hp);
	if (this->setDestroy)
	{
		HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_BOSSDEAD, x, y);
		float cx, cy;
		cx = activeArea.left+abs(activeArea.right - activeArea.left) / 2;
		cy= activeArea.top+abs(activeArea.top - activeArea.bottom )/2;
		HandleSpawnItem::GetInstance()->SpawnItem(ITEMDEF::ITDCRYSTALL, cx, cy, true);
		this->isDestroyed = true;
		return;
	}
	if (awake)
	{
		if (!this->intro)
		{
			this->SetState(VAMPIREBAT_STATE_IDLE);
			DebugOut(L"awake \n");
			if (attack_start == 0)
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
		this->hitBoder = true;


		float tagetY = this->activeArea.top + rand() % (this->activeArea.bottom - this->activeArea.top - 100);

		float targetX = this->activeArea.left+60 + rand() % (this->activeArea.right - this->activeArea.left-200);
		DebugOut(L"Hit boder \n");
		if (this->x < activeArea.left)
		{
			this->vx = VAMPIREBAT_FLYBACK_VX;
		}
		else if (this->x >= activeArea.left)
		{
			this->vx = -VAMPIREBAT_FLYBACK_VX;
		}
	
		DWORD time = abs(targetX - x) / VAMPIREBAT_FLYBACK_VX;
		this->flyback_time = time;
		this->vy = (tagetY - y) / VAMPIREBAT_FLY_BACK_TIME;
	}


	if (waiting_start != 0 && GetTickCount() - waiting_start > this->waiting_time)
	{
		this->hitBoder = false;
		this->waiting_start = 0;
	}
	else if (waiting_start != 0)
	{

		if (this->outOfArea) //bắn fireball
		{
			DIRECTION nx;
			float fireBall_vy = ((t + (b - t) / 2) - y) / 1200;
			if ((x + 35) > l + (r - l) / 2)
			{
				nx = DIRECTION::LEFT;
			}
			else {
				nx = DIRECTION::RIGHT;
			}
			HandleSpawnEnemy::GetInstance()->SpawnFireBall(x + 35, y, nx, fireBall_vy);
			this->outOfArea = false;

		}
		return;
	}


	this->bossAttackArea.left = x - (VAMPIREBAT_BBOX_FASTACTACK - VAMPIREBAT_SPRITE_BBOX_WIDTH) / 2;
	this->bossAttackArea.top = y - (VAMPIREBAT_BBOX_FASTACTACK - VAMPIREBAT_SPRITE_BBOX_HEIGHT) / 2;
	this->bossAttackArea.right = this->bossAttackArea.left + VAMPIREBAT_BBOX_FASTACTACK;
	this->bossAttackArea.bottom = this->bossAttackArea.top + VAMPIREBAT_BBOX_FASTACTACK;
	if (this->attack_start == 0 && this->flyback_start == 0 && this->waiting_start == 0) // attack khi đang dừng
	{
		flyToRamdomTager = false;
		if (CGameObject::AABB(l, t, r, b, this->bossAttackArea.left, this->bossAttackArea.top, this->bossAttackArea.right, this->bossAttackArea.bottom))
		{
			this->vx = (l - this->x) / VAMPIREBAT_ATTACK_TIME;
			this->vy = (t - this->y) / VAMPIREBAT_ATTACK_TIME;
			targer = { (long)l,(long)t,(long)r,(long)b };
			this->attack_start = GetTickCount();
			this->attack_time = VAMPIREBAT_ATTACK_TIME;

			DebugOut(L"Boss start attact \n");
		}
		else
		{
			this->attack_start = GetTickCount();
			this->outOfArea = true;
		}
	}
	if (this->attack_start != 0 && GetTickCount() - this->attack_start > this->attack_time)
	{
		DebugOut(L"Boss flyback \n");
		this->attack_start = 0;
		if (this->flyback_start == 0)
		{
			this->flyback_start = GetTickCount();
		}

		float tagetY = this->activeArea.top + rand() % (this->activeArea.bottom - this->activeArea.top - 100);
		if (this->outOfArea)
		{
			float targetX = this->activeArea.left + rand() % (this->activeArea.right - this->activeArea.left);
			this->vx = (targetX - x) / VAMPIREBAT_FLY_BACK_TIME;
		}

		this->vy = (tagetY - y) / VAMPIREBAT_FLY_BACK_TIME;
	}
	if (this->flyback_start != 0 && GetTickCount() - this->flyback_start > this->flyback_time)
	{
		if (!this->hitBoder && !flyToRamdomTager)
		{
			this->flyback_start = GetTickCount();
			flyToRamdomTager = true;
			float tagetY = this->activeArea.top+20 + rand() % (this->activeArea.bottom - this->activeArea.top - 200);
			float targetX = this->activeArea.left+60 + rand() % (this->activeArea.right - this->activeArea.left - 200);
			if (this->x < (activeArea.left+abs(activeArea.left-activeArea.right) / 2))
			{
				this->vx = VAMPIREBAT_FLYBACK_VX;
			}
			else 
			{
				this->vx = -VAMPIREBAT_FLYBACK_VX;
			}

			DWORD time = abs(targetX - x) / VAMPIREBAT_FLYBACK_VX;
			this->flyback_time = time;
			this->vy = (tagetY - y) / VAMPIREBAT_FLY_BACK_TIME;
			DebugOut(L"Get new tagger \n");
			return;
		}
		this->flyback_start = 0;

		
		this->flyback_time = VAMPIREBAT_FLY_BACK_TIME;
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
	this->flyback_time = VAMPIREBAT_FLY_BACK_TIME;
	this->waiting_start = 0;
	this->attack_start = 0;
	this->flyback_start = 0;
	this->flyrandom_start = 0;
	this->hp = DEFAULT_HP;
}

PhantomBat::~PhantomBat()
{
}
