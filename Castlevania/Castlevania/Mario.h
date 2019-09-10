#pragma once
#include "GameObject.h"
#include "Whip.h"
#define MARIO_WALKING_SPEED		0.1f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400
#define MARIO_STATE_SIT             500
#define MARIO_STATE_STAND_ATTACK    600


#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT			3

#define MARIO_ANI_BIG_WALKING_RIGHT			4
#define MARIO_ANI_BIG_WALKING_LEFT			5
#define MARIO_ANI_SMALL_WALKING_RIGHT		6
#define MARIO_ANI_SMALL_WALKING_LEFT		7


#define MARIO_ANI_DIE				8
#define MARIO_ANI_SITTING           9
#define MARIO_ANI_STAND_ATTACK           10


#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2

#define MARIO_BIG_BBOX_WIDTH  40
#define MARIO_BIG_BBOX_HEIGHT 64

#define MARIO_SPRITE_BOX_WIDTH 60
#define MARIO_SPRITE_BOX_HEIGHT 66

#define MARIO_SMALL_BBOX_WIDTH  60
#define MARIO_SMALL_BBOX_HEIGHT 64



#define MARIO_UNTOUCHABLE_TIME 5000

#define MARIO_ATTACK_TIME 200

class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD actack_start=0;
	void Renderer(int ani);
	Whip* whip;
public: 
	bool isActack = false;
	void SetWhip(Whip* whip) { this->whip = whip;
	whip->SetPosition(x, y);
	};
	CMario() : CGameObject()
	{
		level = MARIO_LEVEL_BIG;
		untouchable = 0;
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
	virtual void GetSpriteBox(float &width, float &height) {
		width = MARIO_SPRITE_BOX_WIDTH; height = MARIO_SPRITE_BOX_HEIGHT;
	}
};