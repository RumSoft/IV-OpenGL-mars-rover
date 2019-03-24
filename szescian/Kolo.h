#pragma once
#include "Geom.h"

class Kolo : public Geom
{
public:
	Vec3 point;
	float R, H;
	//x,y,z jako pozycja srodkowa kola ;		r, h - wiadomo co i jak
	Kolo(Vec3 p, float r, float h) : point(p), R(r), H(h)
	{
		float alpha = 0.0;
		Vec3 P[2] = {
			Vec3(point),
			Vec3(point.X + h,point.Y,point.Z),
		};
		auto s1 = Shape(TriangleStrip, GREEN);					//zewnêtrzne ko³o
		for (alpha = 0.0; alpha <= 2 * M_PI; alpha += M_PI / 8.0)
		{
			P[0].Y = R * sin(alpha) + point.Y;
			P[0].Z = R * cos(alpha) + point.Z;
			P[1].Y = R * sin(alpha) + point.Y;
			P[1].Z = R * cos(alpha) + point.Z;
			s1.Points.push_back(P[0]);
			s1.Points.push_back(P[1]);
		}
		this->Shapes.push_back(s1);

		float R2 = R - R / 3;
		auto s2 = Shape(TriangleStrip, BLUE);					//wewnêtrzne ko³o
		for (alpha = 0.0; alpha <= 2 * M_PI; alpha += M_PI / 8.0)
		{
			P[0].Y = R2 * sin(alpha) + point.Y;
			P[0].Z = R2 * cos(alpha) + point.Z;
			P[1].Y = R2 * sin(alpha) + point.Y;
			P[1].Z = R2 * cos(alpha) + point.Z;
			s2.Points.push_back(P[0]);
			s2.Points.push_back(P[1]);
		}
		this->Shapes.push_back(s2);
	}
};
