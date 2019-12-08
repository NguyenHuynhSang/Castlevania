#pragma once
#include"CTileMap.h"
#include "Textures.h"
#include<Windows.h>
#include<string>
class MapManager
{
	static MapManager* _instance;
	unordered_map<std::string, CTileMap*> tileMaps;
public:
	void AddMap(string MapID, const std::string& filePath, LPDIRECT3DTEXTURE9 texTileSet);
	CTileMap* Get(std::string ID) { return tileMaps[ID]; }
	unordered_map<std::string, CTileMap*> const* GetMaps() {
		return &this->tileMaps;
	
	};
	static MapManager* GetInstance();
};

