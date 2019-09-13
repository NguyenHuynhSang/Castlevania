#include "BoundMap.h"



void BoundMap::Render()
{
}

void BoundMap::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + this->width;
	b = t + this->height;
}

BoundMap::BoundMap()
{
}


BoundMap::~BoundMap()
{
}
