#pragma once
#include <vector>
#include "ObjShapeMemory.h"
#include "obj_loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "image_loader.h"

inline unsigned int LoadTexture(const char* file, GLenum textureSlot)
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
		throw 1;
	}
	stbi_image_free(data);
	return texHandle;
}

/*
 GLuint texture;

		// allocate a texture name
		glGenTextures(1, &texture);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// load and generate the texture
		int width, height, nrChannels;
		const auto data = stbi_load(txt, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

 */


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
		for (const auto v : loader.LoadedMeshes[0].Vertices)
			shape->AddPoint(v);

		return shape;
	}
	void Init() override
	{
		const auto shape = this->Shapes[1];
		const auto txt = "objects/GroundTexture2.png";
		shape->texture = LoadTexture(txt, 1);
		shape->Color = ColorF(XYZ((shape->MeshMaterial.Ks)));
	}

	void PostRender() override
	{
		// podstawowe teksturowanie !!
		int a = 100;
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 3);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(Quad);
		glTexCoord2d(0, 0); glVertex3f(XYZ(Vec3(0, 0, 20)));
		glTexCoord2d(0, 1); glVertex3f(XYZ(Vec3(a, 0, 20)));
		glTexCoord2d(1, 0); glVertex3f(XYZ(Vec3(0, a, 20)));
		glTexCoord2d(1, 1); glVertex3f(XYZ(Vec3(a, a, 20)));
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
};
