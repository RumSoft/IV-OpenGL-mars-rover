
#pragma once
#include "Geom.h"

class Kolo : public Geom
{
public:
	float X, Y, Z, R, H;
	float alpha = 0.0, PI = 3.14;
	//x,y,z jako pozycja srodkowa kola;		r, h - wiadomo co i jak
	Kolo(float x, float y, float z, float r, float h) : X(x), Y(y), Z(z), R(r), H(h)
	{
		Vec3 P[2] = {
			Vec3(x, y, z),
			Vec3(x + h, y, z),
		};

		auto s1 = Shape(TriangleStrip, GREEN);					//zewn�trzne ko�o
		for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 8.0)
		{
			P[0].Y = R * sin(alpha) + y;
			P[0].Z = R * cos(alpha) + z;
			P[1].Y = R * sin(alpha) + y;
			P[1].Z = R * cos(alpha) + z;
			s1.Points.push_back(P[0]);
			s1.Points.push_back(P[1]);
		}
		this->Shapes.push_back(s1);

		R = R - R / 3;
		auto s2 = Shape(TriangleStrip, BLUE);					//wewn�trzne ko�o
		for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 8.0)
		{
			P[0].Y = R * sin(alpha) + y;
			P[0].Z = R * cos(alpha) + z;
			P[1].Y = R * sin(alpha) + y;
			P[1].Z = R * cos(alpha) + z;
			s2.Points.push_back(P[0]);
			s2.Points.push_back(P[1]);
		}
		this->Shapes.push_back(s2);
		/*Vec3 x[9] = {
			Vec3(-A,-B, 0), // nie uzywam, tylko po to bo licze od 1
			Vec3(-A,-B, 0), //x1
			Vec3(-A, B, 0), //x2 itd
			Vec3(A,-B, 0),
			Vec3(A, B, 0),
			Vec3(0.7*-A,0.9* -B, C),
			Vec3(0.7*-A,0.9* B, C),
			Vec3(0.7*A,0.9*-B, C),
			Vec3(0.7*A,0.9* B, C),
		};

		// dooko�a
		auto s1 = Shape(TriangleStrip, GREEN);
		s1.Points.push_back(x[1]);
		s1.Points.push_back(x[2]);
		s1.Points.push_back(x[3]);
		s1.Points.push_back(x[4]);
		s1.Points.push_back(x[7]);
		s1.Points.push_back(x[8]);
		s1.Points.push_back(x[5]);
		s1.Points.push_back(x[6]);
		s1.Points.push_back(x[1]);
		s1.Points.push_back(x[2]);
		this->Shapes.push_back(s1);
		*/
	}
};