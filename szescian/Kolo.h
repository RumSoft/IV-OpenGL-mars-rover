#pragma once
#include "Geom.h"

class Kolo : public Geom
{
public:
	Vec3 point;
	float R, H, alpha, PI;
	//x,y,z jako pozycja srodkowa kola ;		r, h - wiadomo co i jak
	Kolo(Vec3 p, float r, float h) : point(p), R(r), H(h), alpha(0.0), PI(3.14)
	{
		Vec3 P[2] = {
			Vec3(point),
			Vec3(point.X+h,point.Y,point.Z),
		};
		auto s1 = Shape(TriangleStrip, GREEN);					//zewnêtrzne ko³o
		for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 8.0)
		{
			P[0].Y = R * sin(alpha) + point.Y;
			P[0].Z = R * cos(alpha) + point.Z;
			P[1].Y = R * sin(alpha) + point.Y;
			P[1].Z = R * cos(alpha) + point.Z;
			s1.Points.push_back(P[0]);
			s1.Points.push_back(P[1]);
		}
		this->Shapes.push_back(s1);

		R = R - R / 3;
		auto s2 = Shape(TriangleStrip, BLUE);					//wewnêtrzne ko³o
		for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 8.0)
		{
			P[0].Y = R * sin(alpha) + point.Y;
			P[0].Z = R * cos(alpha) + point.Z;
			P[1].Y = R * sin(alpha) + point.Y;
			P[1].Z = R * cos(alpha) + point.Z;
			s2.Points.push_back(P[0]);
			s2.Points.push_back(P[1]);
		}
		this->Shapes.push_back(s2);
	}
};
