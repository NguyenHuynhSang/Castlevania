#pragma once

#include<Windows.h>
#include"debug.h"
#include<string>
#include"Library/RapidXML/rapidxml.hpp"
#include"Library/RapidXML/rapidxml_utils.hpp"
#include"TileSheet.h"
#include"Sprites.h"
#include<string>
#include"Textures.h"
class ResourceManagement
{
	static ResourceManagement * __instance;

	CSprites * sprites;
public:
	static ResourceManagement * GetInstance();
	void LoadSprites(const std::string& filePath);
	void LoadAnimations();
	void oldWayLoadResource();
	ResourceManagement();
	~ResourceManagement();
};

