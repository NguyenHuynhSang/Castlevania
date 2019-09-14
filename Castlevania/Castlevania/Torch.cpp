#include "Torch.h"
#include"Item.h"
#include"Heart.h"
#include"SceneManagement.h"
void Torch::Render()
{
	if (this->isDestroyed) {
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
		Item *heart; 
		if (this->itemName == "bigheart") {
			heart = new Heart();
			SceneManagement* scene = SceneManagement::GetInstance();
			heart->SetPosition(this->x+ TORCH_BBOX_WIDTH/2, this->y - 64);
			scene->SpawnItem(heart);
		}
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
