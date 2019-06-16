#pragma once
#include <vector>
#include "Entity.h"
#include "ColorF.h"
#include "string"
#include "fstream"
#include "Vertex.h"
#include "image_loader.h"


enum ShapeType
{
	Line,
	LineStrip,
	Triangle,
	TriangleStrip,
	TriangleFan,
	Quad,
	QuadStrip
};

class Shape : public Entity
{
public:
	Shape() = default;
	Shape(ShapeType type) : Type(type) {}
	Shape(ShapeType type, ColorF color) : Type(type), Color(color) {}
	std::vector<Vertex> Vertices;
	Material MeshMaterial;
	ShapeType Type = LineStrip;
	ColorF Color = BLACK;
	unsigned int texture=0;

	void AddPoint(Vec3 p) { AddPoint(Vertex(p, UP, Vec2(0.5, 0.5))); }
	void AddPoint(Vec3 p, Vec3 n) { AddPoint(Vertex(p, n, Vec2(0.5, 0.5))); }
	void AddPoint(Vertex v) { Vertices.push_back(v); }
	void AddPoint(Vec3 p, Vec2 t) { AddPoint(Vertex(p, Vec3::Zero(), t)); }
	void AddPoint(Vec3 p, Vec3 n, Vec2 t) { AddPoint(Vertex(p, n, t)); }

	Shape* WithPosition(Vec3 pos) {
		this->Origin = pos;
		return this;
	}

	Shape* WithScale(Vec3 scale) {
		this->Scale = scale;
		return this;
	}

	Shape* WithScale(float scale) {
		this->Scale = Vec3(scale, scale, scale);
		return this;
	}

	Shape* WithRotation(Quat rotation) {
		this->Rotation = rotation;
		return this;
	}

	Shape* WithColor(ColorF color) {
		this->Color = color;
		return this;
	}

	Shape* WithType(ShapeType type) {
		this->Type = type;
		return this;
	}


	static unsigned int LoadTexture(const char* file, GLenum textureSlot)
	{
		if (!Shape::is_file_exist(file))
			return 0;
		GLuint texHandle;
		// Copy file to OpenGL
		glGenTextures(textureSlot, &texHandle);
		glBindTexture(GL_TEXTURE_2D, texHandle);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

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

private:
	static bool is_file_exist(const char* fileName)
	{
		const std::ifstream infile(fileName);
		return infile.good();
	}
};