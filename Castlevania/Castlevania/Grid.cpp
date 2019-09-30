#include "Grid.h"



void Grid::handleMelee()
{
	for (int x = 0; x < NUM_CELLS; x++)
	{
		for (int y = 0; y < NUM_CELLS; y++)
		{
			handleCell(cells_[x][y]);
		}
	}
}

void Grid::handleCell(Unit * unit)
{
	while (unit != NULL)
	{
		Unit* other = unit->next_;
		while (other != NULL)
		{
			if (unit->x_ == other->x_ &&
				unit->y_ == other->y_)
			{
				//handleAttack(unit, other);
			}
			other = other->next_;
		}

		unit = unit->next_;
	}
}

void Grid::Add(Unit * unit)
{
	//xác định unit thuộc cell nào

	int cellX = (int)(unit->x_ / CELL_SIZE);
	int cellY = (int)(unit->y_ / CELL_SIZE);
	unit->prev_ = NULL;
	unit->next_ = cells_[cellX][cellY];
	cells_[cellX][cellY] = unit;
	if (unit->next_!=NULL)
	{
		unit->next_->prev_ = unit;
	}
}


//to-do: Nếu unit ra khỏi cell thì remove unit tại cell đó
// và add vào cell tiếp
void Grid::Move(Unit * unit, float x, float y)
{
	//Tìm xem unit đang ở cell nào
	int oldCellX = (int)(unit->x_ / CELL_SIZE);
	int oldCellY = (int)(unit->y_ / CELL_SIZE);

	// Tìm xem unit di chuyển đến cell nào
	int cellX = (int)(x / CELL_SIZE);
	int cellY = (int)(y /CELL_SIZE);

	unit->x_ = x;
	unit->y_ = y;

	// nếu unit đứng yên return
	if (oldCellX == cellX && oldCellY == cellY) return;

	// xóa liên kết với cell cũ
	if (unit->prev_ != NULL)
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

Grid::Grid()
{
	//clean grid
	for (size_t i = 0; i < NUM_CELLS; i++)
	{
		for (size_t j = 0; j < NUM_CELLS; j++)
		{
			this->cells_[i][j] = NULL;
		}
	}
}


Grid::~Grid()
{
}

Unit::Unit(Grid * grid, float x, float y)
{
	this->grid = grid;
	this->x_ = x;
	this->y_ = y;
	this->prev_ = NULL;
	this->next_ = NULL;
	this->grid->Add(this);
}

void Unit::MoveTo(float newX, float newY)
{
	this->grid->Move(this, newX, newY);
}
