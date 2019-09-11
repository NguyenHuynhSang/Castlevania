#pragma once
#include "GameObject.h"
#include "Whip.h"
#define SIMON_WALKING_SPEED		0.1f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_SIT             500
#define SIMON_STATE_STAND_ATTACK    600


#define SIMON_ANI_BIG_IDLE_RIGHT		0
#define SIMON_ANI_BIG_IDLE_LEFT			1
#define SIMON_ANI_SMALL_IDLE_RIGHT		2
#define SIMON_ANI_SMALL_IDLE_LEFT			3

#define SIMON_ANI_BIG_WALKING_RIGHT			4
#define SIMON_ANI_BIG_WALKING_LEFT			5
#define SIMON_ANI_SMALL_WALKING_RIGHT		6
#define SIMON_ANI_SMALL_WALKING_LEFT		7


#define SIMON_ANI_DIE				8
#define SIMON_ANI_SITTING           9
#define SIMON_ANI_STAND_ATTACK           10


#define	SIMON_LEVEL_SMALL	1
#define	SIMON_LEVEL_BIG		2

#define SIMON_BIG_BBOX_WIDTH  40
#define SIMON_BIG_BBOX_HEIGHT 64

#define SIMON_SPRITE_BOX_WIDTH 60
#define SIMON_SPRITE_BOX_HEIGHT 66

#define SIMON_SMALL_BBOX_WIDTH  60
#define SIMON_SMALL_BBOX_HEIGHT 64



#define SIMON_UNTOUCHABLE_TIME 5000

#define SIMON_ATTACK_TIME 250

class CSimon : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD actack_start=0;
	void Renderer(int ani);
	Whip* whip;
	bool isJumping=false;
public: 
	bool isActack = false;
	bool IsJumping() { return this->isJumping; }
	CSimon() : CGameObject()
	{
		level = SIMON_LEVEL_BIG;
		untouchable = 0;
		whip = Whip::GetInstance();
		
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();	
	
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	DWORD GetActack_Time() { return actack_start; }
	void ResetActack_Time() { actack_start = 0; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartActack() { actack_start = GetTickCount(); };
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void ResetSpriteFrame() {
		this->ResetFrame(SIMON_ANI_STAND_ATTACK);
		whip->ResetFrame(WHIP_ANI_LV1);
	}
	virtual void GetSpriteBox(float &width, float &height) {
		width = SIMON_SPRITE_BOX_WIDTH; height = SIMON_SPRITE_BOX_HEIGHT;
	}

	
};