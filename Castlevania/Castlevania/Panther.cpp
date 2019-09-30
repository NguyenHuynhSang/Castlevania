#include "Panther.h"
#include"Game.h"
#include"Ground.h"




void Panther::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + PANTHER_BBOX_WIDTH;
	b = t + PANTHER_BBOX_HEIGHT;
}

void Panther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroyed)
	{
		return;
	}
	if (this->setDestroy)
	{
		this->isDestroyed = true;
		this->UpdateEnemy();
		return;
	}

	if (this->isFreeze)
	{
		return;
	}
	if (!this->isActive)
	{
		if (state == PANTHER_STATE_LIEDOWN && this->x < CGame::GetInstance()->GetCamera().left + SCREEN_WIDTH / 2 + 150) {
			SetState(PANTHER_STATE_RUNNING);
			this->isActive = true;
		}
	
	}
	//DebugOut(L"this->nx=%d \n", this->nx);
	CGameObject::Update(dt);
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
// 
	// Simple fall down
	vy += PANTHER_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	//


	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		if (state == PANTHER_STATE_RUNNING) {
			SetState(PANTHER_STATE_JUMP);
		}

	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.2f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame

		y += min_ty * dy + ny * 0.2f;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground *>(e->obj)) {
				if (e->ny == -1) {
					if (state  == PANTHER_STATE_JUMP)
					{
						this->nx = -this->nx; // đổi hướng
						this->SetState(PANTHER_STATE_RUNNING);
						//vx = -PANTHER_RUNNING_SPEED;
					}
					else if (state == PANTHER_STATE_LIEDOWN)
					{
						//nếu đang nằm set lại vy để frame tiếp theo
						//k va chạm với object khác
						if (ny != 0) vy = 0;
					}
			
				}
				else {
					x += dx;
					y += dy;
					//if (nx != 0) vx = 0;
				//	if (ny != 0) vy = 0;
				}
			}
			else
			{
				if (e->nx != 0)
					x += dx;
				else if (e->ny != 0)
				{
					y += dy;
				}
			}
		}

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Panther::Render()
{
	RenderBoundingBox();
	int ani = 0;
	if (state == PANTHER_STATE_LIEDOWN) {
		ani = PANTHER_ANI_LIEDOWN;
		animations[ani]->Render(nx, x, y);
		return;
	}
	else if (state == PANTHER_STATE_JUMP) {
		ani = PANTHER_ANI_JUMP;
		animations[ani]->Render(nx, x, y);
		return;
	}
	else if (state == PANTHER_STATE_RUNNING) {
		ani = PANTHER_ANI_RUNNING;
		animations[ani]->Render(nx, x, y);
		return;
	}
}

void Panther::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PANTHER_STATE_LIEDOWN:
		vx = 0;
		vy = 0;
		break;
	case PANTHER_STATE_JUMP:
		vy = -PANTHER_JUMPING_SPEED;
		break;
	case PANTHER_STATE_RUNNING:
		vx = nx > 0 ? -PANTHER_RUNNING_SPEED : PANTHER_RUNNING_SPEED;
		// truyền vy vào để xét va chạm theo trục y tức là nó vẫn sẽ
		//trả về va chạm khi đang trên ground
		//dùng để check k còn trên ground => jump
		vy = PANTHER_JUMPING_SPEED;
		break;
	}
}



Panther::~Panther()
{
}
