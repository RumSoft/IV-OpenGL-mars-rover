#pragma once
#include "Geom.h"
#include "Kadlubek.h"
#include "Kolo.h"
#include "Ramie.h"

class Lazik : public Geom
{
public:
	std::vector<Geom*> parts;

	Lazik()
	{
		float r = 7, h = 10;
		Vec3 wheels[] = {
			Vec3( 25,-20, -10),
			Vec3( 25,  0, -10),
			Vec3( 25, 20, -10),
			Vec3(-25,-20, -10),
			Vec3(-25,  0, -10),
			Vec3(-25, 20, -10)
		};

		parts.push_back(new Kadlubek(15, 25, 10));
		
		for (auto wheel : wheels) {
			auto w = new Kolo(wheel, r, h);
			auto r = new Ramie(Vec3::Scale(wheel, Vec3(.4, .8, -0.1)) , wheel - Vec3(wheel.X > 0 ? h/2 : -h/2, 0, 0), 3, 2, 3, RED);
			parts.push_back(w);
			parts.push_back(r);
		}

		for (auto part : parts)
			Shapes.insert(Shapes.end(), part->Shapes.begin(), part->Shapes.end());
	}
};
