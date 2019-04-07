#pragma once
#include "Geom.h"
#include "Ramie.h"

class Kamera : public Geom
{
public:

	Kamera(float h, float a, float b, float c)
	{
		auto kams = Vec3::Zero();

		auto r1 = new Ramie(kams, kams + Vec3(0, 0, h), 3, 2, 0, RED);	//pierwsze ramie
		this->Children.push_back(r1);

		auto s1 = new Shape(TriangleStrip, BLUE);
		s1->Origin = kams + Vec3(0, 0, h);
		s1->Points.emplace_back(-a, b, c);
		s1->Points.emplace_back(a, b, c);
		s1->Points.emplace_back(-a, -a, c);
		s1->Points.emplace_back(a, -a, c);
		s1->Points.emplace_back(-a, -b, c / 3);
		s1->Points.emplace_back(a, -b, c / 3);
		s1->Points.emplace_back(-a, -b, 0);
		s1->Points.emplace_back(a, -b, 0);
		s1->Points.emplace_back(-a, b, 0);
		s1->Points.emplace_back(a, b, 0);
		this->Shapes.push_back(s1);

		auto s2 = new Shape(TriangleStrip, BLUE);
		s2->Origin = kams + Vec3(0, 0, h);
		s2->Points.emplace_back(-a, -b, 0);
		s2->Points.emplace_back(-a, -b, c / 3);
		s2->Points.emplace_back(a, -b, 0);
		s2->Points.emplace_back(a, -b, c / 3);
		s2->Points.emplace_back(a, -a, 0);
		s2->Points.emplace_back(a, -a, c);
		s2->Points.emplace_back(a, b, 0);
		s2->Points.emplace_back(a, b, c);
		s2->Points.emplace_back(-a, b, 0);
		s2->Points.emplace_back(-a, b, c);
		s2->Points.emplace_back(-a, -a, 0);
		s2->Points.emplace_back(-a, -a, c);
		s2->Points.emplace_back(-a, -b, 0);
		s2->Points.emplace_back(-a, -b, c / 3);
		this->Shapes.push_back(s2);
	}
};