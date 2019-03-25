#pragma once
#include "Geom.h"

class Kolo : public Geom
{
public:
	Vec3 point;
	float R, H;
	Kolo(Vec3 pos, float r, float h) : point(pos), R(r), H(h)
	{
		int steps = 10;
		float f = 2 * M_PI / steps;

		auto s1 = Shape(TriangleStrip, ColorF(0.3, 0.3, 0.3));
		for (int i = 0; i <= steps; i++)
		{
			s1.Origin = pos;
			s1.Points.push_back(Vec3(-h/2, R * sin(f * i), R * cos(f * i)));
			s1.Points.push_back(Vec3( h/2, R * sin(f * i), R * cos(f * i)));
		}
		this->Shapes.push_back(s1);
	}
};
