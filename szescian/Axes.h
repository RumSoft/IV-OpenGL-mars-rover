#pragma once
#include "Geom.h"

class Axes : public Geom
{
public:
	int Width = 500;
	Axes(float width = 500)
		: Width(width)
	{
		auto mainX = new Shape(Line, RED.Opacity(0.2));
		mainX->Points.emplace_back(0, 0, 0);
		mainX->Points.emplace_back(Width, 0, 0);
		this->Shapes.push_back(mainX);

		auto mainY = new Shape(Line, GREEN.Opacity(0.2));
		mainY->Points.emplace_back(0, 0, 0);
		mainY->Points.emplace_back(0, Width, 0);
		this->Shapes.push_back(mainY);

		auto mainZ = new Shape(Line, BLUE.Opacity(0.2));
		mainZ->Points.emplace_back(0, 0, 0);
		mainZ->Points.emplace_back(0, 0, Width);
		this->Shapes.push_back(mainZ);
	}

	void PreRender() override { glLineWidth(5); }
	void PostRender() override { glLineWidth(1); }
};
