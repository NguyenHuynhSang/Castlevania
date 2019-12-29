#pragma once
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
	string mapID;
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
	std::unordered_map<std::string,std::vector<LPTILEOBJECT>> listObject ; 
	std::unordered_map<unsigned int, LPTILESET> listTileSet;
	void LoadMap(const std::string& filePath, LPDIRECT3DTEXTURE9 texTileSet);
	void LoadObjects(const std::string& filePath);
public:
	void LoadTileSets(const std::string& filePath);
	void Render();
	void LoadGameData(const std::string& filePath, LPDIRECT3DTEXTURE9 texTileSet, string mapID);
	void ClearObject() {
		this->listObject.clear();
	}
	unsigned int GetMapWidth() {
		return this->mapWidth;
	}
	unsigned int GetMapHeight() {
		return this->mapHeight;
	}
	std::unordered_map<unsigned int, LPTILESET>& GetTileSets() {
		return this->listTileSet;
	}
	std::unordered_map<std::string, std::vector<LPTILEOBJECT>>&  GetObjects() {
		return this->listObject;
	};
	~CTileMap();
};

#endif