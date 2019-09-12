#include "TileObject.h"


ObjectGroup * ObjectGroup::__instance = NULL;

ObjectGroup *ObjectGroup::GetInstance()
{
	if (__instance == NULL) __instance = new ObjectGroup();
	return __instance;
}




TileObject::~TileObject()
{
}
