#pragma once
#include <vector>
#include "Entity.h"
#include "ColorF.h"


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
	std::vector<Vec3> Points;
	std::vector<Vec3> Normals;
	ShapeType Type = LineStrip;
	ColorF Color = BLACK;

	void AddPoint(Vec3 p) {
		Points.push_back(p);

		int i = Points.size();
		if (i < 3)
			return;

		auto p1 = Points[i-3];
		auto p2 = Points[i-2];
		auto p3 = Points[i-1];
		auto n = Vec3::Normalized(Vec3::Cross(p2 - p1, p3 - p1));
		if (Points.size() == 3)
		{
			Normals.push_back(n);
			Normals.push_back(n);
		}
		Normals.push_back(n);
	}


	void AddPoint(Vec3 p, Vec3 n) {
		Points.push_back(p);
		Normals.push_back(n);
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