#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"

#include "Goomba.h"
#include"Brick.h"
void CSimon::Renderer(int ani)
{
	int alpha = 255;
	if (untouchable) alpha = 128;
	animations[ani]->Render(nx, x, y, alpha);

	RenderBoundingBox();
	RenderSpriteBox();// = tọa độ simon trong world game để tính vị trí so với các object khác
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY * dt;
	if (state == SIMON_STATE_STAND_ATTACK) {
		whip->Update(dt);
	}


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		//	DebugOut(L"SIMON ny=%f", ny);
			// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick *>(e->obj)) {
				if (e->ny < 0) {
					this->isJumping = false; // cham dat moi cho nhay tiep
					if (GetActack_Time() != 0) { // còn đang đánh thì dừng lại
						vx = 0;
					}
				
				} 
				
			}
			else if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);
				//DebugOut(L"[col] SIMON ->Goomba \n");
				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						//	goomba->SetState(GOOMBA_STATE_DIE);
						vy = -SIMON_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{

					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							if (level > SIMON_LEVEL_SMALL)
							{
								level = SIMON_LEVEL_SMALL;
								StartUntouchable();
							}
							else
								SetState(SIMON_STATE_DIE);
						}
					}
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	whip->SetPosition(x, y);
}

void CSimon::Render()
{
	//DebugOut(L"Pos x=%f y=%f \n",x,y);
	int ani;
	if (state == SIMON_STATE_STAND_ATTACK) {
		ani = SIMON_ANI_STAND_ATTACK;
		whip->SetPosition(x - 1.5*SIMON_SPRITE_BOX_WIDTH, y);
		whip->SetDirection(nx);
		whip->Render();
		Renderer(ani);
		return;
	}
	if (state == SIMON_STATE_SIT) {
		ani = SIMON_ANI_SITTING;
		Renderer(ani);
		return;
	}
	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else
		if (level == SIMON_LEVEL_BIG)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = SIMON_ANI_BIG_IDLE_RIGHT;
				else ani = SIMON_ANI_BIG_IDLE_RIGHT;
			}
			else if (vx > 0)
				ani = SIMON_ANI_BIG_WALKING_RIGHT;
			else ani = SIMON_ANI_BIG_WALKING_RIGHT;
		}
		else if (level == SIMON_LEVEL_SMALL)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = SIMON_ANI_BIG_IDLE_RIGHT;
				else ani = SIMON_ANI_BIG_IDLE_RIGHT;
			}
			else if (vx > 0)
				ani = SIMON_ANI_BIG_WALKING_RIGHT;
			else ani = SIMON_ANI_BIG_WALKING_RIGHT;
		}

	Renderer(ani);
	//DebugOut(L"ani=%d", ani);
	return;
}



void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
	{
		vy = -SIMON_JUMP_SPEED_Y;
		isJumping = true;
		break;
	}

	case SIMON_STATE_STAND_ATTACK:
	{
		if (!this->isJumping) vx = 0;
		break;
	}
	case SIMON_STATE_SIT:
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;

	}
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x + 10;

	top = y;


	right = left + SIMON_BIG_BBOX_WIDTH;
	bottom = top + SIMON_BIG_BBOX_HEIGHT;




	/*left += 10;
	top += 10;*/

	//	DebugOut(L"BBOX l=%f t=%f r=%f b=%f \n ",left, top,right,bottom);
}

