#pragma once
#include "Geom.h"
#include "Disc.h"
#include "Chwytak.h"
#include "TextureMemory.h"

class Kolo : public Geom
{
public:
	float R, H;
	Shape* felga1;
	Shape* felga2;
	Kolo(float r, float h) : R(r), H(h)
	{
		int steps = 15;
		float f = 2 * M_PI / steps;
		float r2 = r * 0.7;

		auto s1 = new Shape(TriangleStrip, ColorF(0.2, 0.2, 0.2));
		for (int i = 0; i <= steps; i++)
		{
			s1->AddPoint(Vec3(-h / 2, r * cos(i * f), r * sin(i * f)), 
				Vec3::Normalized(Vec3(0, cos(i * f), sin(i * f))));
			s1->AddPoint(Vec3(-h / 2, r * cos((i + 1) * f), r * sin((i + 1) * f)),
				Vec3::Normalized(Vec3(0, cos((i + 1) * f), sin((i + 1) * f))));

			s1->AddPoint(Vec3(h / 2, r * cos(i * f), r * sin(i * f)),
				Vec3::Normalized(Vec3(0, cos(i * f), sin(i * f))));

			s1->AddPoint(Vec3(h / 2, r * cos((i + 1) * f), r * sin((i + 1) * f)), 
				Vec3::Normalized(Vec3(0, cos((i + 1) * f), sin((i + 1) * f))));

			s1->AddPoint(Vec3(h / 2, r2 * cos(i * f), r2 * sin(i * f)),
				Vec3::Normalized(Vec3(0, cos(i * f), sin(i * f))));
			s1->AddPoint(Vec3(h / 2, r2 * cos((i + 1) * f), r2 * sin((i + 1) * f)), 
				Vec3::Normalized(Vec3(0, cos((i + 1) * f), sin((i + 1) * f))));

			s1->AddPoint(Vec3(-h / 2, r2 * cos(i * f), r2 * sin(i * f)), 
				Vec3::Normalized(Vec3(0, cos(i * f), sin(i * f))));
			s1->AddPoint(Vec3(-h / 2, r2 * cos((i + 1) * f), r2 * sin((i + 1) * f)),
				Vec3::Normalized(Vec3(0, cos((i + 1) * f), sin((i + 1) * f))));
		}

		felga1 = new Disc(GRAY);
		felga2 = new Disc(GRAY);

		this->Shapes.push_back(felga1
			->WithPosition(Vec3(h / 3, 0, 0))
			->WithScale(r*0.9)
			->WithRotation(Quat::FromAngleAxis(Deg2Rad(90), Vec3::Forward())));

		this->Shapes.push_back(felga2
			->WithPosition(Vec3(-h / 3, 0, 0))
			->WithScale(r*0.9)
			->WithRotation(Quat::FromAngleAxis(Deg2Rad(90), Vec3::Forward())));
		this->Shapes.push_back(s1);

	}

	void Init() override
	{
		felga1->texture = TextureMemory::Instance().GetTexture("textures/ProjektFelgi.png");
		felga2->texture = TextureMemory::Instance().GetTexture("textures/ProjektFelgi.png");
		
	}

};
