#include "Fishman.h"



void Fishman::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

void Fishman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void Fishman::Render()
{
}

Fishman::Fishman():Enemy()
{
	AddAnimation("FISHMAN_ANI_JUMP");
	AddAnimation("FISHMAN_ANI_WALKING");
	AddAnimation("FISHMAN_ANI_SHOOTING");
}


Fishman::~Fishman()
{
}
