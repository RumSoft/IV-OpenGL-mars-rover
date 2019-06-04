#pragma once
#include "string";
#include <utility>
#include <vector>
#include "Shape.h"
#include "ObjShapeMemory.h"
#include "obj_loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "image_loader.h"
#include "TextureMemory.h"

using namespace std;

class ObjFile : public Geom
{
	Shape* loadOBJ()
	{
		const auto obj = fullname() + ".obj";
		auto loader = objl::Loader();
		if (!loader.LoadFile(obj))
			return nullptr;

		auto shape = new Shape(Triangle);
		shape->MeshMaterial = loader.LoadedMeshes[0].MeshMaterial;
		for (const auto v : loader.LoadedMeshes[0].Vertices)
			shape->AddPoint(v);
		_texture = (!_folder.empty() ? _folder + "/" : "") + loader.LoadedMeshes[0].MeshMaterial.map_Kd;
		return shape;
	}

public:
	string _folder;
	string _filename;
	string _texture;
	ColorF _color;
	string fullname() const { return (!_folder.empty() ? _folder + "/" : "") + _filename; }

	ObjFile(string folder, string filename, ColorF color)
		: ObjFile(folder, filename)
	{
		_color = color;
	}

	ObjFile(string folder, string filename)
		: _folder(move(folder)), _filename(move(filename))
	{
		auto memory = ObjShapeMemory::Instance();
		if (!memory.Exists(fullname()))
			memory.AddShape(loadOBJ(), fullname());
		this->Shapes.push_back(memory.GetShape(fullname()));
	}

	void Init() override
	{
		const auto shape = this->Shapes[1];
		if (shape == nullptr)
			return;
		if (!_texture.empty())
			shape->texture = TextureMemory::Instance().GetTexture(_texture);

		if (shape->texture > 0)
			shape->Color = ColorF(XYZ((shape->MeshMaterial.Ks)));
		else
			shape->Color = _color;
	}

	void PreRender() override
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void PostRender() override
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
};
