#include "Grid.h"

Unit::Unit(Grid * gird, float x, float y)
	: grid_(gird),
	x_(x),
	y_(y)
{
	grid_->Add(this);
}

void Grid::Add(Unit * unit)
{
	//tính vị trí của unit
	int cellX = (int)(unit->x_ / Grid::cellSize);
	int cellY = (int)(unit->y_ / Grid::cellSize);

	// thêm vào trước ds unit ở ô đó
	unit->prev_ = NULL;
	unit->next_ = cells_[cellX][cellY];
	cells_[cellX][cellY] = unit;

	// đã có 1 list unit ở đó
	if (unit->next_ != NULL)
	{
		unit->next_->prev_ = unit;
	}
}

void Grid::Move(Unit * unit, float x, float y)
{
	// tìm vị trí củ của cell chứa unit 
	int oldCellX = (int)(unit->x_ / Grid::cellSize);
	int oldCellY = (int)(unit->y_ / Grid::cellSize);

	// xem unit h đang ở cell nào
	int cellX = (int)(x / Grid::cellSize);
	int cellY=(int)(y / Grid::cellSize);


	// cập nhật lại vị trí
	// set lại vị trí vì có thể object di chuyển một khoảng nhỏ
	// nhưng vẫn nằm trong cell cũ
	unit->x_ = x;
	unit->y_ = y;

	// nếu k ra khỏi cell 
	if (oldCellX==cellX &&oldCellY==cellY)
	{
		return;
	}

	// bỏ liên kết của unit với cell cũ
	if (unit->prev_!=NULL)
	{
		unit->prev_->next_ = unit->next_;
	}
	if (unit->next_ != NULL)
	{
		unit->next_->prev_ = unit->prev_;
	}

	// If it's the head of a list, remove it.

	if (cells_[oldCellX][oldCellY] == unit)
	{
		cells_[oldCellX][oldCellY] = unit->next_;
	}

	// Add it back to the grid at its new cell.
	Add(unit);




}

Grid::Grid(unsigned int mapWidth, unsigned int mapHeight) :
	mapWidth(mapWidth),
	mapHeight(mapHeight)
{
	this->numXCell = mapWidth / cellSize;
	this->numYcell = mapHeight / cellSize;
	// clear grid
	for (size_t i = 0; i < numXCell; i++)
	{
		for (size_t j = 0; j < numYcell; j++)
		{
			this->cells_[i][j] = NULL;
		}
	}

}

Grid::~Grid()
{
}

