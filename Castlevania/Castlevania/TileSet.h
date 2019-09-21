#pragma once
#ifndef CTileSet_
#define CTileSet_
#include<string>
class CTileSet {
private:
	unsigned int firstgid;
	std::string name;
	unsigned int tilewidth;
	unsigned int tileheight;
	unsigned int tilecount;
	unsigned int  columns;
	std::string source;
	unsigned int texWidth;
	unsigned int texHeight;
public:
	~CTileSet();
	CTileSet() {
		firstgid = tilewidth = tileheight = tilecount = columns = texWidth = texHeight = 0;
		name = source = "";
	}

	CTileSet(int firstgid, std::string name, unsigned int tilewidth, unsigned int tileheight,
		unsigned int tilecount, unsigned int  columns, std::string source, unsigned int tileWidth,
		unsigned int TileHeight) :firstgid(firstgid), name(name), tilewidth(tilewidth), tileheight(tileheight),
		tilecount(tilecount), columns(columns), source(source), texWidth(texWidth), texHeight(texHeight) {}
	unsigned int GetTileSetID();
};
typedef CTileSet* LPTILESET;
#endif


