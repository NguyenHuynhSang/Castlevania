#include "Spark.h"
#include"debug.h"


void Spark::Render()
{
	if (this->isDestroyed) return;
	animations[0]->Render(0, x, y);
}

void Spark::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = t = r = b = 0;
}

void Spark::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (this->isDestroyed) return;
	UpdateEffect();
	if (this->setDestroy) {
		SpawnItem();
		this->isDestroyed = true;
	}
	CGameObject::Update(dt);
}

Spark::Spark():Effects()
{
	AddAnimation("HEART_ANI_SMALL");
}


Spark::~Spark()
{
}
