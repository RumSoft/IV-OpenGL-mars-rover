#pragma once
#include "Shape.h"

class Face : public Shape {
public:
	Face(Vec3 a, Vec3 b, Vec3 c, ColorF color, bool reverse = false)
		: Face(a, b, c, c, color, reverse)
	{}
	Face(Vec3 a, Vec3 b, Vec3 c, Vec3 d, ColorF color , bool reverse = false) {
		Type = ShapeType::TriangleStrip;
		Color = color;

		auto center = (a + b + c + d) / 4;
		this->Origin = center;

		auto x1 = a - center;
		auto x2 = b - center;
		auto x3 = c - center;
		auto x4 = d - center;

		auto n = Vec3::Normalized(Vec3::Cross(x2 - x1, x3 - x1));

		this->Vertices.emplace_back(x1, n, Vec2(0, 0));
		this->Vertices.emplace_back(x2, n, Vec2(0, 1));
		this->Vertices.emplace_back(x3, n, Vec2(1, 0));
		this->Vertices.emplace_back(x4, n, Vec2(1, 1));
	}

	void PreRender() override
	{
		
	}

	void PostRender() override
	{
		
	}
};