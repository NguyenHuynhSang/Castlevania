#include "Grid.h"
#include"Camera.h"
#include"Item.h"
#include"Enemy.h"
#include"Candle.h"
#include"SubWeapon.h"
#include"Torch.h"
#include"Brick.h"
#include"PhantomBat.h"
#include"Effects.h"
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
	if (cellX>numXCell)//safe 
	{
		DebugOut(L"[OUTOFGRID] NUMX\n");
		return;
	}
	//safe 
	if (cellY > numYCell-1)
	{
		DebugOut(L"[OUTOFGRID] NUMY \n");
		return;
	}
	// thêm vào trước ds unit ở ô đó
	unit->prev_ = NULL;
	unit->next_ = cells_[cellY][cellX];
	cells_[cellY][cellX] = unit;

	// đã có 1 list unit ở đó
	if (unit->next_ != NULL)
	{
		unit->next_->prev_ = unit;
	}

	// thêm vào sau ds;
	//unit->next_ = NULL;
	//Unit * lastNode= cells_[cellY][cellX];
	//if (cells_[cellY][cellX]==NULL)
	//{
	//	unit->prev_ = NULL;
	//	cells_[cellY][cellX] = unit;
	//}
	//else
	//{
	//	while (lastNode->next_ != NULL)
	//	{
	//		lastNode = lastNode->next_;

	//	}
	//	unit->prev_ = lastNode;
	//	if (unit->prev_ != NULL)
	//	{
	//		unit->prev_->next_ = unit;
	//	}
	//}
	



}


bool AABB(float l, float t, float r, float b, float l1, float t1, float r1, float b1)
{
	float left = l1 - r;
	float top = b1 - t;
	float right = r1 - l;
	float bottom = t1 - b;
	//  xét ngược lại cho nhanh hơn
	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}

void Grid::Update(Unit * unit, float x, float y)
{
	float cx_, cy_;

	Camera::GetInstance()->GetCamera(cx_, cy_);


	float l, t, r, b;
	unit->GetGameObject()->GetBoundingBox(l, t, r, b);
	

	if (AABB(l,t,r,b,cx_,cy_,cx_+SCREEN_WIDTH,cy_+SCREEN_HEIGHT))
	{
		unit->GetGameObject()->SetActive();
	}
	else
	{
		if (unit->GetGameObject()->CheckActive()) {
			if (dynamic_cast<Item*>(unit->GetGameObject())
				|| dynamic_cast<Enemy*>(unit->GetGameObject())
				|| dynamic_cast<SubWeapon*>(unit->GetGameObject()))
			{
				if (!dynamic_cast<PhantomBat*>(unit->GetGameObject()))
				{
					unit->GetGameObject()->DestroyImmediate();
				}
			
			}
		
		}
	}
	//out of map? destroy immediate
	if (x < -15 || x > mapWidth || y<0 || y > SCREEN_HEIGHT) // -15px for bound map
	{
		unit->GetGameObject()->DestroyImmediate();
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
	// dùng để sắp xếp lại thứ tự các loại object
	vector<Unit*> enemiesUnit;
	vector<Unit*> itemUnit;
	vector<Unit*> subWeaponUnit;
	vector<Unit*> effectUnit;
	enemiesUnit.clear();
	itemUnit.clear();
	subWeaponUnit.clear();
	effectUnit.clear();




	float camx, camy;
	Camera::GetInstance()->GetCamera(camx, camy);
	int startCol = floor(camx / this->cellSize);
	startCol = startCol > 0 ? startCol + -1 : 0;
	int endCol = floor((camx + SCREEN_WIDTH) / this->cellSize);
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
					LPGAMEOBJECT object = unit->GetGameObject();
					if (dynamic_cast<Enemy*>(object))
					{

						enemiesUnit.push_back(unit);
					}
					else if (dynamic_cast<Item*>(object))
					{
						itemUnit.push_back(unit);
					}
					else if (dynamic_cast<SubWeapon*>(object))
					{
						subWeaponUnit.push_back(unit);

					}
					else if (dynamic_cast<Effects*>(object))
					{
						effectUnit.push_back(unit);
					}
					else 
					{
						listUnits.push_back(unit);
					}
					unit = unit->next_;

				}
				else
				{

				}
			}
		}
	}




	// lấy theo thứ tự
	listUnits.insert(listUnits.end(), itemUnit.begin(), itemUnit.end());
	listUnits.insert(listUnits.end(),enemiesUnit.begin(),enemiesUnit.end());
	listUnits.insert(listUnits.end(), subWeaponUnit.begin(), subWeaponUnit.end());
	listUnits.insert(listUnits.end(), effectUnit.begin(), effectUnit.end());
}

Grid::Grid(unsigned int mapWidth, unsigned int mapHeight) :
	mapWidth(mapWidth),
	mapHeight(mapHeight + 80)
{
	this->numXCell = ceil((float)this->mapWidth / this->cellSize) + 1;
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

