#pragma once
#include "Geom.h"
#include "Kadlubek.h"
#include "Kolo.h"
#include "Ramie.h"
#include "Chwytak.h"
#include "Kamera.h"
#include "Cylinder.h"
#include <iostream>
#include <string>

class Lazik : public Geom
{
private:
	InputHandler* input;
public:
	Chwytak* chwytak;
	Kadlubek* kadlubek;
	Kamera* kamera;

	Lazik()
	{
		this->Origin += Vec3(0, 5, 16.5);
		this->Rotation *= Quat::FromAngleAxis(Deg2Rad(0), Vec3::Up());

		float r = 7, h = 10;
		Vec3 wheels[] = {
			Vec3(25, -20, -10),
			Vec3(25, 0, -10),
			Vec3(25, 20, -10),
			Vec3(-25, -20, -10),
			Vec3(-25, 0, -10),
			Vec3(-25, 20, -10)
		};

		kadlubek = new Kadlubek(15, 25, 10);
		chwytak = (Chwytak*)(new Chwytak(4, 6, 25))->WithPosition(Vec3(0, 23, 9));
		kamera = (Kamera*)(new Kamera(15, 3, 8, 5))->WithPosition(Vec3(8, -20, 10));

		this->Children.push_back(kadlubek);
		this->Children.push_back(chwytak);
		this->Children.push_back(kamera);

		for (const auto wheel : wheels)
		{
			auto w = (new Kolo(r, h))->WithPosition(wheel);
			auto rr = new Ramie(Vec3::Scale(wheel, Vec3(.4, .8, -0.1)), wheel - Vec3(wheel.X > 0 ? h / 2 : -h / 2, 0, 0), 3, 2, 3, RED);
			this->Children.push_back(w);
			this->Children.push_back(rr);
		}

		input = InputHandler::GetInstance();
	}

	void Update(float frametime) override
	{
		const Vec3 speed = FORWARD * 150 * frametime;
		if (input->IsDown('X'))
			this->Origin += Rotation * speed;

		if (input->IsDown('Z'))
			this->Rotation *= Quat::FromAngleAxis(Deg2Rad(95 * frametime), axisZ);

		if (input->IsDown('C'))
			this->Rotation *= Quat::FromAngleAxis(Deg2Rad(-95 * frametime), axisZ);

		if (input->IsDown('V'))
			this->Origin -= Rotation * speed;
	}

};
