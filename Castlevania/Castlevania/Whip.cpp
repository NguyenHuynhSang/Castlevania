#include "Whip.h"



void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	
}

void Whip::RenderWhip(int nx)
{
	if (animations[WHIP_ANI_LV1]->GetCurrentFrame() == 0) {
		y += 18;
		x -= 8;
		if (nx < 0) x += 60; 	
	}
	if (animations[WHIP_ANI_LV1]->GetCurrentFrame() == 1) {
		y += 5;
		x -= 10;
		if (nx < 0) x += 52;
	}
	if (animations[WHIP_ANI_LV1]->GetCurrentFrame() == 2) {
		y+=15;
		x +=58;
		if (nx < 0) x -= 2*58+20;
		RenderSpriteBox();
	}
	animations[0]->Render(nx, x, y);
	
}

void Whip::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

Whip::Whip()
{
}


Whip::~Whip()
{
}
