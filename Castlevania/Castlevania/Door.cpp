#include "Door.h"



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

	animations[ani]->Render(0, x, y);
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
}


Door::~Door()
{
}
