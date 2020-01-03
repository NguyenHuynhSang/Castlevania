﻿#pragma once
#include "GameObject.h"
#include "Whip.h"

#define SIMON_WALKING_SPEED		0.13f 
#define SIMON_AUTOWALKING_SPEED		0.05f 
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_DEFLECT_SPEED_X 0.2f
#define SIMON_DEFLECT_SPEED_Y 0.35f
#define SIMON_GRAVITY			0.0015f
#define SIMON_FALLDOWN_VY 0.8f
#define SIMON_FALLING_GRAVITY    0.003f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f
#define SIMON_UPSTAIR_VELOCITY 0.04f
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
#define SIMON_STATE_UPSTAIR_RIGHT 1100
#define SIMON_STATE_UPSTAIR_LEFT 1200
#define SIMON_STATE_DOWNSTAIR_IDLE 1300
#define SIMON_STATE_DOWNSTAIR_RIGHT 1400
#define SIMON_STATE_DOWNSTAIR_LEFT 1500
#define SIMON_STATE_UPSTAIR_ATTACK 1600
#define SIMON_STATE_DOWNSTAIR_ATTACK 1700
#define SIMON_STATE_FALL_DOWN      1800



#define SIMON_ANI_IDLE		0
#define SIMON_ANI_WALKING			1
#define SIMON_ANI_SITTING                  2
#define SIMON_ANI_STAND_ATTACK           3
#define SIMON_ANI_SIT_ATTACK           4
#define SIMON_ANI_DEFLECT               5
#define SIMON_ANI_IDLE_UPWHIP              6
#define SIMON_ANI_IDLE_UPSTAIR          7
#define SIMON_ANI_STEP_UPSTAIR            8
#define SIMON_ANI_IDLE_DOWNSTAIR         9
#define SIMON_ANI_STEP_DOWNSTAIR            10
#define SIMON_ANI_UPSTAIR_ATTACK            11
#define SIMON_ANI_DOWNSTAIR_ATTACK         12
#define SIMON_ANI_DIE                  13



#define SIMON_SPRITE_BOX_WIDTH 60
#define SIMON_SPRITE_BOX_HEIGHT 66

#define SIMON_SMALL_BBOX_WIDTH  60
#define SIMON_SMALL_BBOX_HEIGHT 64

#define SIMON_ONSTAIR_DISTANCE_X 16 // quãng đường theo trục x mỗi lần lên xuống 1 bậc cầu thang
#define SIMON_ONSTAIR_DISTANCE_Y 16 // quãng đường theo trục y mỗi lần lên xuống 1 bậc cầu thang


// Hiệu số vị trí của stair trigger và vị trí simon khi bắt đầu bước lên
#define SIMON_UPSTAIR_RIGHT_OFFSET  12
#define SIMON_UPSTAIR_LEFT_OFFSET 16 // da giam 3px
#define SIMON_DOWNSTAIR_LEFT_OFFSET 10
#define SIMON_DOWNSTAIR_RIGHT_OFFET 18


#define SIMON_UNTOUCHABLE_TIME 5000
#define SIMON_DELAY_ACCTACK_BYSUBWEBPON_TIME 50
#define SIMON_ATTACK_TIME 350
#define SIMON_POWERUP_TIME 1000

#define SIMON_MAX_HP 16
#define SIMON_MAX_ENERY 99
#define SIMON_PARALYZE_TIME 300

class CSimon : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
	DWORD attack_start = 0;
	DWORD upwhip_start = 0;
	DWORD paralyze_start = 0; //paralyze when falldown
	DWORD delay_attack_start = 0;
	int hp_;
	int enery_;
	static int score_;


	Whip* whip;
	int subWeaponDef = -1;
	bool isJumping = false;
	bool isAutoWalk = false;
	bool isActack = false;
	bool isUseSubWeapon = false;
	bool isSpawnSubWeapon = false;
	bool isOnStair = false;
	bool startOnStair = false;
	bool isColliceWithStair = false;
	bool isFirstStepOnStair = false;
	bool isHitDoor = false;
	bool getCross = false;
	bool isFightWithBoss = false;
	bool isDoubleShot = false;
	bool isTrippleShot = false;
	STAIRDIRECTION onStairDirection = STAIRDIRECTION::DEFAULT;
	int lastState = -1;
	D3DXVECTOR2 stairPos;
	D3DXVECTOR2 LastStepOnStairPos;
	void HandleFirstStepOnStair();
	void HandlePerStepOnStair();
	float lastPosition;// dùng để walk through door
	void Renderer(int ani);
