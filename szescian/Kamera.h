#pragma once
#include "Geom.h"

class Kamera : public Geom
{
public:

	Kamera(float h, float a, float b, float c)
	{
		auto kams = Vec3::Zero();

		auto r1 = new Ramie(kams, UP * h + FORWARD, 10, 2, 0, ColorF(0x7e72a0));	//pierwsze ramie
		this->Children.push_back(r1);


		// GÓRA I DÓŁ 
		auto s1 = new Shape(TriangleStrip, GRAY);
		s1->Origin = kams + Vec3(0, 0, h);
		s1->AddPoint(Vec3(-a, b, c),
			Vec2(0.9, 0.75));
		s1->AddPoint(Vec3(a, b, c),
			Vec2(0.9, 0.95));
		s1->AddPoint(Vec3(-a, -a, c),
			Vec2(0.1, 0.75));
		s1->AddPoint(Vec3(a, -a, c),
			Vec2(0.1, 0.95));
		s1->AddPoint(Vec3(-a, -b, c / 3),
			Vec2(0.5, 0.75));
		s1->AddPoint(Vec3(a, -b, c / 3),
			Vec2(0.5, 0.95));
		s1->AddPoint(Vec3(-a, -b, 0),
			Vec2(0.1, 0.75));
		s1->AddPoint(Vec3(a, -b, 0),
			Vec2(0.1, 0.95));
		s1->AddPoint(Vec3(-a, b, 0),
			Vec2(0.9, 0.75));
		s1->AddPoint(Vec3(a, b, 0),
			Vec2(0.9, 0.75));
		this->Shapes.push_back(s1);


		// LEWO OBIEKTYW PRAWO
		auto s2 = new Shape(TriangleStrip, GRAY);
		s2->Origin = kams + Vec3(0, 0, h);
		s2->AddPoint(Vec3(-a, -b, 0),
			Vec2(0,0));
		s2->AddPoint(Vec3(-a, -b, c / 3),
			Vec2(0, 1));
		s2->AddPoint(Vec3(a, -b, 0),
			Vec2(1, 1));
		s2->AddPoint(Vec3(a, -b, c / 3),
			Vec2(1, 0));
		s2->AddPoint(Vec3(a, -a, 0),
			Vec2(0, 0));
		s2->AddPoint(Vec3(a, -a, c),
			Vec2(0, 0));

		s2->AddPoint(Vec3(a, b, 0),
			Vec2(0.6, 0.45));
		s2->AddPoint(Vec3(a, b, c),
			Vec2(0.6, 0.15));
		s2->AddPoint(Vec3(-a, b, 0),
			Vec2(0.9, 0.45));
		s2->AddPoint(Vec3(-a, b, c),
			Vec2(0.9, 0.15));

		s2->AddPoint(Vec3(-a, -a, 0),
			Vec2(0.9, 0.15));
		s2->AddPoint(Vec3(-a, -a, c),
			Vec2(0, 0));
		s2->AddPoint(Vec3(-a, -b, 0),
			Vec2(0, 0));
		s2->AddPoint(Vec3(-a, -b, c / 3),
			Vec2(0, 0));
		this->Shapes.push_back(s2);
	}

	void Init() override
	{
		auto tex = Shape::LoadTexture("textures/ProjektKamera.png", 1);
		this->Shapes[0]->texture = tex;
		this->Shapes[1]->texture = tex;
		//this->Shapes[2]->texture = tex;
	
	}
};