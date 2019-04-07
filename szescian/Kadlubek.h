#pragma once
#include "Geom.h"
#include "Sphere.h"
#include "Face.h"

class Kadlubek : public Geom
{
public:
	float A, B, C;

	Kadlubek(float a, float b, float c) : A(a), B(b), C(c)
	{
		Vec3 x[9] = {
			Vec3(-A,-B, 0), // nie uzywam, tylko po to bo licze od 1
			Vec3(-A,-B, 0), //x1
			Vec3(-A, B, 0), //x2 itd
			Vec3(A,-B, 0),
			Vec3(A, B, 0),
			Vec3(0.7 * -A,0.9 * -B, C),
			Vec3(0.7 * -A,0.9 * B, C),
			Vec3(0.7 * A,0.9 * -B, C),
			Vec3(0.7 * A,0.9 * B, C),
		};

		this->Shapes.push_back(new Face(x[1], x[2], x[3], x[4], LIGHTGRAY));
		this->Shapes.push_back(new Face(x[3], x[4], x[7], x[8], LIGHTGRAY));
		this->Shapes.push_back(new Face(x[7], x[8], x[5], x[6], LIGHTGRAY));
		this->Shapes.push_back(new Face(x[5], x[6], x[1], x[2], LIGHTGRAY));
		this->Shapes.push_back(new Face(x[1], x[3], x[5], x[7], LIGHTGRAY));
		this->Shapes.push_back(new Face(x[8], x[4], x[6], x[2], LIGHTGRAY));
	}
};
