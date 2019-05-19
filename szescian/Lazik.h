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
	Kolo* koloL;
	Kolo* koloR;
	float angle=0;

	Lazik()
	{
		this->Origin += Vec3(0, 5, 16.5);
		this->Rotation *= Quat::FromAngleAxis(Deg2Rad(0), Vec3::Up());

		float r = 13.5, h = 8;
		Vec3 wheels[] = {
			Vec3(25, -30, -15),
			Vec3(25, 0, -15),
			//Vec3(25, 30, -15),
			Vec3(-25, -30, -15),
			Vec3(-25, 0, -15),
			//Vec3(-25, 30, -15)
		};

		kadlubek = new Kadlubek(15, 25, 10);
		chwytak = (Chwytak*)(new Chwytak(4, 6, 25))->WithPosition(Vec3(0, 23, 9));
		kamera = (Kamera*)(new Kamera(15, 3, 8, 5))->WithPosition(Vec3(8, -20, 10));
		koloL = (Kolo*)(new Kolo(r, h))->WithPosition(Vec3(-25, 30, -15));
		koloR = (Kolo*)(new Kolo(r, h))->WithPosition(Vec3(25, 30, -15));
		auto rrL = new Ramie(Vec3::Scale(Vec3(-25, 30, -15), Vec3(.4, .7, -0.1)), Vec3(-25, 30, -15) - Vec3(Vec3(-25, 30, -15).X > 0 ? h / 2 : -h / 2, 0, 0), 3, 2, 3, RED);
		auto rrR = new Ramie(Vec3::Scale(Vec3(25, 30, -15), Vec3(.4, .7, -0.1)), Vec3(25, 30, -15) - Vec3(Vec3(25, 30, -15).X > 0 ? h / 2 : -h / 2, 0, 0), 3, 2, 3, RED);

		this->Children.push_back(kadlubek);
		this->Children.push_back(chwytak);
		this->Children.push_back(kamera);
		this->Children.push_back(koloL);
		this->Children.push_back(koloR);
		this->Children.push_back(rrL);
		this->Children.push_back(rrR);

		for (const auto wheel : wheels)
		{
			auto w = (new Kolo(r, h))->WithPosition(wheel);
			auto rr = new Ramie(Vec3::Scale(wheel, Vec3(.4, .7, -0.1)), wheel - Vec3(wheel.X > 0 ? h / 2 : -h / 2, 0, 0), 3, 2, 3, RED);
			this->Children.push_back(w);
			this->Children.push_back(rr);
		}

		input = InputHandler::GetInstance();
	}

	void Update(float frametime) override
	{
		const Vec3 speed = FORWARD * 150 * frametime;
		
		if (input->IsDown('X'))
		{
			this->Origin += Rotation * speed;
			this->Rotation *= Quat::FromAngleAxis(Deg2Rad(-angle * frametime), axisZ);
		}

		if (input->IsDown('V'))
		{
			this->Origin -= Rotation * speed;
			this->Rotation *= Quat::FromAngleAxis(Deg2Rad(angle * frametime), axisZ);
		}

		if (input->IsDown('C'))
		{
			if (angle <= 50)
			{
				this->angle += 2;
				koloL->Rotation *= Quat::FromAngleAxis(Deg2Rad(50 * frametime), -axisZ);
				koloR->Rotation *= Quat::FromAngleAxis(Deg2Rad(50 * frametime), -axisZ);
			}
		}
		else
		{
			if (angle > 0)
			{
				angle--;
				koloL->Rotation *= Quat::FromAngleAxis(Deg2Rad(-25 * frametime), -axisZ);
				koloR->Rotation *= Quat::FromAngleAxis(Deg2Rad(-25 * frametime), -axisZ);
			}
			
		}

		if (input->IsDown('Z'))
		{
			if (angle >= -50)
			{
				this->angle -= 2;
				koloL->Rotation *= Quat::FromAngleAxis(Deg2Rad(50 * frametime), axisZ);
				koloR->Rotation *= Quat::FromAngleAxis(Deg2Rad(50 * frametime), axisZ);
			}
		}
		else
		{
			if (angle < 0)
			{
				angle++;
				koloL->Rotation *= Quat::FromAngleAxis(Deg2Rad(-25 * frametime), axisZ);
				koloR->Rotation *= Quat::FromAngleAxis(Deg2Rad(-25 * frametime), axisZ);
			}

		}
			
		/*const Vec3 speed = FORWARD * 150 * frametime;
		if (input->IsDown('X'))
			this->Origin += Rotation * speed;

		if (input->IsDown('Z'))
			this->Rotation *= Quat::FromAngleAxis(Deg2Rad(95 * frametime), axisZ);

		if (input->IsDown('C'))
			this->Rotation *= Quat::FromAngleAxis(Deg2Rad(-95 * frametime), axisZ);

		if (input->IsDown('V'))
			this->Origin -= Rotation * speed;
			*/
	}

};
