#include "Effects.h"
#include"Item.h"
#include"Heart.h"
#include"SceneManagement.h"
void Effects::SpawnItem()
{
	SceneManagement *scene = SceneManagement::GetInstance();
	if (itemName == "bigheart") {
		Item * item;
		item = new Heart();
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
