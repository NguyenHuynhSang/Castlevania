#pragma once
#include"GameObject.h"
class StaticObject:public CGameObject
{
protected:
	float weight;
	float height;
public:
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b) {
		l = x;
		t = y;
		r = x + weight;
		b = y + height;
	};
	virtual void GetSpriteBox(float& _width, float& _height) {
		_width = this->weight;
		_height = this->height;
	};
	void SetSize(float w,float h) {
		this->weight = w;
		this->height = h;
	}
	StaticObject();
	~StaticObject();
};

