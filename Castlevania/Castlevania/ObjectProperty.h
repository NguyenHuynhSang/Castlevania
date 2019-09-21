#pragma once
#include<string>
class ObjectProperty
{
private:
	std::string name;
	float value;
public:
	ObjectProperty() ;
	ObjectProperty(std::string name, float value) :name(name), value(value) {}
	~ObjectProperty();
};



