#pragma once
class HandleSpawnSubWeapon
{
	static HandleSpawnSubWeapon * __instance;
public:

	void SpawnSubWeapon(int subWeaponDef,float x,float y,int nx);
	HandleSpawnSubWeapon();
	~HandleSpawnSubWeapon();
	static HandleSpawnSubWeapon * GetInstance();
};

