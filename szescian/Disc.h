#pragma once
#include "Shape.h"

class Disc : public Shape {
public:
	Disc(ColorF color, int steps = 10) {
		this->Type = TriangleFan;
		this->Color = color;

		this->AddPoint(Vec3(0, 0, 0), UP);
		auto f = 2 * M_PI / steps;
		for (auto i = 0; i <= steps; i++)
			this->AddPoint(Vec3(cos(i * f), sin(i * f), 0), UP);
	}
};