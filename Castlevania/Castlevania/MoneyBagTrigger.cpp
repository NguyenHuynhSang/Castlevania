#include "MoneyBagTrigger.h"
#include"HandleSpawnItem.h"
void MoneyBagTrigger::SpawnMoneyBag()
{
	HandleSpawnItem::GetInstance()->SpawnItem(ITDMONEYBAGFULLCOLOR,this->item_x,this->item_y,false);
}

MoneyBagTrigger::MoneyBagTrigger()
{

}


MoneyBagTrigger::~MoneyBagTrigger()
{
}
