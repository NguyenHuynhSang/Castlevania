#pragma once

#include<Windows.h>
#include"debug.h"
#include<string>
#include"Library/RapidXML/rapidxml.hpp"
#include"Library/RapidXML/rapidxml_utils.hpp"
#include"Sprites.h"
#include<string>
#include"Textures.h"
using namespace rapidxml;
class ResourceManagement
{
	static ResourceManagement * __instance;

	CSprites * sprites;
public:
	static ResourceManagement * GetInstance();
	void LoadSprites(const std::string& filePath, LPDIRECT3DTEXTURE9 tex);
	void LoadAnimations(const std::string& filePath, CAnimations* animations);
	ResourceManagement();
	~ResourceManagement();
};

