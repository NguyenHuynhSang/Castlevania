#include "TileObject.h"


ObjectLayer * ObjectLayer::__instance = NULL;

ObjectLayer *ObjectLayer::GetInstance()
{
	if (__instance == NULL) __instance = new ObjectLayer();
	return __instance;
}




TileObject::~TileObject()
{
}

void TileObject::AddProperty(std::string name, int value)
{
	this->properties.insert(std::make_pair(name, value));
}
