#pragma once

#include"GameObject.h"
#define TORCH_BBOX_WIDTH 32
#define TORCH_BBOX_HEIGHT 64
#define TORCH_DESTROY 1
#define TORCH_BURNING 0
class Torch:public CGameObject
{

	int itemDef;
public:
	virtual void Render();
	void SetItem(int item) {
		this->itemDef = item;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void GetSpriteBox(float& width, float& height) {
		width = TORCH_BBOX_WIDTH;
		height = TORCH_BBOX_HEIGHT;
	};
	Torch();

	~Torch();
};

