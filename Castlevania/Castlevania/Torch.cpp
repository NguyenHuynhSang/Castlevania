#include "Torch.h"
#include"SceneManagement.h"
#include"Effects.h"
#include"Flame.h"
void Torch::Render()
{
	if (this->setDestroy) {
		return;
	}
	animations[0]->Render(0, x, y);
	RenderBoundingBox();

}

void Torch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroyed) {
		return;
	}
	if (this->setDestroy) {
		this->TurnOffCollision();
		Effects* effect = new Flame();
		effect->SetPositionInWorld(this->x+10, this->y+TORCH_BBOX_HEIGHT/4);
		effect->AddItemDef(this->itemDef);
		SceneManagement::GetInstance()->SpawnEffect(effect);
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
