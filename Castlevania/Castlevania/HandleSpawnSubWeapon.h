#pragma once

class SceneManagement;
class HandleSpawnSubWeapon
{
	static HandleSpawnSubWeapon * __instance;
	SceneManagement* scene;
public:

	void SpawnSubWeapon(int subWeaponDef,float x,float y,int nx);
	HandleSpawnSubWeapon();
	void Init(SceneManagement* scene);
	~HandleSpawnSubWeapon();
	static HandleSpawnSubWeapon * GetInstance();
};

