#pragma once
#include<unordered_map>
#include"define.h"
class TileObject
{
private:
	int id;
	/*string name;
	string type;
	std::unordered_map<string, int> properties;*/
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	std::string propertyName; // chỉ load 1 cần update thêm
public:
	~TileObject();
	TileObject() {
		id = x = y = width = height = 0;
	}
	int GetId(){return this->id;}
	int GetX() { return this->x; }
	int GetY() { return this->y; } 
	unsigned int GetHeight() { return this->height; }
	unsigned int GetWidth() { return this->width; }
	std::string GetPropertyName(){
		return this->propertyName;
	}
	TileObject(int id, int x, int y, int w, int h,std::string propertyName ) :id(id), x(x), y(y), width(w), height(h), propertyName(propertyName){};
};

typedef TileObject *LPTILEOBJECT;

class ObjectLayer {
private:
	int id;
	std::string name;
	std::string type;
	std::unordered_map<int, LPTILEOBJECT> objects;
	static ObjectLayer * __instance;
public:
	void Add(int id, LPTILEOBJECT object) {
		objects[id] = object;
	}
	LPTILEOBJECT GetTileObject(int id) {
		return objects[id];
	}
	static ObjectLayer * GetInstance();

};


typedef ObjectLayer *LPLISTOBJECTS;