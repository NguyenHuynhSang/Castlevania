#include "Torch.h"
#include"HandleSpawnEffects.h"
#include"HandleSpawnItem.h"
void Torch::Render()
{
	if (this->setDestroy) {
		return;
	}
	animations[0]->Render(DIRECTION::DEFAULT, x, y);
	//RenderBoundingBox();

}

void Torch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroyed) {
		return;
	}
	if (this->setDestroy) {

		HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_FLAME, this->x + 10, this->y + TORCH_BBOX_HEIGHT / 4);
		HandleSpawnItem::GetInstance()->SpawnItem(this->itemDef, this->x, this->y);
		isDestroyed = true;
	}

}

void Torch::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + TORCH_BBOX_WIDTH;
	b = t + TORCH_BBOX_HEIGHT;

}

Torch::Torch()
{

	AddAnimation("TORCH_ANI_BURNING");
	SetState(TORCH_BURNING);
}


Torch::~Torch()
{
}
