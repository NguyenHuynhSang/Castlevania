﻿#pragma once
#include "GameObject.h"
#include "Whip.h"
#define SIMON_WALKING_SPEED		0.13f 
#define SIMON_AUTOWALKING_SPEED		0.05f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.6f
#define SIMON_DEFLECT_SPEED_X 0.2f
#define SIMON_DEFLECT_SPEED_Y 0.45f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f
#define SIMON_UPSTAIR_VELOCITY 0.02f
#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_SIT             500
#define SIMON_STATE_STAND_ATTACK    600
#define SIMON_STATE_SIT_ATTACK 700
#define SIMON_STATE_DEFLECT 800
#define SIMON_STATE_POWERUP 900
#define SIMON_STATE_UPSTAIR_IDLE 1000
#define SIMON_STATE_UPSTAIR_STEPUP 1100

#define SIMON_ANI_BIG_IDLE_RIGHT		0
#define SIMON_ANI_BIG_IDLE_LEFT			1
#define SIMON_ANI_SMALL_IDLE_RIGHT		2
#define SIMON_ANI_SMALL_IDLE_LEFT			3

#define SIMON_ANI_BIG_WALKING_RIGHT			4
#define SIMON_ANI_BIG_WALKING_LEFT	    5
#define SIMON_ANI_SMALL_WALKING_RIGHT		6
#define SIMON_ANI_SMALL_WALKING_LEFT   7

#define SIMON_ANI_DIE				     8
#define SIMON_ANI_SITTING                  9
#define SIMON_ANI_STAND_ATTACK           10
#define SIMON_ANI_SIT_ATTACK           11
#define SIMON_ANI_DEFLECT               12
#define SIMON_ANI_IDLE_UPWHIP              13
#define SIMON_ANI_IDLE_UPSTAIR          14
#define SIMON_ANI_STEP_UPSTAIR            15

#define	SIMON_LEVEL_SMALL	1
#define	SIMON_LEVEL_BIG		2

#define SIMON_BIG_BBOX_WIDTH  38
#define SIMON_BIG_BBOX_HEIGHT 62

#define SIMON_SPRITE_BOX_WIDTH 60
#define SIMON_SPRITE_BOX_HEIGHT 66

#define SIMON_SMALL_BBOX_WIDTH  60
#define SIMON_SMALL_BBOX_HEIGHT 64

#define SIMON_UPSTAIR_DISTANCE_X 16 // quãng đường theo trục x mỗi lần lên 1 bậc cầu thang
#define SIMON_UPSTAIR_DISTANCE_Y 16 // quãng đường theo trục y mỗi lần lên 1 bậc cầu thang

#define SIMON_UPSTAIR_OFFSET  9



#define SIMON_UNTOUCHABLE_TIME 5000

#define SIMON_ATTACK_TIME 300
#define SIMON_POWERUP_TIME 1000
class CSimon : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD actack_start=0;
	DWORD upwhip_start = 0;;
	void Renderer(int ani);
	Whip* whip;
	bool isJumping=false;
	bool isAutoWalk = false;
	bool isActack = false;
	bool sleepControl = false;
	float body_x;
	int subWeapon;
	bool isOnStair = false;
	bool startOnStair = false;
	bool isColliceWithStair = false;
	bool isFirstStepOnStair = false;
	D3DXVECTOR2 stairPos;
	D3DXVECTOR2 LastStepOnStairPos;
public: 
	void HandleFirstStepOnStair();
	void StartOnStair(bool flag) {
		this->startOnStair = flag;
	}
	bool CheckStairOnStair() {
		return this->startOnStair;
	}
	bool CheckIsOnStair() {
		return this->isOnStair;
	}
	bool CheckCollideWithStair() {
		return this->isColliceWithStair;
	}
	void SetStartStepOnStair() {
		this->startOnStair = true;
	}
	void SetAutoWalk(bool flag) {
		this->isAutoWalk = flag;
		state = SIMON_STATE_WALKING_RIGHT;
		
	}
	
	DWORD GetPowerUpTime() {
		return this->upwhip_start;
	}
	void StartPowerUp() {
		this->upwhip_start = GetTickCount();
	};
	bool CheckAutoWalk() {
		return this->isAutoWalk;
	}

	bool IsJumping() { return this->isJumping; }
	CSimon() : CGameObject()
	{
		level = SIMON_LEVEL_BIG;
		untouchable = 0;
		whip = Whip::GetInstance();
		this->AddAnimation("SIMON_ANI_IDLE");		// idle right big 0
		this->AddAnimation("SIMON_ANI_IDLE");		// idle left big  1
		this->AddAnimation("SIMON_ANI_IDLE");		// idle right small  2
		this->AddAnimation("SIMON_ANI_IDLE");		// idle left small 3
		this->AddAnimation("SIMON_ANI_WALKING");		// walk right big  4
		this->AddAnimation("SIMON_ANI_IDLE");		// walk left big  5
		this->AddAnimation("SIMON_ANI_IDLE");		// walk right small  6
		this->AddAnimation("SIMON_ANI_IDLE");		// walk left big  7
		this->AddAnimation("SIMON_ANI_IDLE");		// die   8
		this->AddAnimation("SIMON_ANI_SITTING");       // sit   9
		this->AddAnimation("SIMON_ANI_STAND_ATTACK");       // stand attack   10
		this->AddAnimation("SIMON_ANI_SIT_ATTACK");       // sit attack   11
		this->AddAnimation("SIMON_ANI_DEFLECT");    //12
		this->AddAnimation("SIMON_ANI_IDLE_UPWHIP");    //13
		this->AddAnimation("SIMON_ANI_IDLE_UPSTAIR");    //14
		this->AddAnimation("SIMON_ANI_STEP_UPSTAIR");    //15

		//this->animations[SIMON_ANI_STAND_ATTACK]->SetAnimationLoop(false);
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();	
	void ResetPowerUpTime() {
		this->upwhip_start = 0;
	}
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void SimonUseSubWeapon();
	DWORD GetActack_Time() { return actack_start; }
	void ResetActack_Time() { actack_start = 0; }
	bool CheckAttack() {
		return this->isActack;
	}
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartActack() { 
	this->isActack = true;
	};
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void ResetSpriteFrame() {
		this->ResetFrame(SIMON_ANI_STAND_ATTACK);
		whip->ResetFrame(WHIP_ANI_LV1);
	}
	virtual void GetSpriteBox(float &width, float &height) {
		width = SIMON_SPRITE_BOX_WIDTH; height = SIMON_SPRITE_BOX_HEIGHT;
	}

	};