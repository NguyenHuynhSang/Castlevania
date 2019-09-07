#pragma once

#include<Windows.h>
#include"debug.h"
class ResourceManagement
{
	static ResourceManagement * __instance;
public:
	static ResourceManagement * GetInstance();
	void LoadSprites();
	void LoadAnimations();
	ResourceManagement();
	~ResourceManagement();
};

