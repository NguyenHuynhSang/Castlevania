#pragma once
#include"BBoxObjects.h"
class MoneyBagTrigger:public BBoxObject
{
private:
	float item_x;
	float item_y;
public:
	virtual void Render() {};
	 void SetItemPosition( float x, float y ){
		 this->item_x = x;
		 this->item_y = y;
	}
	 void SpawnMoneyBag();
	MoneyBagTrigger();
	~MoneyBagTrigger();
};

