#pragma once
#include"debug.h"
#include"TileSheet.h"
#include "Textures.h"
#include"Sprites.h"
#include"Game.h"
class CTileMap
{
	unsigned int mapRow;
	unsigned int mapCol;
	int **matrix;

	int tileWidth;
	int tileHeight;


	unsigned int tileSheetCol;
	unsigned int tileSheetRow;

public:
	void LoadMap(const std::string& filePath);
	void Render();
	CTileMap();
	~CTileMap();
};

class TileObject {
private:

public:
	int id;
	string name;
	string type;
	std::unordered_map<string, int> properties;
	int x;
	int y;
	unsigned int width;
	unsigned int height;
};

class ObjectGroup {
private:
	int id;
	string name;
	string type;
	std::unordered_map<int, std::shared_ptr<TileObject>> listobject;
public:
};