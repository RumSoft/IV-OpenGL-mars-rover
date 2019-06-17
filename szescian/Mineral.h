#pragma once
#include "Geom.h"
#include "IScene.h"
#include "ObjFile.h"

class Mineral : public ObjFile
{
	IScene* _scene;
public:
	Mineral(IScene* scene) 
	: ObjFile("objects", "mineral", 1)
	{
		_scene = scene;
		this->Scale = 17;
		//this->Shapes.push_back(new Face(ZERO, UP * 50, FORWARD * 100, FORWARD * 100 + UP * 10)
		/*_scene = scene;
		auto obj = new ObjFile("objects", "mineral", 1);
		this->proxy = obj->proxy;
		obj->Origin = this->Origin;
		proxy->Origin = this->Origin;
		this->Children.push_back(obj->WithScale(17));*/
		
	}

	void PostRender() override
	{
		this->proxy->DrawProxy();
	}
};
