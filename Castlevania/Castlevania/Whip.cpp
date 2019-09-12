#include "Whip.h"
#include"debug.h"

Whip * Whip::__instance = NULL;


void Whip::Render(int nx)
{

}

Whip *Whip::GetInstance()
{
	if (__instance == NULL) __instance = new Whip();
	return __instance;
}
void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	
}

void Whip::Render()
{

	animations[0]->Render(nx, x, y);
	RenderBoundingBox();
	RenderSpriteBox();
	return;
}



void Whip::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (nx > 0) {
		l = x + 60 * 2+2;
		t = y + 12;
	}
	else {
		l = x+55-2;
		t = y + 12;
	}

	r = l +64;
	b = t +20;
}

Whip::Whip()
{
	AddAnimation("WHIP_ANI_LV1");
}


Whip::~Whip()
{
}
