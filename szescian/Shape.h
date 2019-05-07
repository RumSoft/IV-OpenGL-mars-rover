#pragma once
#include <vector>
#include "Entity.h"
#include "ColorF.h"
#include "Vertex.h"


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

	void AddPoint(Vec3 p) {
		AddPoint(Vertex(p, UP, Vec2(0.5, 0.5)));
	}

	void AddPoint(Vec3 p, Vec3 n) {
		AddPoint(Vertex(p, n, Vec2(0.5, 0.5)));
	}

	void AddPoint(Vertex v)
	{
		Vertices.push_back(v);
	}

	void AddPoint(Vec3 p, Vec3 n, Vec2 t)
	{
		AddPoint(Vertex(p, n, t));
	}

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

};