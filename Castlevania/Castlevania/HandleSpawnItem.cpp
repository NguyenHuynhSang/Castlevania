#include "HandleSpawnItem.h"
#include"Heart.h"
#include"MorningStar.h"
#include"SceneManagement.h"
#include"LargeHeart.h"
#include"DaggerItem.h"



HandleSpawnItem * HandleSpawnItem::__instance = NULL;


void HandleSpawnItem::SpawnItem(int itemDef, float x, float y, bool isHiding )
{
	
	switch (itemDef)
	{
	case ITDHeart: {
		item = new Heart(x);
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		SceneManagement::GetInstance()->SpawnItem(item);
		break;
	}
	case ITDLargeHeart: {
		item = new LargeHeart();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		SceneManagement::GetInstance()->SpawnItem(item);
		break;
	}
	case ITDDagger: {
		item = new DaggerItem();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		SceneManagement::GetInstance()->SpawnItem(item);
		break;
	}
	case ITDWhip: {
		item = new MorningStar();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		SceneManagement::GetInstance()->SpawnItem(item);
		break;
	}
	}
}

void HandleSpawnItem::SpawnRandomItem(float x, float y, bool isHiding)
{
	int rank = 0 + rand() % (200 + 1 - 0);
	if (rank<100)
	{
		item = new Heart(x);
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		SceneManagement::GetInstance()->SpawnItem(item);
	}
	else if (rank<150)
	{
		item = new LargeHeart();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		SceneManagement::GetInstance()->SpawnItem(item);
	}
	else if (rank<180)
	{
		item = new MorningStar();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		SceneManagement::GetInstance()->SpawnItem(item);
	
	}
	else
	{
		item = new DaggerItem();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		SceneManagement::GetInstance()->SpawnItem(item);
	}

}



HandleSpawnItem::HandleSpawnItem()
{
}


HandleSpawnItem::~HandleSpawnItem()
{
	delete item;
}

HandleSpawnItem * HandleSpawnItem::GetInstance()
{
	if (__instance == NULL) __instance = new HandleSpawnItem();
	return __instance;
}
