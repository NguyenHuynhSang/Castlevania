#include "Door.h"
#include"Sound.h"


void Door::Render()
{
	int ani = 0;
	if (state == DOOR_STATE_OPEN)
	{
		ani = DOOR_ANI_OPEN;
	}
	else if (state == DOOR_STATE_CLOSE)
	{
		ani = DOOR_ANI_CLOSE;
	}
	else {
		ani = DOOR_ANI_CLOSING;
	}

	animations[ani]->Render(DIRECTION::DEFAULT, x, y);
}

void Door::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->animations[DOOR_ANI_OPEN]->CheckAnimationDone())
	{
		this->doorClosed = false;
		this->doorOpened = true;
	}

	if (this->animations[DOOR_ANI_CLOSING]->CheckAnimationDone())
	{
		this->doorClosed = true;
		this->doorOpened = false;
	}
}



void Door::SetState(int state)
{
	Sound* sound = Sound::GetInstance();

	switch (state)
	{
	case DOOR_STATE_CLOSE: {
		break;
	}
	case DOOR_STATE_OPEN: {
		if (this->state != DOOR_STATE_CLOSING && this->state != DOOR_STATE_OPEN)
		{
			sound->Play(eSound::soundOpenDoor);
		}
		break;
	}
	case DOOR_STATE_CLOSING: {
		if (this->state != DOOR_STATE_CLOSING && this->state != DOOR_STATE_OPEN)
		{
			sound->Play(eSound::soundOpenDoor);
		}
		DebugOut(L"ABVC \n");
		break;
	}
	default:
		break;
	}
	this->state = state;
}

void Door::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + DOOR_CLOSE_BBOX_WIDTH;
	b = y + DOOR_CLOSE_BBOX_HEIGHT;
	if (state!=DOOR_ANI_CLOSE)
	{
		l = t = r = b = 0;
	}
}

Door::Door()
{
	AddAnimation("DOOR_ANI_CLOSE", false);
	AddAnimation("DOOR_ANI_OPEN", false);
	AddAnimation("DOOR_ANI_CLOSING", false);
	animations[DOOR_ANI_OPEN]->ResetAnimation();
	animations[DOOR_ANI_CLOSING]->ResetAnimation();

	this->doorClosed = false;
	this->doorClosed = false;
}


Door::~Door()
{
}
