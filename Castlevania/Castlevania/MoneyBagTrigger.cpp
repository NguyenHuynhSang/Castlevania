#include "MoneyBagTrigger.h"
#include"SceneManagement.h"
#include"Item.h"
#include"MoneyBag.h"
void MoneyBagTrigger::SpawnMoneyBag()
{
	Item* item = new MoneyBag();
	item->SetPosition(this->item_x, this->item_y);
	SceneManagement::GetInstance()->SpawnItem(item);
}

MoneyBagTrigger::MoneyBagTrigger()
{

}


MoneyBagTrigger::~MoneyBagTrigger()
{
}
