#pragma once
#include"define.h"
class SceneManagement;
class HandleSpawnSubWeapon
{
	static HandleSpawnSubWeapon * __instance;
	SceneManagement* scene;
	bool isDoubleShot = false;
public:
	void SetDoubleShot(bool flag) { this->isDoubleShot = flag; }
	void CheckNumOfSubWeaponUsed();
	void SpawnSubWeapon(int subWeaponDef,float x,float y, DIRECTION nx);
	HandleSpawnSubWeapon();
	void Init(SceneManagement* scene);
	~HandleSpawnSubWeapon();
	static HandleSpawnSubWeapon * GetInstance();
};

