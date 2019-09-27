#include "Effects.h"


Effects::Effects()
{
	this->TurnOffCollision() ;
	this->lifetime_start = GetTickCount();
}


Effects::~Effects()
{
}
