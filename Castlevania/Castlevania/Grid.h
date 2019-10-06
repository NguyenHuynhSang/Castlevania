#pragma once
#include<vector>
#include"GameObject.h"
#include<vector>
#define CELL_SIZE  256

class Unit
{
	friend class Grid;
	float x_;
	float y_;
	Grid* grid_;
	// ds lien ket doi
	Unit* prev_;
	Unit* next_;
public:
	Unit(Grid * grid, float x, float y);
	~Unit();
};


class Grid
{
private:
	unsigned int mapWidth;
	unsigned int mapHeight;
	unsigned int cellSize= CELL_SIZE;

	unsigned int numXCell;
	unsigned int numYcell;

	std::vector<std::vector<Unit *>> cells_;
public:
	void Add(Unit *unit);
	void Move(Unit *unit,float x,float y);
	Grid(unsigned int mapWidth, unsigned int mapHeight);
	~Grid();
};

