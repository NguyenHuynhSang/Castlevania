#include "Ghoul.h"
#include"debug.h"
void Ghoul::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GHOUL_BBOX_WIDTH;

	if (state == GHOUL_STATE_DIE)
		bottom = y + GHOUL_BBOX_HEIGHT_DIE;
	else 	
		bottom = y + GHOUL_BBOX_HEIGHT;
}

void Ghoul::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
		// Simple fall down
	

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		vy += GHOUL_GRAVITY;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.2f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.2f;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Ghoul::Render()
{
	
	int ani = GHOUL_ANI_WALKING;
	if (state == GHOUL_STATE_DIE) {
		ani = GHOUL_ANI_DIE;
	}

	animations[ani]->Render(nx,x,y);
	RenderBoundingBox();
	//RenderSpriteBox();
}

void Ghoul::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GHOUL_STATE_DIE:
			y += GHOUL_BBOX_HEIGHT - GHOUL_BBOX_HEIGHT_DIE + 1;
			vx = 0;
			vy = 0;
			break;
		case GHOUL_STATE_WALKING: 
			vx = -GHOUL_WALKING_SPEED;
	}

}
