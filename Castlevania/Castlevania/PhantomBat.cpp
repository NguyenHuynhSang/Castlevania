#include "PhantomBat.h"
#include"Simon.h"
void PhantomBat::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
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
		this->SetState(VAMPIREBAT_STATE_IDLE);
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

	if (this->x<activeArea.left || (this->x + VAMPIREBAT_BBOX_WIDTH)>activeArea.right
		|| (this->y + VAMPIREBAT_BBOX_HEIGHT) > activeArea.bottom || this->y < activeArea.top)
	{

		if (this->flyback_start == 0)
		{
			this->flyback_start = GetTickCount();
		}
		float targetX = this->activeArea.left + rand() % (this->activeArea.right- this->activeArea.left);
		float tagetY = this->activeArea.top + rand() % (this->activeArea.bottom- this->activeArea.top);

		this->vx = (targetX - x) / VAMPIREBAT_FLY_BACK_TIME;
		this->vy = (tagetY - y) / VAMPIREBAT_FLY_BACK_TIME;
		this->flyToPos = true;
		this->isActack = false;

	}

	if (waiting_start != 0 && GetTickCount() - waiting_start > this->waiting_time)
	{
		this->isActack = false;
		this->flyToPos = false;
		this->waiting_start = 0;
	}
	else if(waiting_start != 0)
	{
		return;
	}
	float cx, cy;//center x,y
	this->slowActackArea.left = x - (VAMPIREBAT_BBOX_SLOWACTACK - VAMPIREBAT_BBOX_WIDTH) / 2;
	this->slowActackArea.top = y - (VAMPIREBAT_BBOX_SLOWACTACK - VAMPIREBAT_BBOX_HEIGHT) / 2;
	this->slowActackArea.right = this->slowActackArea.left + VAMPIREBAT_BBOX_SLOWACTACK;
	this->slowActackArea.bottom = this->slowActackArea.top + VAMPIREBAT_BBOX_SLOWACTACK;


	this->fastActackArea.left = x - (VAMPIREBAT_BBOX_FASTACTACK - VAMPIREBAT_BBOX_WIDTH) / 2;
	this->fastActackArea.top = y - (VAMPIREBAT_BBOX_FASTACTACK - VAMPIREBAT_BBOX_HEIGHT) / 2;
	this->fastActackArea.right = this->fastActackArea.left + VAMPIREBAT_BBOX_FASTACTACK;
	this->fastActackArea.bottom = this->fastActackArea.top + VAMPIREBAT_BBOX_FASTACTACK;


	if (!this->isActack && !this->flyToPos)
	{
		if (CGameObject::AABB(l, t, r, b, this->slowActackArea.left, this->slowActackArea.top, this->slowActackArea.right, this->slowActackArea.bottom))
		{
			this->vx = -(this->x - l) / VAMPIREBAT_ATTACKSLOW_TIME;
			this->vy = -(this->y - t) / VAMPIREBAT_ATTACKSLOW_TIME;
			this->isActack = true;
			targer = { (long)l,(long)t,(long)r,(long)b };
			this->attack_start = GetTickCount();
			this->attack_time = VAMPIREBAT_ATTACKSLOW_TIME;
		}
		else  if (CGameObject::AABB(l, t, r, b, this->fastActackArea.left, this->fastActackArea.top, this->fastActackArea.right, this->fastActackArea.bottom))
		{
			this->vx = -(this->x - l) / VAMPIREBAT_ATTACKFAST_TIME;
			this->vy = -(this->y - t) / VAMPIREBAT_ATTACKFAST_TIME;
			this->isActack = true;
			targer = { (long)l,(long)t,(long)r,(long)b };
			this->attack_start = GetTickCount();
			this->attack_time = VAMPIREBAT_ATTACKFAST_TIME;
		}
	}

	if (this->isActack)
	{
		if (GetTickCount() - this->attack_start > this->attack_time)
		{
			if (!this->flyToPos)
			{
				if (this->flyback_start == 0)
				{
					this->flyback_start = GetTickCount();
				}
				float targetX = x;
				while (abs(targetX-x)>100)
				{
					float targetX = this->activeArea.left + rand() % (this->activeArea.right - this->activeArea.left);
				}
				
	
				float tagetY = this->activeArea.top + rand() % (this->activeArea.bottom - this->activeArea.top);
				
			


				this->vx = (targetX - x) / VAMPIREBAT_FLY_BACK_TIME;
				this->vy = (tagetY - y) / VAMPIREBAT_FLY_BACK_TIME;
				this->flyToPos = true;
				this->isActack = false;
			}

		}
	}
	if (this->flyback_start != 0 && GetTickCount() - this->flyback_start > VAMPIREBAT_FLY_BACK_TIME)
	{
		this->flyback_start = 0;
		this->flyToPos = false;
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
	RenderActiveBox(this->slowActackArea, MYCOLOR::BLUE, 100);
	RenderActiveBox(this->fastActackArea, MYCOLOR::RED);
}

void PhantomBat::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	default:
		break;
	}
}

PhantomBat::PhantomBat() :Enemy()
{
	AddAnimation("VAMPIREBAT_ANI_SLEEP");
	AddAnimation("VAMPIREBAT_ANI_FLYING");
	this->state = VAMPIREBAT_STATE_SLEEP;
	this->attack_time = VAMPIREBAT_ATTACKSLOW_TIME;
}

PhantomBat::~PhantomBat()
{
}
