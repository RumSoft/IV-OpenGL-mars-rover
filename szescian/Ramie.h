#pragma once
#include "Geom.h"

class Ramie : public Geom {
public:
	Ramie(Vec3 p1, Vec3 p2, int steps = 3, float r = 2, ColorF color = RED) : Ramie(p1, p2, steps, r, 0, color) {}
	Ramie(Vec3 p1, Vec3 p2, int steps = 3, float r = 2, float r2 = 0, ColorF color = RED) {
		auto s1 = Shape(TriangleStrip, RED);
		s1.Points.push_back(p1);
		s1.Points.push_back(p2);
		this->Shapes.push_back(s1);

		auto s2 = Shape(TriangleStrip, RED);
		auto rot = Quat::FromToRotation(p1, p2);
		auto len = Vec3::Magnitude(p2 - p1);
		
		float f = 2 * M_PI / steps;
		for (int i = 0; i <= steps; i++)
		{
			s2.Points.push_back(p2 + Vec3(r * sin(i * f), r * cos(i * f)));
			s2.Points.push_back(p1 + Vec3(r * sin(i * f), r * cos(i * f)));
		}
		this->Rotation = rot;
		this->Shapes.push_back(s2);


		if (r2 > 0) {
			this->Shapes.push_back(Sphere(p1, r2, 5, color).GetShape());
			this->Shapes.push_back(Sphere(p2, r2, 5, color).GetShape());
		}
	}
};