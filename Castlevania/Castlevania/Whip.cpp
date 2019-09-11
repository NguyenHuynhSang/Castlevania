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
	return;
}



void Whip::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + 10;
	b = y + 10;
}

Whip::Whip()
{
}


Whip::~Whip()
{
}
