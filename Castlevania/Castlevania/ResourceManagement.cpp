#include "ResourceManagement.h"


ResourceManagement * ResourceManagement::__instance = NULL;

ResourceManagement *ResourceManagement::GetInstance()
{
	if (__instance == NULL) __instance = new ResourceManagement();
	return __instance;
}
ResourceManagement::ResourceManagement()
{
}


ResourceManagement::~ResourceManagement()
{
}
