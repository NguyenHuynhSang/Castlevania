#include "ScoreText.h"



void ScoreText::Render()
{
	int ani = 0;
	if (state==SCORETEXT_STATE_100)
	{
		ani = SCORETEXT_ANI_100;
	}
	else if (state == SCORETEXT_STATE_400)
	{
		ani = SCORETEXT_ANI_400;
	}
	else if (state == SCORETEXT_STATE_700)
	{
		ani = SCORETEXT_ANI_700;
	}
	else
	{
		ani = SCORETEXT_ANI_1000;
	}
	animations[ani]->Render(0, x, y);
}

void ScoreText::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = t = r = b = 0;
}

void ScoreText::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroyed) return;
	UpdateEffect();
	if (this->setDestroy) {
		this->isDestroyed = true;
	}
}

ScoreText::ScoreText() :Effects()
{
	AddAnimation("SCORETEXT_ANI_100");
	AddAnimation("SCORETEXT_ANI_400");
	AddAnimation("SCORETEXT_ANI_700");
	AddAnimation("SCORETEXT_ANI_1000");
}

ScoreText::ScoreText(int state) : Effects()
{
	AddAnimation("SCORETEXT_ANI_100");
	AddAnimation("SCORETEXT_ANI_400");
	AddAnimation("SCORETEXT_ANI_700");
	AddAnimation("SCORETEXT_ANI_1000");
	this->state = state;
}


ScoreText::~ScoreText()
{
}
