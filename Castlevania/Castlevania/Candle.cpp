#include "Candle.h"
#include"SceneManagement.h"
#include"Effects.h"
#include"Flame.h"

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
	animations[0]->Render(0, x, y);
}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroyed) {
		return;
	}
	if (this->setDestroy) {
		Effects* effect = new Flame();
		effect->SetPositionInWorld(this->x + 5, this->y);
		SceneManagement::GetInstance()->SpawnEffect(effect);
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
