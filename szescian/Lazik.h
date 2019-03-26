#pragma once
#include "Geom.h"
#include "Kadlubek.h"
#include "Kolo.h"
#include "Ramie.h"
#include "Chwytak.h"
#include "Kamera.h"
#include "Cylinder.h"

class Lazik : public Geom
{
private:
	InputHandler* input;
public:
	std::vector<Geom*> parts;
	Lazik()
	{
		float r = 7, h = 10;
		Vec3 wheels[] = {
			Vec3(25,-20, -10),
			Vec3(25,  0, -10),
			Vec3(25, 20, -10),
			Vec3(-25,-20, -10),
			Vec3(-25,  0, -10),
			Vec3(-25, 20, -10)
		};

		parts.push_back(new Kadlubek(15, 25, 10));
		parts.push_back(new Chwytak(Vec3(0, 23, 9), 4, 6, 25));
		parts.push_back(new Kamera(Vec3(8, -20, 10), 15, 3, 8, 5));

		for (auto wheel : wheels) {
			auto w = new Kolo(wheel, r, h);
			auto r = new Ramie(Vec3::Scale(wheel, Vec3(.4, .8, -0.1)), wheel - Vec3(wheel.X > 0 ? h / 2 : -h / 2, 0, 0), 3, 2, 3, RED);
			parts.push_back(w);
			parts.push_back(r);
		}

		for (auto part : parts)
			for (auto shape : part->Shapes)
				Shapes.push_back(shape);

		input = InputHandler::GetInstance();
	}

	void Update() override
	{
		if (input->IsDown('X')) {
			
		}
	}
};
