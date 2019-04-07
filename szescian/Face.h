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

		int tess = 2;
		//for(int i = 0; i<tess)

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
		
		auto n = Vec3::Normalized(Vec3::Cross(b - a, c - a));
		
		this->Normals.push_back(n);
		this->Normals.push_back(n);
		this->Normals.push_back(n);
		this->Normals.push_back(n);
	}

	void PreRender() override
	{
		auto p = this->Points[0];
		auto n = this->Normals[0];
		auto pn = p + n * 55;

		glLineWidth(5);

		glBegin(GL_LINE);
		glColor3f(1, 0, 0);
		glVertex3f(p.X, p.Y, p.Z);
		glVertex3f(pn.X, pn.Y, pn.Z);
		glEnd();

		glLineWidth(1);
	}
};