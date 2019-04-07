#pragma once
#include "Shape.h"

class Disc : public Shape {
public:
	Disc(ColorF color, int steps = 10) {
		this->Type = TriangleFan;
		this->Color = color;
		
		this->Points.push_back(Vec3(0, 0, 0));
		this->Normals.push_back(Vec3::Up());

		auto f = 2 * M_PI / steps;
		for (int i = 0; i <= steps; i++) {
			this->Points.push_back(Vec3(cos(i * f), sin(i * f), 0));
			this->Normals.push_back(Vec3::Up());
		}
	}
};