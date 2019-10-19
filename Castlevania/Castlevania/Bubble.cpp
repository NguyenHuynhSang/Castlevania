#include "Bubble.h"



void Bubble::Render()
{
	animations[0]->Render(DIRECTION::DEFAULT, x, y);
}

void Bubble::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = t = r = b = 0;
}

void Bubble::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (this->isDestroyed) return;
	UpdateEffect();
	if (this->setDestroy) {
		this->isDestroyed = true;
	}
	vy += BUBBLE_GRAVITY * dt;
	x += dx;
	y += dy;
}

Bubble::Bubble():Effects()
{
}

Bubble::Bubble(float vx, float vy) : Effects()
{
	AddAnimation("BUBBLE_ANI");
	this->vx = vx;
	this->vy = vy;
}


Bubble::~Bubble()
{
}
