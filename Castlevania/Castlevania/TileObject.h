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

public:
	~TileObject();
	TileObject() {
		id = x = y = width = height = 0;
	}
	int GetId(){return this->id;}
	int GetX() { return this->x; }
	int GetY() { return this->y+ GAME_WORLD_Y; } // cộng thêm phần board
	unsigned int GetHeight() { return this->height; }
	unsigned int GetWidth() { return this->width; }

	TileObject(int id, int x, int y, int w, int h) :id(id), x(x), y(y), width(w), height(h) {};
};

typedef TileObject *LPTILEOBJECT;

class ObjectGroup {
private:
	int id;
	std::string name;
	std::string type;
	std::unordered_map<int, LPTILEOBJECT> objects;
	static ObjectGroup * __instance;
public:
	void Add(int id, LPTILEOBJECT object) {
		objects[id] = object;
	}
	LPTILEOBJECT GetTileObject(int id) {
		return objects[id];
	}
	static ObjectGroup * GetInstance();

};


typedef ObjectGroup *LPLISTOBJECTS;