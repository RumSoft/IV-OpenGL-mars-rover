#pragma once
#include "Geom.h"

class Kadlubek : public Geom
{
public:
	float A,B,C;
	
	Kadlubek(float a, float b, float c) : A(a), B(b), C(c)
	{
		Vec3 x[9] = {
			Vec3(-A,-B, 0), // nie uzywam, tylko po to bo licze od 1
			Vec3(-A,-B, 0), //x1
			Vec3(-A, B, 0), //x2 itd
			Vec3( A,-B, 0),
			Vec3( A, B, 0),
			Vec3(0.7*-A,0.9* -B, C),
			Vec3(0.7*-A,0.9* B, C),
			Vec3( 0.7*A,0.9*-B, C),
			Vec3( 0.7*A,0.9* B, C),
		};

		// dookoła
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


		//dwie dodatkowe sciany których nie ma w tym dookoła
		auto s2 = Shape(TriangleStrip, BLUE);
		s2.Points.push_back(x[1]);
		s2.Points.push_back(x[3]);
		s2.Points.push_back(x[5]);
		s2.Points.push_back(x[7]);
		this->Shapes.push_back(s2);

		auto s3 = Shape(TriangleStrip, RED);
		s3.Points.push_back(x[8]);
		s3.Points.push_back(x[4]);
		s3.Points.push_back(x[6]);
		s3.Points.push_back(x[2]);
		this->Shapes.push_back(s3);
	}
};
