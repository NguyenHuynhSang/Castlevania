#include "Effects.h"
#include"Item.h"
#include"Heart.h"
#include"MorningStar.h"
#include"SceneManagement.h"
void Effects::SpawnItem()
{
	SceneManagement *scene = SceneManagement::GetInstance();
	Item * item;
	if (itemName == "bigheart") {
		
		item = new Heart();
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
	}
	else if (itemName == "whip") {
		item = new MorningStar();
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
	}
}

Effects::Effects()
{
	this->TurnOffCollision() ;
	this->lifetime_start = GetTickCount();
}


Effects::~Effects()
{
}
