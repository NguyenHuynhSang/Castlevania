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
#include"Textures.h"



void Grid::RenderCell(RECT rec, MYCOLOR color, int alpha)
{
	D3DXVECTOR3 p(rec.left, rec.top + 80, 0);
	RECT rect = { 0,0,0,0 };
	LPDIRECT3DTEXTURE9 bbox;
	switch (color)
	{
	case MYCOLOR::RED:
		bbox = CTextures::GetInstance()->Get(ID_TEX_SPRITE_BBOX);
		break;
	case MYCOLOR::BLUE:
		bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);
		break;
	default:
		bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);
		break;
	}

	rect.left = 0;
	rect.top = 0;
	rect.right = (int)rec.right - (int)rec.left;
	rect.bottom = (int)rec.bottom - (int)rec.top;


	CGame::GetInstance()->Draw(true, DIRECTION::DEFAULT, rec.left, rec.top + 80, bbox, rect.left, rect.top, rect.right, rect.bottom, alpha);

}



void Grid::Add(LPGAMEOBJECT object)
{
	float x_, y_;
	object->GetPosition(x_, y_);
	//tính vị trí của object
	int cellX = (int)(x_ / this->cellSize);
	int cellY = (int)(y_ / this->cellSize);
	if (cellX > numXCell)//safe 
	{
		DebugOut(L"[OUTOFGRID] NUMX\n");
		return;
	}
	//safe 
	if (cellY > numYCell - 1)
	{
		DebugOut(L"[OUTOFGRID] NUMY \n");
		return;
	}
	object->SetCellIndex(cellX, cellY);
	this->cells_[cellY][cellX].push_back(object);





}

void Grid::AddToAlwayUpdateObjects(LPGAMEOBJECT object)
{

	this->alwaysUpdateobject.push_back(object);

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

void Grid::Update(LPGAMEOBJECT object)
{
	float cx_, cy_;

	Camera::GetInstance()->GetCamera(cx_, cy_);

	float x, y;
	object->GetPosition(x, y);


	float l, t, r, b;
	object->GetBoundingBox(l, t, r, b);


	if (AABB(l, t, r, b, cx_, cy_, cx_ + SCREEN_WIDTH, cy_ + SCREEN_HEIGHT))
	{
		object->SetActive();
	}
	else
	{
		if (object->CheckActive()) {
			if (dynamic_cast<Item*>(object)
				|| dynamic_cast<Enemy*>(object)
				|| dynamic_cast<SubWeapon*>(object))
			{
				if (!dynamic_cast<PhantomBat*>(object))
				{
					object->DestroyImmediate();
				}

			}

		}
	}
	//out of map? destroy immediate
	if (x < -15 || x > mapWidth || y<0 || y > SCREEN_HEIGHT) // -15px for bound map
	{
		object->DestroyImmediate();
	}

	CellIndex oldCell = object->GetCellIndex();

	// tìm vị trí cũ của cell chứa object 

	// xem object h đang ở cell nào

	int cellX = (int)(x / this->cellSize);
	int cellY = (int)(y / this->cellSize);


	if (object->CheckDestroyed())
	{

		// loại bỏ cell cũ
		for (vector<LPGAMEOBJECT>::iterator it = cells_[oldCell.y][oldCell.x].begin(); it != cells_[oldCell.y][oldCell.x].end(); ) {
			if ((*it) == object) {
				it = cells_[oldCell.y][oldCell.x].erase(it);
			}
			else ++it;
		}
		// xóa luôn
		delete object;
		return;
	}
	// nếu k ra khỏi cell 
	if (oldCell.x == cellX && oldCell.y == cellY)
	{
		return;
	}
	if (oldCell.x!=-1 && oldCell.y!=-1) // loại bỏ cell cũ
	{
		for (vector<LPGAMEOBJECT>::iterator it = cells_[oldCell.y][oldCell.x].begin(); it != cells_[oldCell.y][oldCell.x].end(); ) {
			if ((*it) == object) {
				it = cells_[oldCell.y][oldCell.x].erase(it);
			}
			else ++it;
		}

	}
	
	//thêm lại vào cell mới
	Add(object);



}

void Grid::Update(float dt)
{

}

void Grid::GetListobject(vector<LPGAMEOBJECT>& listobjects)
{
	// dùng để sắp xếp lại thứ tự các loại object
	vector<LPGAMEOBJECT> enemiesobject;
	vector<LPGAMEOBJECT> itemobject;
	vector<LPGAMEOBJECT> subWeaponobject;
	vector<LPGAMEOBJECT> effectobject;
	enemiesobject.clear();
	itemobject.clear();
	subWeaponobject.clear();
	effectobject.clear();




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
			for (size_t k = 0; k < this->cells_[i][j].size(); k++)
			{
				LPGAMEOBJECT obj = this->cells_[i][j].at(k);
				if (!obj->CheckDestroyed())
				{
					if (dynamic_cast<Enemy*>(obj))
					{

						enemiesobject.push_back(obj);
					}
					else if (dynamic_cast<Item*>(obj))
					{
						itemobject.push_back(obj);
					}
					else if (dynamic_cast<SubWeapon*>(obj))
					{
						subWeaponobject.push_back(obj);

					}
					else if (dynamic_cast<Effects*>(obj))
					{
						effectobject.push_back(obj);
					}
					else
					{
						listobjects.push_back(obj);
					}
				}
				else
				{

				}
			}


			// chi render nhung cell co object


		}
	}
	//loop thought alwaysUpdateobject

	for (size_t i = 0; i < this->alwaysUpdateobject.size(); i++)
	{
		LPGAMEOBJECT ob = alwaysUpdateobject.at(i);
		listobjects.push_back(ob);

	}



	// lấy theo thứ tự
	listobjects.insert(listobjects.end(), itemobject.begin(), itemobject.end());
	listobjects.insert(listobjects.end(), enemiesobject.begin(), enemiesobject.end());
	listobjects.insert(listobjects.end(), subWeaponobject.begin(), subWeaponobject.end());
	listobjects.insert(listobjects.end(), effectobject.begin(), effectobject.end());
	//DebugOut(L"List Object %d\n", listobjects.size());
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
			this->cells_[i][j].clear();
		}
	}

	this->alwaysUpdateobject.clear();
}

void Grid::Render()
{
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
			string _UIinfor = "CastleVania\n    ";
			RECT cell = { j * cellSize,i * cellSize,j * cellSize + cellSize ,i * cellSize + cellSize };
			if (i % 2 == 0)
			{
				if (j % 2 == 0)
					RenderCell(cell, MYCOLOR::RED, 100);
				else {
					RenderCell(cell, MYCOLOR::BLUE, 100);
				}
			}
			else {
				if (j % 2 == 0)
					RenderCell(cell, MYCOLOR::BLUE, 100);
				else {
					RenderCell(cell, MYCOLOR::RED, 100);
				}
				;
			}
			CGame::GetInstance()->DrawUIText(_UIinfor, cell);
		}
	}

}


Grid::~Grid()
{
}

