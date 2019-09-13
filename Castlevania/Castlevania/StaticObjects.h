#pragma once
#include"GameObject.h"
class StaticObject:public CGameObject
{
protected:
	float width;
	float height;
public:
	virtual void GetSpriteBox(float& _width, float& _height) {
		_width = this->width;
		_height = this->height;
	};
	void SetSize(float w,float h) {
		this->width = w;
		this->height = h;
	}
	StaticObject() {
		width = height = 0;
	};
	~StaticObject();
};

