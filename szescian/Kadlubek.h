#pragma once
#include "Geom.h"
#include "Sphere.h"
#include "Face.h"
#include "TextureMemory.h"

class Kadlubek : public Geom
{
public:
	float A, B, C;

	Shape* top;
	Shape* front, *right, *side3, *side4;
	Shape* bottom;
	Kadlubek(float a, float b, float c) : A(a), B(b), C(c)
	{
		Vec3 x[9] = {
			Vec3(-A,-B, 0), // nie uzywam, tylko po to bo licze od 1
			Vec3(-A,-B, 0), //x1
			Vec3(-A, B, 0), //x2
			Vec3(A,-B, 0),  //x3 itd
			Vec3(A, B, 0),
			Vec3(0.7 * -A,0.9 * -B, C),
			Vec3(0.7 * -A,0.9 * B, C),
			Vec3(0.7 * A,0.9 * -B, C),
			Vec3(0.7 * A,0.9 * B, C),
		};
		bottom = new Face(x[1], x[2], x[3], x[4], LIGHTGRAY);
		front = new Face(x[8], x[4], x[6], x[2], LIGHTGRAY);
		right = new Face(x[3], x[4], x[7], x[8], LIGHTGRAY);
		top = new Face(x[7], x[8], x[5], x[6], LIGHTGRAY);
		side3 = new Face(x[5], x[6], x[1], x[2], LIGHTGRAY);
		side4 = new Face(x[1], x[3], x[5], x[7], LIGHTGRAY);

		this->Shapes.push_back(front);
		this->Shapes.push_back(bottom);
		this->Shapes.push_back(top);
		this->Shapes.push_back(right);
		this->Shapes.push_back(side3);
		this->Shapes.push_back(side4);
	}

	void Init() override
	{
		top->Vertices[1].TextureCoordinate *= 2;
		top->Vertices[3].TextureCoordinate.Y *= 2;
		top->texture = TextureMemory::Instance().GetTexture("textures/ProjektLogo.png");
		side3->texture = TextureMemory::Instance().GetTexture("textures/Metalic.png");
		side4->texture = TextureMemory::Instance().GetTexture("textures/Metalic.png");
		bottom->texture = TextureMemory::Instance().GetTexture("textures/Metalic.png");
		front->texture = TextureMemory::Instance().GetTexture("textures/Metalic.png");
		right->texture = TextureMemory::Instance().GetTexture("textures/Metalic.png");
	}
};
