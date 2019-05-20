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

#define debug

class Lazik : public Geom
{
private:
	InputHandler* input;
public:
	Chwytak* chwytak;
	Kadlubek* kadlubek;
	Kamera* kamera;
	Kolo* wheel1L;
	Kolo* wheel1R;
	Kolo* wheel2L;
	Kolo* wheel2R;
	Kolo* wheel3L;
	Kolo* wheel3R;

	float Velocity, VelocityL = 10, VelocityR = 5, TurnRadius, LWheelAngle, RWheelAngle;

	float angle=0;
	float maxAngle = 90;
	float speedAcc = 0;
	float maxSpeed = 150;


	Lazik()
	{
		this->Origin += Vec3(0, 5, 16.5);
		this->Rotation *= Quat::FromAngleAxis(Deg2Rad(0), Vec3::Up());


		kadlubek = new Kadlubek(15, 25, 10);
		chwytak = (Chwytak*)(new Chwytak(4, 6, 25))->WithPosition(Vec3(0, 23, 9));
		kamera = (Kamera*)(new Kamera(15, 3, 8, 5))->WithPosition(Vec3(8, -20, 10));
		
		float r = 13.5, h = 8;
		wheel1L = (Kolo*)(new Kolo(r, h))->WithPosition(Vec3(-25, 30, -15));
		wheel1R = (Kolo*)(new Kolo(r, h))->WithPosition(Vec3(25, 30, -15));
		wheel2L = (Kolo*)(new Kolo(r, h))->WithPosition(Vec3(-25, 0, -15));
		wheel2R = (Kolo*)(new Kolo(r, h))->WithPosition(Vec3(25, 0, -15));
		wheel3L = (Kolo*)(new Kolo(r, h))->WithPosition(Vec3(-25, -30, -15));
		wheel3R = (Kolo*)(new Kolo(r, h))->WithPosition(Vec3(25, -30, -15));

		this->Children.push_back(kadlubek);
		this->Children.push_back(chwytak);
		this->Children.push_back(kamera);

		this->Children.push_back(wheel1L);
		this->Children.push_back(wheel1R);
		this->Children.push_back(wheel2L);
		this->Children.push_back(wheel2R);
		this->Children.push_back(wheel3L);
		this->Children.push_back(wheel3R);

		input = InputHandler::GetInstance();
	}

	void Update(float frametime) override
	{
		auto vv1 = VelocityL, vv2 = VelocityR;

		if (input->IsDown('C'))
			vv1 *= 0.5;
		else if (input->IsDown('Z'))
			vv2 *= 0.5;

		//if (!input->IsDown('X') && VelocityL > 0)
		//{
		//	VelocityL -= 2; 
		//	VelocityR -= 2;
		//}
		//if (!input->IsDown('V') && VelocityL < 0) {
		//	VelocityL += 2;
		//	VelocityR += 2;
		//}

		//if (input->IsDown('X'))
		//{
		//	VelocityL += 6;
		//	VelocityR += 6;
		//}

		//if (input->IsDown('V'))
		//{
		//	VelocityL -= 6;
		//	VelocityR -= 6;
		//}

		if (input->IsDown('1'))
			VelocityL += 10;
		if (input->IsDown('2'))
			VelocityL -= 10;
		if (input->IsDown('1'))
			VelocityR += 10;
		if (input->IsDown('4'))
			VelocityR -= 10;
		if (input->IsDown('K'))
			VelocityR = VelocityL = 0;

		auto H = 30.f;
		auto W = 50.f;
		if (vv1 == vv2)  TurnRadius  = 0;
		else TurnRadius = W * (vv1 + vv2) / (2 * (vv1 - vv2));
		Velocity = abs(vv1 - vv2) / W;

		auto speed = FORWARD * ((VelocityL + VelocityR) / 2) * frametime;

		if (vv1 == vv2)
			LWheelAngle = RWheelAngle = 0;
		else {
			LWheelAngle = atan(H / (TurnRadius - W / 2));
			RWheelAngle = atan(H / (TurnRadius + W / 2));

			auto turnRadius =  frametime*atan(H / TurnRadius);
			Rotation *= Quat::FromAngleAxis(turnRadius, axisZ);
		}

		wheel1L->Rotation = Quat::FromAngleAxis(LWheelAngle, axisZ);
		wheel1R->Rotation = Quat::FromAngleAxis(RWheelAngle, axisZ);
		wheel3L->Rotation = Quat::FromAngleAxis(-LWheelAngle, axisZ);
		wheel3R->Rotation = Quat::FromAngleAxis(-RWheelAngle, axisZ);

		this->Origin += Rotation * speed;
	}

#ifdef debug
	void PostRender() override
	{
		glLineWidth(5);
		glBegin(GL_LINE_LOOP);
		glColor3fv(RED.GL());
		glVertex3f(XYZ(this->Origin));
		glVertex3f(XYZ((this->Origin + Rotation* LEFT * TurnRadius)));
		glEnd();
		
		glBegin(GL_LINE_LOOP);
		glColor3fv(GREEN.GL());
		glVertex3f(XYZ((this->Origin+ Rotation * this->wheel1L->Origin)));
		glVertex3f(XYZ((this->Origin + Rotation * LEFT * TurnRadius)));
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3fv(BLUE.GL());
		glVertex3f(XYZ((this->Origin + Rotation * this->wheel1R->Origin)));
		glVertex3f(XYZ((this->Origin + Rotation * LEFT * TurnRadius)));
		glEnd();

		int steps = 50;
		float f = 2 * M_PI / steps;
		glBegin(GL_LINE_LOOP);
		glColor3fv(WHITE.GL());
		for (int i = 0; i < steps; i++)
			glVertex3f(XYZ((this->Origin + Rotation * LEFT * TurnRadius +  Vec3(sin(i * f), cos(i * f), 0) * (TurnRadius - 25))));
		glEnd();
		glBegin(GL_LINE_LOOP);
		glColor3fv(WHITE.GL());
		for (int i = 0; i < steps; i++)
			glVertex3f(XYZ((this->Origin + Rotation * LEFT * TurnRadius +  Vec3(sin(i * f), cos(i * f), 0) * (TurnRadius + 25))));
		glEnd();

		glLineWidth(1);
	}

};
#endif