public:
	
	static void AddScore(int score) { score_ += score; }
	static int GetScore() { return score_; }
	void ResetPoint() {
		this->hp_ = 16;
		this->enery_ = 5;
	}
	void ResetIsGetCross() 
	{
		this->getCross = false;
	}
	bool CheckIsGetCross() 
	{
		return this->getCross;
	};
	void ResetState() {
		isOnStair = startOnStair = isColliceWithStair = isFirstStepOnStair
			= isActack = isAutoWalk = isJumping = isHitDoor = isUseSubWeapon = isFightWithBoss= false;
		this->onStairDirection = STAIRDIRECTION::DEFAULT; 
		this->lastState = -1;
		this->delay_attack_start = 0;
		this->attack_start = 0;
		this->untouchable_start = 0;
		this->untouchable = 0;

	

	}


	int GetHP() {
		return this->hp_;
	}
	void SetHP(float hp) {
		this->hp_ = hp;
		if (this->hp_ > SIMON_MAX_HP)
		{
			this->hp_ = SIMON_MAX_HP;
		}
		else if (this->hp_ < 0)
		{
			this->hp_ = 0;
		}
	}

	int GetEnery() {
		return this->enery_;
	}
	void SetEnery(int enery) {

		this->enery_ = enery;
		if (this->enery_ > SIMON_MAX_ENERY)
		{
			this->enery_ = SIMON_MAX_ENERY;
		}
		else if (this->enery_ < 0)
		{
			this->enery_ = 0;
		}
	}

	bool CheckIsFightWithBoss() {
		return this->isFightWithBoss;
	}
	void AddEnery(int point) {
		this->enery_ += point;
		SetEnery(enery_);
	}

	void AddHP(int point) {
		this->hp_ += point;
		SetHP(hp_);
	}



	void SetLastPosition(float ps) {
		this->lastPosition = ps;
	}
	float GetLastPosition() {
		return this->lastPosition;
	}

	bool CheckIsUseSubWeapon() {
		return this->isUseSubWeapon;
	}
	int GetCurrentSubWeapon() {
		return this->subWeaponDef;
	}

	void ResetUseSubWeapon() {
		this->isUseSubWeapon = false;
		this->isSpawnSubWeapon = false;
	}
	void SetStepOnStairDirection(STAIRDIRECTION dir) {
		this->onStairDirection = dir;
	}
	STAIRDIRECTION CheckStepOnStairDirection() {
		return this->onStairDirection;
	}
	void HandleUseSubWeapon();
	void StartOnStair(bool flag) {
		this->startOnStair = flag;
	}
	bool CheckStairOnStair() {
		return this->startOnStair;
	}
	bool CheckIsHitDoor() {
		return this->isHitDoor;
	}

	bool SimonAutoWalkaStep(float step);

	bool CheckCanStepUp() {
		if (this->onStairDirection == STAIRDIRECTION::UPLEFT || this->onStairDirection == STAIRDIRECTION::UPRIGHT)
			return true;
		return false;
	}
	bool CheckCanStepDown() {
		if (this->onStairDirection == STAIRDIRECTION::DOWNLEFT || this->onStairDirection == STAIRDIRECTION::DOWNRIGHT)
			return true;
		return false;
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
	}

	DWORD GetPowerUpTime() {
		return this->upwhip_start;
	}
	void StartPowerUp() {
		this->upwhip_start = GetTickCount();
		whip->UpWhip();
	};
	bool CheckAutoWalk() {
		return this->isAutoWalk;
	}

	bool CheckIsJumping() { return this->isJumping; }
	CSimon();
	~CSimon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void ResetPowerUpTime() {
		this->upwhip_start = 0;
	}
	void SetState(int state,bool chanegSimonattribute=true);
	void SimonUseSubWeapon();
	DWORD GetActack_Time() {
		return attack_start;
	
	
	}
	void ResetActack_Time() { attack_start = 0; }
	bool CheckAttack() {
		
		return this->isActack;
	}
	void StartUseSubWeapon();
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartActack() {
		this->isActack = true;
	//	this->ResetSpriteFrame();

	};

	void SetLastState(int state) {
		this->lastState = state;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void ResetSpriteFrame() {
		this->ResetFrame(SIMON_ANI_STAND_ATTACK);
		this->ResetFrame(SIMON_ANI_UPSTAIR_ATTACK);
		this->ResetFrame(SIMON_ANI_DOWNSTAIR_ATTACK);
		this->ResetFrame(SIMON_ANI_SIT_ATTACK);
		whip->ResetAnimationFrame();
	}
	virtual void GetSpriteBox(float& width, float& height) {
		width = SIMON_SPRITE_BOX_WIDTH; height = SIMON_SPRITE_BOX_HEIGHT;
	}

};

