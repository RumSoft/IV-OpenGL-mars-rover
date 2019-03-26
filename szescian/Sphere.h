#pragma once
#include "Geom.h"

class Sphere : public Geom {
public:
	Shape GetShape() { return this->Shapes[0]; }

	Sphere(Vec3 pos, float r, ColorF color = GREEN) : Sphere(pos, r, 5, color) {}
	Sphere(Vec3 pos, ColorF color) : Sphere(pos, 4, 5, color) {}
	Sphere(Vec3 pos, float r = 5, int steps = 5, ColorF color = GREEN) {
		float f = 2 * M_PI / steps;
		float f2 = M_PI / steps;
		auto s1 = Shape(TriangleStrip, color);
		for (int i = 0; i < steps; i++) {
			for (int j = steps; j >= 0; j--) {
				s1.Points.push_back(r * Vec3(
					sin(j * f2) * cos(i * f),
					sin(j * f2) * sin(i * f),
					cos(j * f2)
				));
				s1.Points.push_back(r * Vec3(
					sin(j * f2) * cos((i + 1) * f),
					sin(j * f2) * sin((i + 1) * f),
					cos(j * f2)
				));
			}
		}
		s1.Origin = pos;
		this->Shapes.push_back(s1);
	}
};