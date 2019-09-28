#pragma once
#include"Effects.h"



#define SCORETEXT_ANI_100 0
#define SCORETEXT_ANI_400 1
#define SCORETEXT_ANI_700 2
#define SCORETEXT_ANI_1000 3

class ScoreText:public Effects
{
public:
	virtual void Render();
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	ScoreText();
	ScoreText(int state);
	~ScoreText();
};

