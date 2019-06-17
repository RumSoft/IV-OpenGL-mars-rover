#pragma once
#include "Geom.h"

class Sphere : public Shape {
public:
	Sphere(Vec3 pos, float r, ColorF color = GREEN) : Sphere(pos, r, 5, color) {}
	Sphere(Vec3 pos, ColorF color) : Sphere(pos, 4, 5, color) {}
	Sphere(Vec3 pos, float r = 5, int steps = 5, ColorF color = GREEN) {
		this->Type = TriangleStrip;
		this->Color = color;
		this->Origin = pos;

		const float f = 2 * M_PI / steps;
		const float f2 = M_PI / steps;

		for (int i = 0; i < steps; i++) {
			for (int j = steps; j >= 0; j--) {
				auto v1 = Vec3(
					sin(j * f2) * cos(i * f),
					sin(j * f2) * sin(i * f),
					cos(j * f2));
				auto v2 = Vec3(
					sin(j * f2) * cos((i + 1) * f),
					sin(j * f2) * sin((i + 1) * f),
					cos(j * f2));

				this->AddPoint(r * v1, v1);
				this->AddPoint(r * v2, v2);
			}
		}
	}
};