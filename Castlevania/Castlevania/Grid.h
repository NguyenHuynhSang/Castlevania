#pragma once
#include<vector>

#define NUM_CELLS  10
#define CELL_SIZE  20
class Grid
{
private:
	int cellWidth;
	int cellHeight;
	int mapWidth;
	int mapHeight;
	Unit* cells_[NUM_CELLS][NUM_CELLS];
public:
	Grid();
	~Grid();
};

class Unit {
	friend class Grid;
	//init unit thuoc grid
public:
	Unit(Grid* grid, float x, float y);
	
	void MoveTo(float newX, float newY);

private:
	//mỗi unit có position và thuộc grid nào
	float _x;
	float _y;
	Grid* gird;

	// Tạo thành dslk đôi
	Unit* prev_;
	Unit* next_;
};
