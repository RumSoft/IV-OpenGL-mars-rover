#pragma once
#include "string";
#include <utility>
#include <vector>
#include "ObjShapeMemory.h"
#include "obj_loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "image_loader.h"

using namespace std;

class ObjFile : public Geom
{
	unsigned int LoadTexture(const char* file, GLenum textureSlot)
	{
		GLuint texHandle;
		// Copy file to OpenGL
		glGenTextures(textureSlot, &texHandle);
		glBindTexture(GL_TEXTURE_2D, texHandle);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		const auto data = stbi_load(file, &width, &height, &nrChannels, 0);
		if (data)
		{
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			gluBuild2DMipmaps(GL_TEXTURE_2D, nrChannels, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			return 0;
		}
		stbi_image_free(data);
		return texHandle;
	}

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
		_texture =  (!_folder.empty() ? _folder + "/" : "" ) + loader.LoadedMeshes[0].MeshMaterial.map_Kd;
		return shape;
	}

public:
	string _folder;
	string _filename;
	string _texture;
	ColorF _color;
	string fullname() const { return (!_folder.empty() ? _folder + "/" : "") + _filename; }

	ObjFile(string folder, string filename, ColorF color)
		:  ObjFile(folder,filename)
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
		if(!_texture.empty())
			shape->texture = LoadTexture(_texture.c_str(), 1);

		if (shape->texture > 0)
			shape->Color = ColorF(XYZ((shape->MeshMaterial.Ks)));
		else
			shape->Color = _color;
	}
};
