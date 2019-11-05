#pragma once
#include"define.h"
class SceneManager;
class HandleSpawnSubWeapon
{
	static HandleSpawnSubWeapon * __instance;
	SceneManager* scene;
	bool isDoubleShot = false;
public:
	void SetDoubleShot(bool flag) { this->isDoubleShot = flag; }
	void CheckNumOfSubWeaponUsed();
	void SpawnSubWeapon(int subWeaponDef,float x,float y, DIRECTION nx);
	HandleSpawnSubWeapon();
	void Init(SceneManager* scene);
	~HandleSpawnSubWeapon();
	static HandleSpawnSubWeapon * GetInstance();
};

