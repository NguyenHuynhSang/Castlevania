#include "Brick.h"
#include"debug.h"
#include"Effects.h"
#include"DebrisBrick.h"
#include"SceneManagement.h"
CBrick::CBrick()
{
	AddAnimation("BRICK_ANI_NORMAL");
	AddAnimation("BRICK_ANI_BREAKING");
}



CBrick::~CBrick()
{
}

void CBrick::Render()
{
	
	int ani = 0;
	if (state==BRICK_STATE_NORMAL)
	{
		ani = BRICK_ANI_NORMAL;
	}
	else
	{
		ani = BRICK_ANI_BREAKING;
	}
	animations[ani]->Render(0,x, y);
	RenderBoundingBox();
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroyed) {
		return;
	}
	if (this->setDestroy) {
		Effects * effect;
		for (size_t i = 0; i < 4; i++)
		{
			//rank tu -0.1->0.2
			float vx = (float)(-100 + rand() % 200) / 1000;
			float vy = (float)(-100 + rand() % 200) / 1000;
			effect = new DebrisBrick(vx,vy);
			effect->SetPositionInWorld(this->x, this->y);
			SceneManagement::GetInstance()->SpawnEffect(effect);
		}



		isDestroyed = true;
	}
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

