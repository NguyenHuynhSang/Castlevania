﻿#pragma once
#ifndef CTileMap_
#define CTileMap_
#include<map>
#include"Library/RapidXML/rapidxml.hpp"
#include"Library/RapidXML/rapidxml_utils.hpp"
#include"TileObject.h"
#include"TileSet.h"
#include"Sprites.h"
using namespace rapidxml;
class CTileMap
{
	static CTileMap * __instance;
	unsigned int mapRow;
	unsigned int mapCol;
	unsigned int mapWidth; // lấy đúng bằng cái tileset background ==
	unsigned int mapHeight; //==> nếu tileset k vẽ hết map=> Lỗi
	int **matrix;
	int tileWidth;
	int tileHeight;
	unsigned int tileSheetCol;
	unsigned int tileSheetRow;
	// dùng lưu id của objectgroup và các object nằm trong group đó
	std::map<int,std::vector<LPTILEOBJECT>> listObject ; 
	std::map<unsigned int, LPTILESET> listTileSet;
	
public:
	void LoadTileSets(const std::string& filePath);
	void LoadMap(const std::string& filePath, LPDIRECT3DTEXTURE9 texTileSet);
	void Render();
	void LoadObjects(const std::string& filePath);
	void ClearObject() {
		this->listObject.clear();
	}
	unsigned int GetMapWidth() {
		return this->mapWidth;
	}
	unsigned int GetMapHeight() {
		return this->mapHeight;
	}
	std::map<unsigned int, LPTILESET>& GetTileSets() {
		return this->listTileSet;
	}
	std::map<int, std::vector<LPTILEOBJECT>>&  GetObjects() {
		return this->listObject;
	};
	static CTileMap * GetInstance();
	~CTileMap();
};

#endif