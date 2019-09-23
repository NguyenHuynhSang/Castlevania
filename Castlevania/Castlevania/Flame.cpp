#include "Flame.h"
#include"debug.h"


void Flame::Render()
{
	if (this->isDestroyed) return;
	animations[0]->Render(0, x, y);
}

void Flame::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = t = r = b = 0;
}

void Flame::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (this->isDestroyed) return;
		UpdateEffect();
	if (this->setDestroy) {
		SpawnItem();
		this->isDestroyed = true;
	}
	CGameObject::Update(dt);
}

Flame::Flame():Effects()
{
	AddAnimation("FLAME_ANI_BURNING");
}


Flame::~Flame()
{
}
