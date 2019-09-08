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

using Layer = std::vector<Tile>;
using MapTiles = std::map<std::string, Layer>; //Luu tru tung ten layer
using TileSet= std::unordered_map< int, std::shared_ptr<TileInfo>>;