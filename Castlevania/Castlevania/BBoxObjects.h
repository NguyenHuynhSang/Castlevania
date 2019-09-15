#pragma once
#include"GameObject.h"
class BBoxObject:public CGameObject
{
protected:
	float width;
	float height;
public:
	virtual void GetSpriteBox(float& _width, float& _height) {
		_width = this->width;
		_height = this->height;
	};
	virtual void  GetBoundingBox(float &l, float &t, float &r, float &b) {
		l = x;
		t = y;
		r = l + this->width;
		b = t + this->height;
	}
	void SetSize(float w,float h) {
		this->width = w;
		this->height = h;
	}
	BBoxObject() {
		width = height = 0;
	};
	~BBoxObject();
};

