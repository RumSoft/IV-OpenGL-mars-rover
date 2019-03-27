#pragma once
#include "Shape.h"

class Cylinder : public Shape
{
public:
	Cylinder(Vec3 pos, float r, float h, int steps, ColorF color, Quat rot = Quat::Identity(), bool center = true)
	{
		this->Type = TriangleStrip;
		this->Origin = pos;
		this->Color = color;

		float f = 2 * M_PI / steps;
		for (int i = 0; i <= steps; i++) {
			this->Points.push_back(rot * Vec3(0, 0, center ? -h / 2 : 0));
			this->Points.push_back(rot * Vec3(r *sin(i * f), r *cos(i*f), center ? -h / 2 : 0));
		}

		for (int i = 0; i <= steps; i++) {
			this->Points.push_back(rot * Vec3(r *sin(i * f), r *cos(i*f), center ? -h / 2 : 0));
			this->Points.push_back(rot * Vec3(r *sin(i * f), r *cos(i*f), center ? h / 2 : h));
		}

		for (int i = 0; i <= steps; i++) {
			this->Points.push_back(rot * Vec3(r *sin(i * f), r *cos(i*f), center ? h / 2 : h));
			this->Points.push_back(rot * Vec3(0, 0, h / 2));
		}
	}
};
