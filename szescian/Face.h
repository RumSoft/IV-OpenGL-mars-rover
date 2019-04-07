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

		this->Points.push_back(x1);
		this->Points.push_back(x2);
		this->Points.push_back(x3);
		this->Points.push_back(x4);
		
		auto n = Vec3::Normalized(Vec3::Cross(b - a, d - a));
		
		this->Normals.push_back(n);
		this->Normals.push_back(n);
		this->Normals.push_back(n);
		this->Normals.push_back(n);
	}
};