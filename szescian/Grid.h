#pragma once
#include "Geom.h"

class Grid : public Geom
{
public:
	float Size;
	int Steps;

	Grid(const float size = 100, const int steps = 10) : Size(size), Steps(steps)
	{
		float h = 0;
		auto s1 = new Shape(Line, ColorF(0, 0, 0, 0.3));
		float a = Size / 2;
		float f = Size / steps;
		for (int i = 0; i <= Steps; i++)
		{
			s1->Points.emplace_back(-a + i * f, -a, h);
			s1->Points.emplace_back(-a + i * f, a, h);
		}

		for (int i = 0; i <= Steps; i++)
		{
			s1->Points.emplace_back(-a, -a + i * f, h);
			s1->Points.emplace_back(a, -a + i * f, h);
		}

		this->Shapes.push_back(s1);
	}
};
