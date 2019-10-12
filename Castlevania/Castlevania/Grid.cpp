#include "Grid.h"
#include"Camera.h"
#include"Item.h"
#include"Enemy.h"
#include"SubWeapon.h"
Unit::Unit(Grid * gird, LPGAMEOBJECT object)
	: grid_(gird),
	object(object),
	x_(object->x),
	y_(object->y)
{
	grid_->Add(this);
}

Unit::~Unit()
{
	DebugOut(L"Destructor Unit \n");
	delete object;
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



void Grid::Update(Unit * unit, float x, float y)
{
	float cx_, cy_;

	Camera::GetInstance()->GetCamera(cx_, cy_);

	if (x>cx_ && x<cx_+SCREEN_WIDTH && y>0 && y< cy_+SCREEN_HEIGHT)
	{
		unit->GetGameObject()->SetActive();
	}
	if (x < -15 || x > mapWidth || y<0 || y > SCREEN_HEIGHT ) // -15px for bound map
	{
		unit->GetGameObject()->DestroyImmediate();
	}
	if (unit->GetGameObject()->CheckActive())
	{
		
		 if (x<cx_|| x>cx_ + SCREEN_WIDTH
			|| y<cy_ || y>cy_ + SCREEN_HEIGHT)
		{
			if (dynamic_cast<Item *>(unit->GetGameObject())
				|| dynamic_cast<Enemy *>(unit->GetGameObject())
				|| dynamic_cast<SubWeapon *>(unit->GetGameObject()))
			{
				unit->GetGameObject()->DestroyImmediate();
			}
		}

	}



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

	if (unit->GetGameObject()->CheckDestroyed())
	{
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
		delete unit;
		return;
	}


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

}

void Grid::GetListUnit(vector<Unit*>& listUnits)
{
	float camx, camy;
	Camera::GetInstance()->GetCamera(camx, camy);
	int startCol = camx / this->cellSize;
	startCol = startCol > 0 ? startCol + -1 : 0;
	int endCol = (camx + SCREEN_WIDTH) / this->cellSize;
	endCol = endCol > numXCell ? numXCell : endCol + 1;
	for (int i = 0; i < this->numYCell; i++)
	{
		for (int j = startCol; j < endCol; j++)
		{
			Unit * unit = this->cells_[i][j];
			// chi render nhung cell co unit

			while (unit != NULL)
			{
				if (!unit->GetGameObject()->CheckDestroyed())
				{
					listUnits.push_back(unit);
					unit = unit->next_;

				}
				else
				{

				}
			}
		}
	}


}

Grid::Grid(unsigned int mapWidth, unsigned int mapHeight) :
	mapWidth(mapWidth),
	mapHeight(mapHeight + 80)
{
	this->numXCell = ceil((float)this->mapWidth / this->cellSize);
	this->numYCell = ceil((float)this->mapHeight / this->cellSize);
	// clear grid

	this->cells_.resize(numYCell);

	for (int i = 0; i < numYCell; i++)
		cells_[i].resize(numXCell);

	for (size_t i = 0; i < numYCell; i++)
	{
		for (size_t j = 0; j < numXCell; j++)
		{
			this->cells_[i][j] = NULL;
		}
	}

}

void Grid::Render()
{
}

void Grid::RemoveUnit(Unit* unit)
{
	// tìm vị trí củ của cell chứa unit 
	int oldCellX = (int)(unit->x_ / this->cellSize);
	int oldCellY = (int)(unit->y_ / this->cellSize);
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
	delete unit->GetGameObject();
}

Grid::~Grid()
{
}
