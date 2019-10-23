#include "HandleSpawnSubWeapon.h"
#include"SceneManagement.h"
#include"Dagger.h"
#include"Axe.h"
#include"StopWatch.h"
#include"HolyWater.h"
HandleSpawnSubWeapon * HandleSpawnSubWeapon::__instance = NULL;

void HandleSpawnSubWeapon::SpawnSubWeapon(int subWeaponDef,float x, float y, DIRECTION nx)
{
	switch (subWeaponDef)
	{
	case SWDDAGGER:
	{
		SubWeapon *sw = new Dagger();
		sw->SetPositionInWorld(x,y);
		sw->SetNx(nx);
		scene->SpawnSubWeapon(sw);
		break;
	}
	case SWDAXE: {
		SubWeapon *sw = new Axe();
		sw->SetPositionInWorld(x, y);
		sw->SetNx(nx);
		scene->SpawnSubWeapon(sw);
		break;
	}
	case SWDSTOPWATCH: {
		SubWeapon *sw = StopWatch::GetInstance();
		StopWatch * sub = dynamic_cast<StopWatch *>(sw);
		sub->StartStopWatch();
		scene->SpawnSubWeapon(sw);
		break;
	}
	case SWDHOLLYWATER: {
		SubWeapon* sw = new HolyWater(nx);
		sw->SetPositionInWorld(x, y);
		scene->SpawnSubWeapon(sw);
		break;



	}
	}
}

HandleSpawnSubWeapon::HandleSpawnSubWeapon()
{
}

void HandleSpawnSubWeapon::Init(SceneManagement* scene)
{
	this->scene = scene;
}


HandleSpawnSubWeapon::~HandleSpawnSubWeapon()
{
}
HandleSpawnSubWeapon * HandleSpawnSubWeapon::GetInstance()
{
	if (__instance == NULL) __instance = new HandleSpawnSubWeapon();
	return __instance;
}
