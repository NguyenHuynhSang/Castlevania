#pragma once
#include<string>
class ObjectProperty
{
private:
	std::string name;
	float value;
public:
	std::string GetName() {
		return this->name;
	}
	float GetValue() {
		return this->value;
	}
	ObjectProperty() ;
	ObjectProperty(std::string name, float value) :name(name), value(value) {}
	~ObjectProperty();
};

typedef ObjectProperty* LPOBJECTPROPERTY;


