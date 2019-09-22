#include "SpawnZone.h"



bool SpawnZone::CheckInCam()
{
	return false;
}

void SpawnZone::Render()
{
	RenderBoundingBox();
}

void SpawnZone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

SpawnZone::SpawnZone()
{
}


SpawnZone::~SpawnZone()
{
}
