#ifndef TileSheetInfo
#define TileSheetInfo

#include<d3dx9.h>
#include"Library/RapidXML/rapidxml.hpp"
#include"Library/RapidXML/rapidxml_utils.hpp"
#include"Tile.h"
#include <unordered_map>
#include<map>
using namespace rapidxml;

struct TileSheetInfo
{
	int textureID;
	D3DXVECTOR2 textureSize; //size of image
	unsigned int columns;
	unsigned int rows;
	unsigned int tileWidth;
	unsigned int tileHeight;
};


using Layer = std::vector<std::shared_ptr<Tile>>;
using MapTiles = std::map<std::string, std::shared_ptr<Layer>>; //Luu tru tung ten layer theo thu tu
using TileSet= std::unordered_map<int, std::shared_ptr<TileInfo>>; //' k co thu tu
#endif
