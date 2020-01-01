#pragma once

#include<Windows.h>
#include"debug.h"
#include<string>
#include"Library/RapidXML/rapidxml.hpp"
#include"Library/RapidXML/rapidxml_utils.hpp"
#include"Library/RapidXML/rapidxml_print.hpp"

#include"Sprites.h"
#include<string>
#include<unordered_map>
#include"Textures.h"
using namespace rapidxml;
class PlayScene;
class MiniScene;
class ResourceManager
{
	static ResourceManager * __instance;

	CSprites * sprites;
public:
	static ResourceManager * GetInstance();
	void BuildGrid(const std::string& filePath);
	void LoadData(const std::string& filePath);
	void LoadSceneData(const std::string& filePath, std::unordered_map<int, MiniScene*>& miniScene);
	void LoadSprites(const std::string& filePath, LPDIRECT3DTEXTURE9 tex);
	void LoadAnimations(const std::string& filePath, CAnimations* animations);
	ResourceManager();
	~ResourceManager();
};

