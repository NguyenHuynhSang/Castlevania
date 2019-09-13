#pragma once
#ifndef CTileMap_
#define CTileMap_
#include"debug.h"
#include<map>
#include"Library/RapidXML/rapidxml.hpp"
#include"Library/RapidXML/rapidxml_utils.hpp"
#include "Textures.h"
#include"Sprites.h"
#include"Game.h"
#include"TileObject.h"
#include"TileSet.h"

using namespace rapidxml;
class CTileMap
{
	static CTileMap * __instance;
	unsigned int mapRow;
	unsigned int mapCol;
	int **matrix;
	int tileWidth;
	int tileHeight;
	unsigned int tileSheetCol;
	unsigned int tileSheetRow;
	// dùng lưu id của objectgroup và các object nằm trong group đó
	std::map<int,vector<LPTILEOBJECT>> listObject ; 
	std::map<unsigned int, LPTILESET> listTileSet;
	
public:
	void LoadTileSets(const std::string& filePath);
	void LoadMap(const std::string& filePath, LPDIRECT3DTEXTURE9 texTileSet);
	void Render();
	void LoadObjects(const std::string& filePath);
	std::map<unsigned int, LPTILESET>& GetTileSets() {
		return this->listTileSet;
	}
	std::map<int, vector<LPTILEOBJECT>>&  GetObjects() {
		return this->listObject;
	};
	static CTileMap * GetInstance();
	~CTileMap();
};

#endif