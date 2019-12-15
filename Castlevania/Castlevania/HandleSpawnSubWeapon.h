#pragma once
#include"define.h"
class PlayScene;
class HandleSpawnSubWeapon
{
	static HandleSpawnSubWeapon * __instance;
	PlayScene* scene;
	bool isDoubleShot = false;
public:
	void SetDoubleShot(bool flag) { this->isDoubleShot = flag; }
	void CheckNumOfSubWeaponUsed();
	void SpawnSubWeapon(int subWeaponDef,float x,float y, DIRECTION nx);
	HandleSpawnSubWeapon();
	void Init(PlayScene* scene);
	~HandleSpawnSubWeapon();
	static HandleSpawnSubWeapon * GetInstance();
};

