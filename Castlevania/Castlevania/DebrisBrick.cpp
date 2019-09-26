#include "DebrisBrick.h"



void DebrisBrick::Render()
{
	animations[0]->Render(0, x, y);
}

void DebrisBrick::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = t = r = b = 0;
}

void DebrisBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (this->isDestroyed) return;
	UpdateEffect();
	if (this->setDestroy) {
		SpawnItem();
		this->isDestroyed = true;
	}
	vy += DEBRIS_GRAVITY * dt;
	x += dx;
	y += dy;

}

DebrisBrick::DebrisBrick()
{
}

DebrisBrick::DebrisBrick(float vx, float vy)
{
	AddAnimation("DEBRIS_ANI");
	this->vx = vx;
	this->vy = vy;
}


DebrisBrick::~DebrisBrick()
{
}
