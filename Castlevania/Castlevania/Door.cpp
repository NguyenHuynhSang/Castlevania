#include "Door.h"



void Door::Render()
{
	int ani = 0;
	if (state==DOOR_STATE_OPEN)
	{
		ani = DOOR_ANI_OPEN;
	}
	else
	{
		ani = DOOR_ANI_CLOSE;
	}

	animations[ani]->Render(0, x, y);
}



void Door::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + DOOR_CLOSE_BBOX_WIDTH;
	b = y + DOOR_CLOSE_BBOX_HEIGHT;
}

Door::Door()
{
	AddAnimation("DOOR_ANI_CLOSE");
	AddAnimation("DOOR_ANI_OPEN");
}


Door::~Door()
{
}
