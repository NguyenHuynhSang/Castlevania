#include "BossDead.h"

void BossDead::Render()
{
	if (this->isDestroyed) return;

	animations[0]->Render(DIRECTION::DEFAULT, x, y);
}

void BossDead::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b = 0;
}

void BossDead::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroyed) return;
	UpdateEffect();
	if (this->setDestroy) {
		this->isDestroyed = true;
	}
}	

BossDead::BossDead():Effects()
{
	AddAnimation("BOSS_DEAD_ANI");
}

BossDead::~BossDead()
{
}
