#include "Spark.h"

void Spark::Render()
{
	if (this->isDestroyed) return;
	animations[0]->Render(DIRECTION::DEFAULT, x, y);
}

void Spark::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b = 0;
}

void Spark::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroyed) return;
	UpdateEffect();
	if (this->setDestroy) {
		this->isDestroyed = true;
	}

}

Spark::Spark() :Effects()
{
	AddAnimation("SPARK_ANI");
}

Spark::~Spark()
{
}
