#pragma once
#include "Geom.h"

class Grid : public Geom
{
public:
	float Size;
	int Steps;

	Grid(const float size = 100, const int steps = 10) : Size(size), Steps(steps)
	{
		const float h = 0;
		auto s1 = new Shape(Line, ColorF(0, 0, 0, 0.3));
		const auto a = Size / 2;
		const auto f = Size / steps;
		for (auto i = 0; i <= Steps; i++)
		{
			s1->AddPoint(Vec3(-a + i * f, -a, h));
			s1->AddPoint(Vec3(-a + i * f, a, h));
		}

		for (auto i = 0; i <= Steps; i++)
		{
			s1->AddPoint(Vec3(-a, -a + i * f, h));
			s1->AddPoint(Vec3(a, -a + i * f, h));
		}

		this->Shapes.push_back(s1->WithPosition(Vec3(0, 0, -1)));
	}
};
