#pragma once
#include "Geom.h"

class Kolo : public Geom
{
public:
	float R, H;
	Kolo(Vec3 pos, float r, float h) : R(r), H(h)
	{
		int steps = 15;
		float f = 2 * M_PI / steps;
		float r2 = r * 0.7;

		auto s1 = Shape(TriangleStrip, ColorF(0.2, 0.2, 0.2));
		for (int i = 0; i <= steps; i++)
		{
			s1.Points.push_back(Vec3(-h / 2, r * cos(i * f), r * sin(i * f)));
			s1.Points.push_back(Vec3(-h / 2, r * cos((i + 1) * f), r * sin((i + 1) * f)));
			
			s1.Points.push_back(Vec3(h / 2, r * cos(i * f), r * sin(i * f)));
			s1.Points.push_back(Vec3(h / 2, r * cos((i + 1) * f), r * sin((i + 1) * f)));
	
			s1.Points.push_back(Vec3(h / 2, r2 * cos(i * f), r2 * sin(i * f)));
			s1.Points.push_back(Vec3(h / 2, r2 * cos((i + 1) * f), r2 * sin((i + 1) * f)));
	
			s1.Points.push_back(Vec3(-h / 2, r2 * cos(i * f), r2 * sin(i * f)));
			s1.Points.push_back(Vec3(-h / 2, r2 * cos((i + 1) * f), r2 * sin((i + 1) * f)));
		}

		auto s2 = Shape(TriangleFan, ColorF(0.3, 0.3, 0.3));
		s2.Points.push_back(Vec3(0.8 * h / 2, 0, 0));
		for (int i = 0; i <= steps; i++)
			s2.Points.push_back(Vec3(0.9 * h / 2, r2 * cos(i * f), r2 * sin(i * f)));

		auto s3 = Shape(TriangleFan, ColorF(0.3, 0.3, 0.3));
		s3.Points.push_back(Vec3(0.8 * -h / 2, 0, 0));
		for (int i = 0; i <= steps; i++)
			s3.Points.push_back(Vec3(0.9 * -h / 2, r2 * cos(-i * f), r2 * sin(-i * f)));

	s1.Origin = pos;
	s2.Origin = pos;
	s3.Origin = pos;
	this->Shapes.push_back(s1);
	this->Shapes.push_back(s2);
	this->Shapes.push_back(s3);
}
};
