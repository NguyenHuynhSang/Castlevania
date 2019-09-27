#include "Brick.h"
#include"debug.h"
#include"HandleSpawnEffects.h"
#include"HandleSpawnItem.h"
CBrick::CBrick()
{
	AddAnimation("BRICK_ANI_NORMAL");
	AddAnimation("BRICK_ANI_BREAKING");
}



CBrick::~CBrick()
{
}

void CBrick::Render()
{
	
	int ani = 0;
	if (state==BRICK_STATE_NORMAL)
	{
		ani = BRICK_ANI_NORMAL;
	}
	else
	{
		ani = BRICK_ANI_BREAKING;
	}
	animations[ani]->Render(0,x, y);
	RenderBoundingBox();
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroyed) {
		return;
	}
	if (this->setDestroy) {
		
		HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_DEBRIS, this->x, this->y);
		HandleSpawnItem::GetInstance()->SpawnItem(this->itemDef, this->x, this->y, false);
		isDestroyed = true;
	}
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

