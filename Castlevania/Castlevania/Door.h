#pragma once
#include"GameObject.h"

#define DOOR_CLOSE_BBOX_WIDTH 16
#define DOOR_CLOSE_BBOX_HEIGHT 96

#define DOOR_STATE_CLOSE 0
#define DOOR_STATE_OPEN 100
#define DOOR_STATE_CLOSING 200


#define DOOR_ANI_CLOSE 0
#define DOOR_ANI_OPEN 1
#define DOOR_ANI_CLOSING 2




class Door:public CGameObject
{
	bool doorClosed;
	bool doorOpened;
	bool isColiceWithPlayer=false;
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	bool CheckIsDoorClosed() {
		return this->doorClosed;

	}
	bool CheckIsDoorOpened() {
		return this->doorOpened;
	};

	bool CheckIsColideWithPlayer() {
		return this->isColiceWithPlayer;
	}
	void SetIsColicePlayer(bool flag) {
		this->isColiceWithPlayer = flag;
	}

	void ResetDoor() {
		this->doorOpened = false;
		this->doorClosed = false;
		animations[DOOR_ANI_CLOSE]->ResetAnimation();
		animations[DOOR_ANI_OPEN]->ResetAnimation();
		animations[DOOR_ANI_CLOSING]->ResetAnimation();
		this->SetState(DOOR_STATE_CLOSE);
	};
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void GetSpriteBox(float& width, float& height) {
	};
	Door();
	~Door();
};

