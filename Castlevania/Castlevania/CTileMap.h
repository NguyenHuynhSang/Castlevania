#pragma once
#include"debug.h"
#include"TileSheet.h"
#include "Textures.h"
#include"Sprites.h"
#include"Game.h"
#include"TileObject.h"

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
public:
	void LoadMap(const std::string& filePath);
	void Render();
	void LoadObjects(const std::string& filePath);
	std::map<int, vector<LPTILEOBJECT>>&  GetObjects() {
		return this->listObject;
	};
	static CTileMap * GetInstance();
	CTileMap();
	~CTileMap();
};


