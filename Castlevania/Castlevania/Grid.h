﻿#pragma once
#include<vector>
#include"GameObject.h"
#include<vector>
#include<Windows.h>
#define CELL_SIZE  256
class Grid;
class Unit
{
	friend class Grid;
	float x_;
	float y_;
	Grid* grid_=nullptr;

	LPGAMEOBJECT object;

	// ds lien ket doi
	Unit* prev_=NULL;
	Unit* next_ = NULL;
public:
	Unit(Grid * grid, LPGAMEOBJECT object,bool isAlwayUpdate=false);
	LPGAMEOBJECT const  GetGameObject() {
		return this->object;
		
	}

	~Unit();
};


class Grid
{
private:
	unsigned int mapWidth;
	unsigned int mapHeight;
	unsigned int cellSize= CELL_SIZE;

	unsigned int numXCell;
	unsigned int numYCell;

	// mang 2 chieu luu unit
	// trong cell co the co nhieu unit 
	std::vector<std::vector<Unit *>> cells_;
	Unit* alwaysUpdateUnit;
	void RenderCell(RECT rec, MYCOLOR color, int alpha = 64);
public:
	void Add(Unit *unit);
	void AddToAlwayUpdateUnit(Unit* unit);
	void Update(Unit *unit,float x,float y);
	void Update(float dt);
	void GetListUnit(vector<Unit*>& listUnits);
	Grid(unsigned int mapWidth, unsigned int mapHeight);
	void Render();
	void RemoveUnit(Unit* unit);
	~Grid();
};

