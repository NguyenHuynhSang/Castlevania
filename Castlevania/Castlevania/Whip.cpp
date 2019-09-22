#include "Whip.h"
#include"debug.h"
#include"Torch.h"
#include"Candle.h"
#include"Enemy.h"
#include"SceneManagement.h"	







void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	// Calculate dx, dy 
	if (animations[currentAnimation]->GetCurrentFrame()
		!= animations[currentAnimation]->GetLastFrame()) {
		return;
	}
	CGameObject::Update(dt);
	for (std::size_t i = 0; i < colliable_objects->size(); i++)
	{

		LPGAMEOBJECT e = colliable_objects->at(i);
		if (dynamic_cast<Torch *>(e))
		{
			Torch * f = dynamic_cast<Torch*> (e);
			if (CGameObject::IsColliding(this, f))
			{
				if (!f->CheckDestroyed()) {
					f->SetDestroy();
					//	DebugOut(L"Set destroy object \n");
				}

			}

		}
		else if (dynamic_cast<Candle *>(e))
		{
			Candle * f = dynamic_cast<Candle*> (e);
			if (CGameObject::IsColliding(this, f))
			{
				if (!f->CheckDestroyed()) {
					f->SetDestroy();
					//	DebugOut(L"Set destroy object \n");
				}

			}

		}
		else if (dynamic_cast<Enemy *>(e)) {
			Enemy * f = dynamic_cast<Enemy*> (e);
			if (CGameObject::IsColliding(this, f)) {
				f->SetDestroy();
			}

		}
	}
}




void Whip::Render()
{
	switch (this->state)
	{
	case WHIP_STATE_NORMAL: {
		currentAnimation = WHIP_ANI_NORMAL;
		break;
	}
	case WHIP_STATE_CHAIN: {
		currentAnimation = WHIP_ANI_CHAIN;
		break;

	}
	case WHIP_STATE_MORNINGSTAR: {
		currentAnimation = WHIP_ANI_MORNINGSTAR;
		break;
	}
	}
	animations[currentAnimation]->Render(nx, x, y);
	if (animations[currentAnimation]->GetCurrentFrame() == animations[currentAnimation]->GetLastFrame())
		RenderBoundingBox();
	return;
}

bool Whip::CheckLastFrame()
{
	return animations[currentAnimation]->CheckAnimationDone();
}



void Whip::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (nx > 0) {
		l = x + 60 * 2 + 12;
		t = y + 12;
	}
	else {
		if (state != WHIP_STATE_MORNINGSTAR)
			l = x + 55 - 4;
		else
			l = x + 55 - 30;
		t = y + 12;
	}


	switch (this->state)
	{
	case WHIP_STATE_NORMAL: {
		r = l + WHIP_BBOX_NORMAL_WIDTH;
		b = t + WHIP_BBOX_NORMAL_HEIGHT;
		break;
	}
	case WHIP_STATE_CHAIN: {
		r = l + WHIP_BBOX_CHAIN_WIDTH;
		b = t + WHIP_BBOX_CHAIN_HEIGHT;
		break;

	}
	case WHIP_STATE_MORNINGSTAR: {
		r = l + WHIP_BBOX_MORNINGSTAR_WIDTH;
		b = t + WHIP_BBOX_MORNINGSTAR_HEIGHT;
		break;
	}
	}

}

Whip::Whip()
{
	AddAnimation("WHIP_ANI_NORMAL");
	AddAnimation("WHIP_ANI_CHAIN");
	AddAnimation("WHIP_ANI_MORNINGSTAR");
	// set loop để khi render hết frame cuối k render lại frame 0
	this->animations[WHIP_ANI_NORMAL]->SetAnimationLoop(false);
	this->animations[WHIP_ANI_CHAIN]->SetAnimationLoop(false);
	this->animations[WHIP_ANI_MORNINGSTAR]->SetAnimationLoop(false);
}


Whip::~Whip()
{
}
