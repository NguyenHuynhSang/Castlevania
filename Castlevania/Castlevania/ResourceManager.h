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
class ResourceManager
{
	static ResourceManager * __instance;

	CSprites * sprites;
public:
	static ResourceManager * GetInstance();
	void LoadData(const std::string& filePath);
	void LoadSprites(const std::string& filePath, LPDIRECT3DTEXTURE9 tex);
	void LoadAnimations(const std::string& filePath, CAnimations* animations);
	ResourceManager();
	~ResourceManager();
};

