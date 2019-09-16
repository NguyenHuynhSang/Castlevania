#include "Panther.h"
#include"Game.h"





void Panther::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + PANTHER_BBOX_WIDTH;
	b = t + PANTHER_BBOX_HEIGHT;
}

void Panther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (!isJumping && this->x < CGame::GetInstance()->GetCamera().left + SCREEN_WIDTH / 2) {
		SetState(PANTHER_STATE_RUNNING);
		this->isJumping = true;
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
		// Simple fall down
	vy += PANTHER_GRAVITY * dt;

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		if(this->isJumping && state==PANTHER_STATE_RUNNING)
		SetState(PANTHER_STATE_JUMP);
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.2f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.2f;
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Panther::Render()
{
	int ani = 0;
	if (state == PANTHER_STATE_LIEDOWN) {
		ani = PANTHER_ANI_LIEDOWN;
		animations[ani]->Render(nx, x, y);
		return;
	}
	if (state == PANTHER_STATE_JUMP) {
		ani = PANTHER_ANI_JUMP;
		animations[ani]->Render(nx, x, y);
		return;
	}
	if (state == PANTHER_STATE_RUNNING) {
		ani = PANTHER_ANI_RUNNING;
		animations[ani]->Render(nx, x, y);
		return;
	}
}

void Panther::SetState(int state)
{
	switch (state)
	{
	case PANTHER_STATE_LIEDOWN: 
	{
		vx = 0;
		vy = 0;
		break;
	}
	case PANTHER_STATE_JUMP:
	{
		vy = -PANTHER_JUMPING_SPEED;
		break;
	}
	case PANTHER_STATE_RUNNING: 
	{
		vx = -nx*PANTHER_RUNNING_SPEED;
		break;
	}
	}
}



Panther::~Panther()
{
}
