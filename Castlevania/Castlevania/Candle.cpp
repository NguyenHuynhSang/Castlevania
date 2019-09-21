#include "Candle.h"



Candle::Candle()
{
}


Candle::~Candle()
{
}

void Candle::Render()
{
}

void Candle::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = t + CANDLE_BBOX_WIDTH;
	b = t + CANDLE_BBOX_HEIGHT;
}
