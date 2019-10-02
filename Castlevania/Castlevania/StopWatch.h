#pragma once
#include"SubWeapon.h"
#define STOPWATCH_FREEZE_TIME 3000


class StopWatch :public SubWeapon
{
	static StopWatch * __instance;

	DWORD stopwatch_start;
public:
	virtual void Render() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b) {
	};
	static StopWatch * GetInstance();
	StopWatch();
	~StopWatch();
};

