#include "Grid.h"
#include"Camera.h"
Unit::Unit(Grid * gird, LPGAMEOBJECT object, float x, float y)
	: grid_(gird),
	object(object),
	x_(x),
	y_(y)
{
	grid_->Add(this);
}

Unit::~Unit()
{
}

void Grid::Add(Unit * unit)
{
	//tính vị trí của unit
	int cellX = (int)(unit->x_ / this->cellSize);
	int cellY = (int)(unit->y_ / this->cellSize);

	// thêm vào trước ds unit ở ô đó
	unit->prev_ = NULL;
	unit->next_ = cells_[cellY][cellX];
	cells_[cellY][cellX] = unit;

	// đã có 1 list unit ở đó
	if (unit->next_ != NULL)
	{
		unit->next_->prev_ = unit;
	}
}

void Grid::Move(Unit * unit, float x, float y)
{
	// tìm vị trí củ của cell chứa unit 
	int oldCellX = (int)(unit->x_ / this->cellSize);
	int oldCellY = (int)(unit->y_ / this->cellSize);

	// xem unit h đang ở cell nào
	int cellX = (int)(x / this->cellSize);
	int cellY = (int)(y / this->cellSize);


	// cập nhật lại vị trí
	// set lại vị trí vì có thể object di chuyển một khoảng nhỏ
	// nhưng vẫn nằm trong cell cũ
	unit->x_ = x;
	unit->y_ = y;

	// nếu k ra khỏi cell 
	if (oldCellX == cellX && oldCellY == cellY)
	{
		return;
	}

	// bỏ liên kết của unit với cell cũ
	if (unit->prev_ != NULL)
	{
		unit->prev_->next_ = unit->next_;
	}
	if (unit->next_ != NULL)
	{
		unit->next_->prev_ = unit->prev_;
	}

	// If it's the head of a list, remove it.

	if (cells_[oldCellY][oldCellX] == unit)
	{
		cells_[oldCellY][oldCellX] = unit->next_;
	}

	// Add it back to the grid at its new cell.
	Add(unit);




}

void Grid::Update(float dt)
{
	for (int i = 0; i < numYcell; i++)
	{
		for (int j = 0; j < numXCell; j++)
		{
			Unit * unit = this->cells_[i][j];

			// chi render nhung cell co unit
			while (unit != NULL)
			{
				
			}
		}
	}
}

void Grid::GetListUnit(vector<Unit*>& listUnits)
{

	float camx, camy;
	Camera::GetInstance()->GetCamera(camx, camy);
	int startCol = camx / this->cellSize;
	int endCol = ceil((float)(camx + SCREEN_WIDTH) / this->cellSize);
	for (int i = 0; i < this->numYcell; i++)
	{
		for (int j = startCol; j < endCol; j++)
		{
			Unit * unit = this->cells_[i][j];

			// chi render nhung cell co unit
			while (unit != NULL)
			{
				listUnits.push_back(unit);
				unit = unit->next_;
			}
		}
	}


}

Grid::Grid(unsigned int mapWidth, unsigned int mapHeight) :
	mapWidth(mapWidth),
	mapHeight(mapHeight+80)
{
	this->numXCell = ceil((float)this->mapWidth / this->cellSize)+1;
	this->numYcell = ceil((float)this->mapHeight / this->cellSize);
	// clear grid

	this->cells_.resize(numYcell);

	for (int i = 0; i < numYcell; i++)
		cells_[i].resize(numXCell);

	for (size_t i = 0; i < numYcell; i++)
	{
		for (size_t j = 0; j < numXCell; j++)
		{
			this->cells_[i][j] = NULL;
		}
	}

}

void Grid::Render()
{
	float camx, camy;
	Camera::GetInstance()->GetCamera(camx, camy);
	int startCol = camx / this->cellSize;
	int endCol = ceil((float)(camx + SCREEN_WIDTH) / this->cellSize);
	for (int i = 0; i < this->numYcell; i++)
	{
		for (int j = startCol; j < endCol; j++)
		{
			Unit * unit = this->cells_[i][j];

			// chi render nhung cell co unit
			while (unit != NULL)
			{
				unit->GetGameObject()->Render();
			}
		}
	}


}

Grid::~Grid()
{
}

