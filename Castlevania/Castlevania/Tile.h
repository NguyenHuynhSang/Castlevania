
#include <d3dx9.h>
#include<memory>
using namespace std;
//  flyweight pattern
// tile Share cac properties tileID va textureID
struct CRectangle {
	int top;
	int left;
	int right;
	int button;
	CRectangle() {};
	CRectangle(int t, int l, int r, int b) : top(t), left(l), right(r), button(b) {};
};

struct TileInfo
{
	TileInfo() :tileID(-1) {

	}
	TileInfo(int texID, unsigned int tileID, CRectangle textureRect) :textureID(texID)
		, tileID(tileID)// tileID trong Tiled luon danh so tu 0
		, textureRect(textureRect) {

	}
	int tileID;
	
	int textureID;
	CRectangle textureRect;
};




struct Tile
{
	std::shared_ptr<TileInfo>  tileProperties;
	int x;
	int y;
}; 

