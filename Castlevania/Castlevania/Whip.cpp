#include "Whip.h"
#include"debug.h"
#include"Torch.h"
#include"Zombie.h"
#include"SceneManagement.h"	
Whip * Whip::__instance = NULL;




Whip *Whip::GetInstance()
{
	if (__instance == NULL) __instance = new Whip();
	return __instance;
}
void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	// Calculate dx, dy 
	if (animations[WHIP_ANI_LV1]->GetCurrentFrame()
		!= animations[WHIP_ANI_LV1]->GetLastFrame()) {
		return;
	}
	CGameObject::Update(dt);
	for (int i = 0; i < colliable_objects->size(); i++)
	{

		LPGAMEOBJECT e = colliable_objects->at(i);
		if (dynamic_cast<Torch *>(e))
		{
			Torch * f = dynamic_cast<Torch*> (e);
			if (CGameObject::IsColliding(this, f) )
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

	animations[0]->Render(nx, x, y);
	if (animations[WHIP_ANI_LV1]->GetCurrentFrame()
		== animations[WHIP_ANI_LV1]->GetLastFrame()) {
		RenderBoundingBox();
	}
	DebugOut(L"Whip current frame =%d \n", animations[WHIP_ANI_LV1]->GetCurrentFrame());
	//RenderSpriteBox();
	return;
}

bool Whip::CheckLastFrame()
{
	return animations[WHIP_ANI_LV1]->CheckAnimationDone();
}



void Whip::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (nx > 0) {
		l = x + 60 * 2+2;
		t = y + 12;
	}
	else {
		l = x+55-2;
		t = y + 12;
	}

	r = l +64;
	b = t +20;
}

Whip::Whip()
{
	AddAnimation("WHIP_ANI_MORNINGSTAR");
	AddAnimation("WHIP_ANI_LV1");
	this->animations[0]->SetAnimationLoop(false);
}


Whip::~Whip()
{
}
