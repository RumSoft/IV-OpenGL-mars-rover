#pragma once
#include <vector>
#include "Shape.h"
#include <map>
#include <string>

class ObjShapeMemory
{
	ObjShapeMemory()
	{
		
	}
	std::map<std::string, Shape*> shapes;
public:
	static ObjShapeMemory& getInstance() {
		static ObjShapeMemory theInstance;
		return theInstance;
	}

	Shape* GetShape(const std::string& name)
	{
		return shapes.at(name);
	}

	void AddShape(Shape* shape, const std::string& name)
	{
		shapes.insert_or_assign(name, shape);
		shapes.
	}

	
};
