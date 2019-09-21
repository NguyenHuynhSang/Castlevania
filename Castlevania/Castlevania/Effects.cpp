#include "Effects.h"
#include"Item.h"
#include"Heart.h"
#include"MorningStar.h"
#include"SceneManagement.h"
void Effects::SpawnItem()
{
	SceneManagement *scene = SceneManagement::GetInstance();
	Item * item;
	switch (this->itemDef)
	{
	case IDLargeHeart: {
		item = new Heart();
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case IDWhip: {
		item = new MorningStar();
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
	}
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
