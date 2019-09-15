#include "MoneyBag.h"
#include"Ground.h"


void MoneyBag::Render()
{
	int ani = 0;
	animations[ani]->Render(0,x,y);
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
	if (this->setDestroy) {
		this->TurnOffCollision();
		this->isDestroyed = true;
		return;
	}
	
	CGameObject::Update(dt);

	vy -= HEART_GRAVITY * dt;

	y += dy;
	x += dx;
	for (int i = 0; i < coObjects->size();i++) {
		{
			if (dynamic_cast<Ground *>(coObjects->at(i)))
			{
				Ground * f = dynamic_cast<Ground*> (coObjects->at(i));
				if (!this->IsColliding(this, f)) {
					vy = 0;
				}
				break;	
			}
			
		}
	}
}

MoneyBag::MoneyBag()
{
	AddAnimation("MONEYBAG_ANI_COLOR");
	AddAnimation("MONEYBAG_ANI_BLUE");
	AddAnimation("MONEYBAG_ANI_RED");
	AddAnimation("MONEYBAG_ANI_WHITE");
}


MoneyBag::~MoneyBag()
{
}
