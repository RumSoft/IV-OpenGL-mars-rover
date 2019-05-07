#pragma once
#include <vector>
#include "ObjShapeMemory.h"
#include "obj_loader.h"

class ObjFile : public Geom
{
public:
	ObjFile(const char* str, ColorF color = RED)
	{
		auto memory = ObjShapeMemory::Instance();
		if (!memory.Exists(str))
			memory.AddShape(loadOBJ(str), str);
		this->Shapes.push_back(memory.GetShape(str)->WithColor(color));
	}

	Shape* loadOBJ(const char* path)
	{
		auto loader = objl::Loader();
		if (!loader.LoadFile(path))
			return nullptr;

		auto shape = new Shape(Triangle);
		shape->MeshMaterial = loader.LoadedMeshes[0].MeshMaterial;
		//shape->AddPoint(loader.LoadedMeshes[0].) 

		for (const auto v : loader.LoadedMeshes[0].Vertices)
			shape->AddPoint(v);

		return shape;
	}
};
