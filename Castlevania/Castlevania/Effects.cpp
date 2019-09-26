#include "Effects.h"
#include"Item.h"
#include"Heart.h"
#include"MorningStar.h"
#include"SceneManagement.h"
#include"LargeHeart.h"
#include"DaggerItem.h"
void Effects::SpawnItem()
{
	SceneManagement *scene = SceneManagement::GetInstance();
	Item * item;
	switch (this->itemDef)
	{
	case IDHeart: {
		item = new Heart(this->x);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case IDLargeHeart: {
		item = new LargeHeart();
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case IDWhip: {
		item = new MorningStar();
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case IDDagger: {
		item = new DaggerItem();
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
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
