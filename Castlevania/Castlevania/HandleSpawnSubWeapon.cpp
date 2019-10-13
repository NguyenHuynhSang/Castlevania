#include "HandleSpawnSubWeapon.h"
#include"SceneManagement.h"
#include"Dagger.h"
#include"Axe.h"
#include"StopWatch.h"
HandleSpawnSubWeapon * HandleSpawnSubWeapon::__instance = NULL;

void HandleSpawnSubWeapon::SpawnSubWeapon(int subWeaponDef,float x, float y,int nx)
{
	switch (subWeaponDef)
	{
	case SWDDAGGER:
	{
		SubWeapon *sw = new Dagger();
		sw->SetPositionInWorld(x,y);
		sw->SetNx(nx);
		SceneManagement::GetInstance()->SpawnSubWeapon(sw);
		break;
	}
	case SWDAXE: {
		SubWeapon *sw = new Axe();
		sw->SetPositionInWorld(x, y);
		sw->SetNx(nx);
		SceneManagement::GetInstance()->SpawnSubWeapon(sw);
		break;
	}
	case SWDSTOPWATCH: {
		SubWeapon *sw = StopWatch::GetInstance();
		StopWatch * sub = dynamic_cast<StopWatch *>(sw);
		sub->StartStopWatch();
		SceneManagement::GetInstance()->SpawnSubWeapon(sw);
		break;
	}
	}
}

HandleSpawnSubWeapon::HandleSpawnSubWeapon()
{
}


HandleSpawnSubWeapon::~HandleSpawnSubWeapon()
{
}
HandleSpawnSubWeapon * HandleSpawnSubWeapon::GetInstance()
{
	if (__instance == NULL) __instance = new HandleSpawnSubWeapon();
	return __instance;
}