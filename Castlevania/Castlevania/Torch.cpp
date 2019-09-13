#include "Torch.h"



void Torch::Render()
{
	animations[0]->Render(0, x, y);
	RenderBoundingBox();

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
}


Torch::~Torch()
{
}
