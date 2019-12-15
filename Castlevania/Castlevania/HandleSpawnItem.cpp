#include "HandleSpawnItem.h"
#include"Heart.h"
#include"MorningStar.h"
#include"PlayScene.h"
#include"LargeHeart.h"
#include"DaggerItem.h"
#include"MoneyBag.h"
#include"AxeItem.h"
#include"IStopWatch.h"
#include"PorkChop.h"
#include"InvisibilityPotion.h"
#include"Cross.h"
#include"IHolyWater.h"
#include"MultiplyShotItem.h"
HandleSpawnItem * HandleSpawnItem::__instance = NULL;

void HandleSpawnItem::SpawnItem(int itemDef, float x, float y, bool isHiding )
{
	Item * item;
	DebugOut(L"Spawn item \n");
	switch (itemDef)
	{
	case ITDHeart: {
		item = new Heart(x);
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case ITDLargeHeart: {
		item = new LargeHeart();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case ITDDagger: {
		item = new DaggerItem();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case ITDAXE: {
		item = new AxeItem();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case ITDWhip: {
		item = new MorningStar();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}

	case ITDMONEYBAGFULLCOLOR: {
		item = new MoneyBag();
		item->SetState(MONEYBAG_STATE_FULLCOLOR);
		item->SetIsHiding(isHiding);
		item->SetPosition(x, y); // vì tọa độ được load vào chưa -80
		scene->SpawnItem(item);
		break;
	}
	case ITDMONEYBAGWHITE: {
		item = new MoneyBag();
		item->SetState(MONEYBAG_STATE_WHITE);
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case  ITDMONEYBAGBLUE: 
	{
		item = new MoneyBag();
		item->SetState(MONEYBAG_STATE_BLUE);
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case  ITDMONEYBAGRED:
	{
		item = new MoneyBag();
		item->SetState(MONEYBAG_STATE_RED);
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case ITDSTOPWATCH: {
		item = new IStopWatch();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case ITDROAST: {
		item = new PorkChop();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case ITDIPOTION: {
		item = new InvisibilityPotion();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case ITDCROSS: {
		item = new Cross();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case ITDHOLYWATER: {
		item = new IHolyWater();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	case ITDMULTIFLYSHOT: {
		item = new MultiplyShotItem();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
		break;
	}
	}
}

void HandleSpawnItem::SpawnRandomItem(float x, float y, bool isHiding)
{
	Item * item;
	DebugOut(L"Spawn random item \n");
	int rank = 0 + rand() % (300 + 1 - 0);
	if (rank<100)
	{
		item = new Heart(x);
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
	}
	else if (rank<150)
	{
		item = new LargeHeart();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
	}
	else if (rank<180)
	{
		item = new MoneyBag();
		item->SetState(MONEYBAG_STATE_RED);
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
	
	}
	else if (rank<200)
	{
		item = new MoneyBag();
		item->SetState(MONEYBAG_STATE_WHITE);
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
	}
	else if (rank < 240) 
	{
		item = new AxeItem();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
	}
	else if (rank<280)
	{
		item = new IStopWatch();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
	}
	else if (rank<290)
	{
		item = new IHolyWater();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
	}
	else {
		item = new Cross();
		item->SetIsHiding(isHiding);
		item->SetPositionInWorld(x, y);
		scene->SpawnItem(item);
	}

}



HandleSpawnItem::HandleSpawnItem()
{
}


HandleSpawnItem::~HandleSpawnItem()
{
	delete scene;
}

HandleSpawnItem * HandleSpawnItem::GetInstance()
{
	if (__instance == NULL) __instance = new HandleSpawnItem();
	return __instance;
}
