#pragma once
#include "Geom.h"
#include "Kadlubek.h"
#include "Kolo.h"
#include "Cylinder.h"
#include <iostream>
#include "LightFollowerLogic.h"

#define debug

#define MAP_SIZE 10
const float myMap[MAP_SIZE][MAP_SIZE] = { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
									  { 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
									  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
									  { 1, 0, 0, 0, 1, 1, 0, 0, 1, 1},
									  { 1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
									  { 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
									  { 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
									  { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
									  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
									  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };
#define mapUnit 100
#define mapOffset (Vec3(1, 1, 0) / 2 * MAP_SIZE)

class Lazik : public Geom
{
private:
	InputHandler* input;
public:
	Kadlubek* kadlubek;
	Kolo* wheel2L;
	Kolo* wheel2R;

	Entity* target;
	Vec3 rayStep;
	float H = 30.f, W = 30.f;
	float V = 0, Vl = 0, Vr = 0, R;
	float angle = 0;
	float max_speed = 150;
	float WheelRadius = 13.5;
	float sensL, sensM, sensR, sensAngl;
	float targetRot, thisRot;
	Vec3 lastRayPos;
	int x, y;
	LightFollowerLogic* lightFollowerFuzzy;
	LightFollowerLogic::Output lightFollowerOutput;

	Lazik(Entity* l)
	{
		target = l;
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

		lightFollowerFuzzy = new LightFollowerLogic();

	}

	float slowUpdateTime = 0;
	const float slowUpdateThreshold = 0.01f;
#define rayStepSize 5
	void AIUpdate(float frametime)
	{
		slowUpdateTime += frametime;
		if (slowUpdateTime >= slowUpdateThreshold)
			slowUpdateTime -= slowUpdateThreshold;
		else
			return;

		//ProcessLightFollowerLogic(frametime);
		ProcessGoalAchieverLogic(frametime);

		Vec3 rayPoint = this->Origin;
		rayStep = Rotation * FORWARD * rayStepSize;

		for (int i = 0; i < 500; i++)
		{
			rayPoint += rayStep;

			lastRayPos = rayPoint / mapUnit + mapOffset;

			x = (int)lastRayPos.X;
			y = (int)lastRayPos.Y;
			if (!IsBetween(x, 0, MAP_SIZE - 1))
				continue;
			if (!IsBetween(y, 0, MAP_SIZE - 1))
				continue;

			if (myMap[x][y] > 0) {
				sensM = i;
				break;
			}
			
		}

		if (input->IsDown('Y'))
			this->Rotation *= Quat::FromAngleAxis(D2R(5), UP);
		if (input->IsDown('T'))
			this->Rotation *= Quat::FromAngleAxis(D2R(-5), UP);

	}

	void Update(float frametime) override
	{

		AIUpdate(frametime);

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
	double wrapMax(double x, double max)
	{
		/* integer math: `(max + x % max) % max` */
		return fmod(max + fmod(x, max), max);
	}
	double wrapMinMax(double x, double min, double max)
	{
		return min + wrapMax(x - min, max - min);
	}

	void ProcessGoalAchieverLogic(float frametime)
	{
		UpdateCollisionSensors();
	}

	void UpdateCollisionSensors()
	{
		PeformSensorRaycastOnMap();
	}
	bool IsBoxHit(Vec3 pos)
	{
		//map offset
		//-Vec3(1,1,0) / 2 * mapUnit * MAP_SIZE
		
	}
	void PeformSensorRaycastOnMap()
	{
		
	}

#pragma region LightFollower
private:
	void ProcessLightFollowerLogic(float frametime)
	{
		UpdateLightSensors();
		lightFollowerOutput = lightFollowerFuzzy->ProcessLightFollower(GetLightSensorsData());
		Vl = 3 * lightFollowerOutput.Vl * frametime;
		Vr = 3 * lightFollowerOutput.Vr * frametime;
	}

	float MapLightSensorValue(float val)
	{
		// desired output:
		//100% light = 0
		//0% light = 512

		//current value
		//100% = 1
		//0% = 0

		return (1 - val) * 512;
	}

	LightFollowerLogic::Input GetLightSensorsData()
	{
		LightFollowerLogic::Input input{};
		input.L = MapLightSensorValue(sensL);
		input.F = MapLightSensorValue(sensM);
		input.R = MapLightSensorValue(sensR);
		return input;
	}

	float SimulateLightSensor(float value, float viewCenterAngle)
	{
		const auto width = D2R(60);

		const auto window = IsBetween(value, viewCenterAngle - width, viewCenterAngle + width);
		const auto func = (cos((viewCenterAngle - value) * 3.14 / width) + 1) / 2;

		return window * func;
	}

	void UpdateLightSensors()
	{
		auto diff = (target->Origin - this->Origin);

		targetRot = -atan2(diff.X, diff.Y);
		thisRot = Quat::ToEuler(Rotation).Z;
		auto anglediff = thisRot - targetRot;

		sensAngl = wrapMinMax(anglediff, -M_PI, +M_PI);

		// left: -60 - -20 deg
		// middle: -20 - 20 deg
		// right: 20 - 60 deg
		sensL = SimulateLightSensor(sensAngl, D2R(-40));
		sensM = SimulateLightSensor(sensAngl, D2R(0));
		sensR = SimulateLightSensor(sensAngl, D2R(40));
	}
public:
#pragma endregion 

	void UpdateWheelRotation(float frametime)
	{
		auto wheel_circumference = (WheelRadius * 2 * M_PI);
		wheel2L->Rotation *= Quat::FromAngleAxis(Vl / wheel_circumference, LEFT);
		wheel2R->Rotation *= Quat::FromAngleAxis(Vr / wheel_circumference, LEFT);
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

		const int width = 5;

		glLineWidth(sensL * sensL * width + 1);
		glBegin(GL_LINE_LOOP);
		glColor3fv(BLUE.GL());
		glVertex3f(XYZ(this->Origin));
		glVertex3f(XYN((this->Origin + Rotation * Quat::FromAngleAxis(D2R(40), UP) * FORWARD * 1000)));
		glEnd();

		glLineWidth(sensM * sensM * width + 1);
		glBegin(GL_LINE_LOOP);	
		glColor3fv(BLUE.GL());
		glVertex3f(XYZ(this->Origin));
		glVertex3f(XYN((this->Origin + Rotation * FORWARD * sensM * rayStepSize)));
		glEnd();

		glLineWidth(sensR * sensR * width + 1);
		glBegin(GL_LINE_LOOP);
		glColor3fv(BLUE.GL());
		glVertex3f(XYZ(this->Origin));
		glVertex3f(XYN((this->Origin + Rotation * Quat::FromAngleAxis(D2R(-40), UP) * FORWARD * 1000)));
		glEnd();


		glLineWidth(1);
		for (int i = 0; i < sensM+5; i++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(XYZ((this->Origin + rayStep * i- Vec3(0,0,  30))));
			glVertex3f(XYZ((this->Origin + rayStep * i + Vec3(0, 0, 30))));
			glEnd();
		}

		glLineWidth(5);
		glBegin(GL_LINE_LOOP);
		glVertex3f(XYZ((this->Origin + rayStep * sensM*rayStepSize - Vec3(0, 0, 30))));
		glVertex3f(XYZ((this->Origin + rayStep * sensM*rayStepSize + Vec3(0, 0, 30))));
		glEnd();


		glLineWidth(3);
		int steps = 100;
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
