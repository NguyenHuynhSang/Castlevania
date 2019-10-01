#pragma once
#include<vector>
#define NUM_CELLS  10
#define CELL_SIZE  20

class Unit {
	friend class Grid;
	//init unit thuoc grid
public:
	Unit(Grid* grid, float x, float y);
	void MoveTo(float newX, float newY);
private:
	//mỗi unit có position và thuộc grid nào
	float x_;
	float y_;
	Grid* grid;
	// Tạo thành dslk đôi
	Unit* prev_;
	Unit* next_;
};
class Grid
{
private:
	int cellWidth;
	int cellHeight;
	int mapWidth;
	int mapHeight;

	int numCellCol;
	int numCellRow;
	std::vector<std::vector<Unit*>> cells_;
public:
	void handleMelee();
	void handleCell(Unit* unit);
	void Add(Unit* unit);
	void Move(Unit* unit, float x, float y);
	Grid();
	~Grid();
};

