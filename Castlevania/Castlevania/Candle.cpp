#include "Candle.h"
#include"HandleSpawnEffects.h"
#include"HandleSpawnItem.h"
Candle::Candle()
{
	AddAnimation("CANDLE_ANI_BURNING");
}


Candle::~Candle()
{
}

void Candle::Render()
{
	if (this->setDestroy) {
		return;
	}
	animations[0]->Render(DIRECTION::DEFAULT, x, y);

}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroyed) {
		return;
	}
	if (this->setDestroy) {
		HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_FLAME, this->x, this->y);
		HandleSpawnItem::GetInstance()->SpawnRandomItem(this->x, this->y);
		isDestroyed = true;
	}
}

void Candle::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + CANDLE_BBOX_WIDTH;
	b = t + CANDLE_BBOX_HEIGHT;
}
