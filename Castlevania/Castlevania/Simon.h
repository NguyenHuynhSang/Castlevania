#pragma once
#include "GameObject.h"
#include "Whip.h"
#define SIMON_WALKING_SPEED		0.13f 
#define SIMON_AUTOWALKING_SPEED		0.05f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.58f
#define SIMON_DEFLECT_SPEED_X 0.2f
#define SIMON_DEFLECT_SPEED_Y 0.45f
#define SIMON_GRAVITY			0.0018f
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
#define SIMON_ANI_IDLE_DOWNSTAIR         16
#define SIMON_ANI_STEP_DOWNSTAIR            17
#define SIMON_ANI_UPSTAIR_ATTACK            18
#define SIMON_ANI_DOWNSTAIR_ATTACK         19
#define	SIMON_LEVEL_SMALL	1
#define	SIMON_LEVEL_BIG		2

#define SIMON_BIG_BBOX_WIDTH  32
#define SIMON_BIG_BBOX_HEIGHT 62

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
class CSimon : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD attack_start = 0;
	DWORD upwhip_start = 0;
	DWORD delay_attack_start = 0;
	void Renderer(int ani);
	Whip* whip;
	bool isJumping = false;
	bool isAutoWalk = false;
	bool isActack = false;
	int subWeaponDef=-1;
	bool isUseSubWeapon = false;
	bool isSpawnSubWeapon = false;
	bool isOnStair = false;
	bool startOnStair = false;
	bool isColliceWithStair = false;
	bool isFirstStepOnStair = false;
	int stepOnStairDirection = -1;
	int lastState = -1;
	D3DXVECTOR2 stairPos;
	D3DXVECTOR2 LastStepOnStairPos;
	void HandleFirstStepOnStair();
	void HandlePerStepOnStair();
public:
	void ResetState() {
		isOnStair = startOnStair = isColliceWithStair = isFirstStepOnStair
			= isActack = isAutoWalk = isJumping = isUseSubWeapon = false;
		this->stepOnStairDirection = -1;
		this->lastState = -1; 
		this->delay_attack_start = 0;
		this->attack_start = 0;
		this->untouchable_start = 0;
		this->untouchable = 0;
	}
	void StartDelayAttack() {
		this->delay_attack_start = GetTickCount();
	}
	DWORD CheckDelayAttackTime() {
		return  this->delay_attack_start;
	}
	bool CheckIsUseSubWeapon() {
		return this->isUseSubWeapon;
	}
	int GetCurrentSubWeapon() {
		return this->subWeaponDef;
	}
	void ResetDelayAttackTime() {
		this->delay_attack_start = 0;
	}
	void ResetUseSubWeapon() {
		this->isUseSubWeapon = false;
		this->isSpawnSubWeapon = false;
	}
	void SetStepOnStairDirection(int dir) {
		this->stepOnStairDirection = dir;
	}
	int CheckStepOnStairDirection() {
		return this->stepOnStairDirection;
	}
	void HandleUseSubWeapon();
	void StartOnStair(bool flag) {
		this->startOnStair = flag;
	}
	bool CheckStairOnStair() {
		return this->startOnStair;
	}

	bool CheckCanStepUp() {
		if (this->stepOnStairDirection == DIR_UPLEFT || this->stepOnStairDirection == DIR_UPRIGHT)
			return true;
		return false;
	}
	bool CheckCanStepDown() {
		if (this->stepOnStairDirection == DIR_DOWNLEFT || this->stepOnStairDirection == DIR_DOWNRIGHT)
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
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void ResetPowerUpTime() {
		this->upwhip_start = 0;
	}
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void SimonUseSubWeapon();
	DWORD GetActack_Time() { return attack_start; }
	void ResetActack_Time() { attack_start = 0; }
	bool CheckAttack() {
		return this->isActack;
	}
	void StartUseSubWeapon() {
		this->isUseSubWeapon = true;
		this->attack_start = GetTickCount();
	}
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartActack() {
		this->isActack = true;
	};

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void ResetSpriteFrame() {
		this->ResetFrame(SIMON_ANI_STAND_ATTACK);
		this->ResetFrame(SIMON_ANI_SIT_ATTACK);
		whip->ResetAnimationFrame();
	}
	virtual void GetSpriteBox(float &width, float &height) {
		width = SIMON_SPRITE_BOX_WIDTH; height = SIMON_SPRITE_BOX_HEIGHT;
	}

};