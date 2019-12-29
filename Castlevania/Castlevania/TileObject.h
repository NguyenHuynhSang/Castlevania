#pragma once
#include<unordered_map>
#include"define.h"
#include<string>
class TileObject
{
private:
	int id;
	std::string name;
	float x;
	float y;
	unsigned int width;
	unsigned int height;
	std::unordered_map<std::string, int> intProperties;
public:
	~TileObject();
	TileObject() {
		id = x = y = width = height = 0;
		this->name = "";
	}
	int GetId(){return this->id;}
	float  GetX() { return this->x; }
	float GetY() { return this->y; }
	std::string  GetName() {
		return this->name;
	}
	int  GetIntProperty(std::string key) {
		if (this->intProperties.empty())
			return -1;
		if (this->intProperties.count(key)<=0)
		{
			return -1;
		}
		return this->intProperties.find(key)->second;
	}
	void AddProperty(std::string name, int value);
	unsigned int GetHeight() { return this->height; }
	unsigned int GetWidth() { return this->width; }
	TileObject(int id,std::string name, int x, int y, int w, int h):id(id),name(name), x(x), y(y), width(w), height(h){};
};

typedef TileObject* LPTILEOBJECT;

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