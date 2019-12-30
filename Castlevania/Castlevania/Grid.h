#pragma once
#include<vector>
#include"GameObject.h"
#include<vector>
#include<Windows.h>
#define CELL_SIZE  256
typedef std::vector<LPGAMEOBJECT> cellObjects;





class Grid
{
private:
	unsigned int mapWidth;
	unsigned int mapHeight;
	unsigned int cellSize= CELL_SIZE;

	unsigned int numXCell;
	unsigned int numYCell;

	// mang 2 chieu luu object
	// trong cell co the co nhieu object 
	std::vector<std::vector<cellObjects>> cells_;
	std::vector<LPGAMEOBJECT> alwaysUpdateobject;
	void RenderCell(RECT rec, MYCOLOR color, int alpha = 64);
public:
	void Add(LPGAMEOBJECT object);
	void AddToAlwayUpdateObjects(LPGAMEOBJECT object);
	void Update(LPGAMEOBJECT object);
	void Update(float dt);
	void GetListobject(vector<LPGAMEOBJECT>& listobjects);
	Grid(unsigned int mapWidth, unsigned int mapHeight);
	void Render();
	~Grid();
};

