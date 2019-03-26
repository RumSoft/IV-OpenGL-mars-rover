#pragma once
#include "Shape.h"

class Cylinder : public Shape
{
public:
	Cylinder(Vec3 pos, float r, float h, int steps, ColorF color)
	{
		this->Type = TriangleStrip;
		this->Origin = pos;
		this->Color = color;

		float f = 2 * M_PI / steps;
		for (int i = 0; i <= steps; i++) {
			this->Points.push_back(Vec3(0, 0, -h / 2));
			this->Points.push_back( Vec3(r *sin(i * f), r *cos(i*f), -h / 2));
		}

		for (int i = 0; i <= steps; i++) {
			this->Points.push_back(Vec3(r *sin(i * f), r *cos(i*f), -h / 2));
			this->Points.push_back(Vec3(r *sin(i * f), r *cos(i*f), h / 2));
		}

		for (int i = 0; i <= steps; i++) {
			this->Points.push_back(Vec3(r *sin(i * f), r *cos(i*f), h / 2));
			this->Points.push_back(Vec3(0, 0, h / 2));
		}
	}
};
