#pragma once
#include "Geom.h"

class Axes : public Geom
{
public:
	int Width = 500;
	Axes(float width = 500)
		: Width(width)
	{
		auto mainX = Shape();
		mainX.Color = RED.Opacity(0.5);
		mainX.Type = Line;
		mainX.Points.emplace_back(0, 0, 0);
		mainX.Points.emplace_back(Width, 0, 0);
		this->Shapes.push_back(mainX);

		auto mainY = Shape();
		mainY.Color = GREEN.Opacity(0.5);
		mainY.Type = Line;
		mainY.Points.emplace_back(0, 0, 0);
		mainY.Points.emplace_back(0, Width, 0);
		this->Shapes.push_back(mainY);

		auto mainZ = Shape();
		mainY.Color = BLUE.Opacity(0.5).Blue(.5);
		mainZ.Type = Line;
		mainZ.Points.emplace_back(0, 0, 0);
		mainZ.Points.emplace_back(0, 0, Width);
		this->Shapes.push_back(mainZ);
	}

	void PreRender() override { glLineWidth(5); }
	void PostRender() override { glLineWidth(1); }
};
