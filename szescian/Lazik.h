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
	Kadlubek* kadlubek;
	Kolo* wheel2L;
	Kolo* wheel2R;

	Entity* light;

	float H = 30.f, W = 30.f;
	float V = 0, Vl = 0, Vr = 0, R;
	float LDist = 0, RDist = 0;
	float angle = 0;
	float max_speed = 150;
	float WheelRadius = 13.5;
	float sensL, sensM, sensR, sensAngl;

	Lazik(Entity* l)
	{
		light = l;
		this->Origin += Vec3(0, 5, 16.5);
		this->Rotation *= Quat::FromAngleAxis(Deg2Rad(0), Vec3::Up());
		kadlubek = new Kadlubek(W / 2, H / 2, 10);

		float h = 2;
		wheel2L = (Kolo*)(new Kolo(WheelRadius, h))->WithPosition(Vec3(-W / 2, 0, -15));
		wheel2R = (Kolo*)(new Kolo(WheelRadius, h))->WithPosition(Vec3(W / 2, 0, -15));

		this->Children.push_back(kadlubek);
		this->Children.push_back(wheel2L);
		this->Children.push_back(wheel2R);
		input = InputHandler::GetInstance();
	}

	float slowUpdateTime = 0;
	const float slowUpdateThreshold = 0.01f;
	void SlowUpdate(float frametime)
	{
		slowUpdateTime += frametime;
		if (slowUpdateTime >= slowUpdateThreshold)
			slowUpdateTime -= slowUpdateThreshold;
		else
			return;

		UpdateSensors();

	}


	void Update(float frametime) override
	{
		SlowUpdate(frametime);


		UpdateSteering(frametime);
		LimitSpeed();
		CalculateTurnRadius(frametime);
		UpdateWheelRotation(frametime);
		auto speed = 100;
		this->Origin += Rotation * FORWARD * (speed * V * frametime);
	}

	bool IsBetween(float val, float a, float b)
	{
		if (a > b)
			return IsBetween(val, b, a);
		return val <= b && val >= a;
	}

	float calcSensorValueFunc(float value, float viewCenterAngle)
	{
		const auto width = D2R(60);

		const auto window = IsBetween(value, viewCenterAngle - width, viewCenterAngle + width);
		const auto func = (cos((viewCenterAngle-value) * 3.14 / width) + 1) / 2;

		return window * func;
	}

	void UpdateSensors()
	{
		auto diff = (light->Origin - this->Origin);
		auto lightAngl = -atan2(diff.X, diff.Y);
		Vec3 rot = Quat::ToEuler(Rotation);
		sensAngl = -fmod(lightAngl - rot.Z, M_PI);

		// left: -60 - -20 deg
		// middle: -20 - 20 deg
		// right: 20 - 60 deg
		sensL = calcSensorValueFunc(sensAngl, D2R(-40));
		sensM = calcSensorValueFunc(sensAngl, D2R(0));
		sensR = calcSensorValueFunc(sensAngl, D2R(40));
	}

	void UpdateWheelRotation(float frametime)
	{
		LDist += Vl;
		RDist += Vr;

		if (LDist > WheelRadius * (2 * M_PI))
			LDist -= WheelRadius * (2 * M_PI);
		if (RDist > WheelRadius * (2 * M_PI))
			RDist -= WheelRadius * (2 * M_PI);

		wheel2L->Rotation = Quat::FromAngleAxis(LDist / WheelRadius, LEFT);
		wheel2R->Rotation = Quat::FromAngleAxis(RDist / WheelRadius, LEFT);
	}

	void CalculateTurnRadius(float frametime)
	{

		R = (W / 2) * (Vl + Vr) / (Vr - Vl);

		angle = (Vr - Vl) / H;
		this->Rotation *= Quat::FromAngleAxis(angle * 1.65, UP);
		V = (Vr + Vl) / 2;

	}

	void LimitSpeed()
	{
		if (Vr > max_speed)
			Vr = max_speed;
		if (Vl > max_speed)
			Vl = max_speed;

		if (Vr < -max_speed)
			Vr = -max_speed;
		if (Vl < -max_speed)
			Vl = -max_speed;
	}

	void UpdateSteering(float frametime)
	{
		if (input->IsDown('1'))
			Vl += 5 * frametime;
		if (input->IsDown('2'))
			Vr += 5 * frametime;
		if (input->IsDown('3'))
			Vl -= 5 * frametime;
		if (input->IsDown('4'))
			Vr -= 5 * frametime;


		if (input->IsDown('K'))
			Vr = Vl = 0;
	}


#ifdef debug
	void PostRender() override
	{
		glLineWidth(5);
		glBegin(GL_LINE_LOOP);
		glColor3fv(RED.GL());
		glVertex3f(XYZ(this->Origin));
		glVertex3f(XYN((this->Origin + Rotation * LEFT * R)));
		glEnd();


		int steps = 50;
		float f = 2 * M_PI / steps;
		glBegin(GL_LINE_LOOP);
		glColor3fv(WHITE.GL());
		for (int i = 0; i < steps; i++)
			glVertex3f(XYN((this->Origin + Rotation * LEFT * R + Vec3(sin(i * f), cos(i * f), 0) * (R))));
		glEnd();
		glBegin(GL_LINE_LOOP);
		glColor3fv(WHITE.GL());
		for (int i = 0; i < steps; i++)
			glVertex3f(XYN((this->Origin + Rotation * LEFT * R + Vec3(sin(i * f), cos(i * f), 0) * (R))));
		glEnd();
		glBegin(GL_LINE_LOOP);
		glColor3fv(GREEN.GL());
		for (int i = 0; i < steps; i++)
			glVertex3f(XYN((this->Origin + Rotation * LEFT * R + Vec3(sin(i * f), cos(i * f), 0) * R)));
		glEnd();
		glLineWidth(1);
	}
#endif

};



