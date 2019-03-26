#pragma once
#include "Geom.h"

class Grid : public Geom
{
public:
	float Size;
	int Steps;

	Grid(const float size = 100, const int steps = 10) : Size(size), Steps(steps)
	{
		auto s1 = new Shape(Line, ColorF(0, 0, 0, 0.3));
		float a = Size / 2;
		float f = Size / steps;
		for (int i = 0; i <= Steps; i++)
		{
			s1->Points.emplace_back(-a + i * f, -a, 0);
			s1->Points.emplace_back(-a + i * f, a, 0);
		}

		for (int i = 0; i <= Steps; i++)
		{
			s1->Points.emplace_back(-a, -a + i * f, 0);
			s1->Points.emplace_back(a, -a + i * f, 0);
		}

		this->Shapes.push_back(s1);
	}
};
