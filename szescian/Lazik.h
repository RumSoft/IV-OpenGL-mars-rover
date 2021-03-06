﻿#pragma once
#include "Geom.h"
#include "Kadlubek.h"
#include "Kolo.h"
#include "Kamera.h"
#include "Fuel.h"
#include "Proxy.h"
#include "ParticleGenerator.h"

class IScene;

class Lazik : public Geom
{
private:
	InputHandler* input;
public:
	IScene* _scene;
	Chwytak* chwytak;
	Kadlubek* kadlubek;
	Kamera* kamera;
	Kolo* wheel1L;
	Kolo* wheel1R;
	Kolo* wheel2L;
	Kolo* wheel2R;
	Kolo* wheel3L;
	Kolo* wheel3R;
	Proxy* proxy = nullptr;
	CAttribute* Fuel;

	ParticleGenerator* part;
	float H = 30.f, W = 50.f;

	float VelocityDiff;
	float Velocity;
	float VelocityL = 0;
	float VelocityR = 0;
	float TurnRadius;
	float LWheelAngle;
	float RWheelAngle;
	float LDist = 0, RDist = 0;
	float angle = 0;
	float maxAngle = D2R(180);
	float speedAcc = 0;
	float max_speed = 150;
	float WheelRadius = 13.5;
	float MinTurnRadius = 50;
	std::string BatteryLevel;

	Lazik(IScene* scene)
	{
		this->Rotation *= Quat::FromAngleAxis(Deg2Rad(0), Vec3::Up());

		kadlubek = (Kadlubek*)(new Kadlubek(15, 25, 10))->WithPosition(UP * 25);
		kamera = (Kamera*)(new Kamera(15, 3, 8, 5))->WithPosition(Vec3(8, -20, 35));

		float h = 8;
		wheel1L = (Kolo*)(new Kolo(WheelRadius, h))->WithPosition(Vec3(-25, 30, 13));
		wheel1R = (Kolo*)(new Kolo(WheelRadius, h))->WithPosition(Vec3(25, 30, 13));
		wheel2L = (Kolo*)(new Kolo(WheelRadius, h))->WithPosition(Vec3(-25, 0, 13));
		wheel2R = (Kolo*)(new Kolo(WheelRadius, h))->WithPosition(Vec3(25, 0, 13));
		wheel3L = (Kolo*)(new Kolo(WheelRadius, h))->WithPosition(Vec3(-25, -30, 13));
		wheel3R = (Kolo*)(new Kolo(WheelRadius, h))->WithPosition(Vec3(25, -30, 13));

		this->Children.push_back(kadlubek);
		this->Children.push_back(kamera);

		this->Children.push_back(wheel1L);
		this->Children.push_back(wheel1R);
		this->Children.push_back(wheel2L);
		this->Children.push_back(wheel2R);
		this->Children.push_back(wheel3L);
		this->Children.push_back(wheel3R);

		this->Children.push_back((new Ramie(Vec3::Scale(wheel1L->Origin, Vec3(0.5, 0.7, 0)) + UP * 23, wheel1L->Origin+RIGHT*3, 5, 2, 3, ColorF(0x545963))));
		this->Children.push_back((new Ramie(Vec3::Scale(wheel2L->Origin, Vec3(0.5, 0.7, 0)) + UP * 23, wheel2L->Origin+RIGHT*3, 5, 2, 3, ColorF(0x545963))));
		this->Children.push_back((new Ramie(Vec3::Scale(wheel3L->Origin, Vec3(0.5, 0.7, 0)) + UP * 23, wheel3L->Origin+RIGHT*3, 5, 2, 3, ColorF(0x545963))));
		this->Children.push_back((new Ramie(Vec3::Scale(wheel1R->Origin, Vec3(0.5, 0.7, 0)) + UP * 23, wheel1R->Origin+LEFT*3,  5, 2, 3, ColorF(0x545963))));
		this->Children.push_back((new Ramie(Vec3::Scale(wheel2R->Origin, Vec3(0.5, 0.7, 0)) + UP * 23, wheel2R->Origin+LEFT*3,  5, 2, 3, ColorF(0x545963))));
		this->Children.push_back((new Ramie(Vec3::Scale(wheel3R->Origin, Vec3(0.5, 0.7, 0)) + UP * 23, wheel3R->Origin+LEFT*3,  5, 2, 3, ColorF(0x545963))));

		chwytak = (new Chwytak(scene, this));
		chwytak->Rotation = Quat::Identity();
		this->Children.push_back(chwytak->WithPosition(Vec3(0, 22, 35)));
		
		_scene = scene;
		
		proxy = new Proxy(this);
		proxy->Scale = Vec3(60, 50, 33);
		proxy->Origin = Vec3(0, 0, 20);
		input = InputHandler::GetInstance();
		Fuel = (CAttribute*)(new CAttribute(500, 10, 1));

		UpdateBatteryLevel();
	}

	void UpdateBatteryLevel()
	{

		BatteryLevel.clear();
		BatteryLevel.push_back('[');
		const float fuel = Fuel->GetValue() / (float)Fuel->GetMaxValue();
		const int length = 35;
		const int fuell = fuel * length;
		for (auto i = 0; i < length; i++)
			if (i < fuell)
				BatteryLevel.push_back('[');
			else {
				BatteryLevel.push_back('.');
			}
		BatteryLevel.push_back(']');
	}

	Quat zrot = Quat::Identity();

	void Rozpierdol()
	{
		this->Fuel->ChangeValue(-100, true); //decrease by 100/500 = 20% 
		for (auto i = 0; i < 100; i++) {
			auto particle = Particles::Fire()
				.WithPosition(this->Origin);
			_scene->Particles.push_back(particle.Randomized(ONE * 20, ONE * 150 + UP * 50, 0.1));
		}
		this->VelocityL *= 0.0;
		this->VelocityR *= 0.0;
	}

	void Update(float frametime) override
	{
		auto
			vv1 = VelocityL,
			vv2 = VelocityR;

		UpdateSteering(vv1, vv2, frametime);
		CalculateTurnRadius(vv1, vv2);
		CalculateRotations(vv1, vv2, frametime);
		updateWheelRotation(vv1, vv2, frametime);
		updateAngleRotation();

		if (input->IsPressed('M'))
			Rozpierdol();

		if (proxy != nullptr)
			proxy->Update(frametime);

		Fuel->Update(frametime);
		UpdateBatteryLevel();
		this->Origin += Quat::GetZRotation(Rotation) * FORWARD * Velocity * frametime;
	}

	void CalculateRotations(float vv1, float vv2, float frametime)
	{
		if (vv1 == vv2)
			LWheelAngle = RWheelAngle = 0;
		else
		{
			LWheelAngle = atan(H / (TurnRadius - W / 2));
			RWheelAngle = atan(H / (TurnRadius + W / 2));

			const auto angl = (Velocity > 0 ? 1 : -1) * abs(TurnRadius) / 29 * atan(H / TurnRadius) * frametime;
			zrot *= Quat::FromAngleAxis(angl, axisZ);
		}
	}

	void CalculateTurnRadius(float vv1, float vv2)
	{
		if (vv1 == vv2) TurnRadius = 0;
		else
		{
			TurnRadius = W * (vv1 + vv2) / (2 * (vv1 - vv2));

			VelocityDiff = abs(vv1 - vv2) / W;

			TurnRadius *= VelocityDiff;
			if (abs(TurnRadius) < 0.1)
				TurnRadius = 0;
		}
	}

	void UpdateSteering(float& vv1, float& vv2, float frametime)
	{
		if (input->IsDown('D'))
			vv1 *= 0.8;
		else if (input->IsDown('A'))
			vv2 *= 0.8;

		if (VelocityR > max_speed)
			VelocityR = max_speed;
		if (VelocityL > max_speed)
			VelocityL = max_speed;

		if (VelocityR < -max_speed)
			VelocityR = -max_speed;
		if (VelocityL < -max_speed)
			VelocityL = -max_speed;

		if (!input->IsDown('W') && Velocity > 0)
		{
			VelocityL -= 50 * frametime;
			VelocityR -= 50 * frametime;
		}

		if (!input->IsDown('S') && Velocity < 0)
		{
			VelocityL += 50 * frametime;
			VelocityR += 50 * frametime;
		}

		if (input->IsDown('W') && !Fuel->IsZero())
		{
			VelocityL += 100 * frametime;
			VelocityR += 100 * frametime;
			Fuel->ChangeValue(-2 * frametime);
		}

		if (input->IsDown('S') && !Fuel->IsZero())
		{
			VelocityL -= 100 * frametime;
			VelocityR -= 100 * frametime;
			Fuel->ChangeValue(-2 * frametime);
		}

		if (input->IsDown('1'))
		{
			VelocityL += 100 * frametime;
			VelocityR += 100 * frametime;
		}

		if (input->IsDown('K'))
			VelocityR = VelocityL = 0;

		Velocity = (vv1 + vv2) / 2;

		if (proxy->isColliding)
		{
			VelocityL *= 0.9;
			VelocityR *= 0.9;
		}
	}

	void updateAngleRotation()
	{
		if (LWheelAngle > maxAngle)
			LWheelAngle = maxAngle;
		if (RWheelAngle > maxAngle)
			RWheelAngle = maxAngle;
		if (LWheelAngle < -maxAngle)
			LWheelAngle = -maxAngle;
		if (RWheelAngle < -maxAngle)
			RWheelAngle = -maxAngle;

		wheel1L->Rotation = Quat::FromAngleAxis(LWheelAngle, axisZ) * wheel1L->Rotation;
		wheel1R->Rotation = Quat::FromAngleAxis(RWheelAngle, axisZ) * wheel1R->Rotation;

		wheel3L->Rotation = Quat::FromAngleAxis(-LWheelAngle, axisZ) * wheel3L->Rotation;
		wheel3R->Rotation = Quat::FromAngleAxis(-RWheelAngle, axisZ) * wheel3R->Rotation;
	}

	void updateWheelRotation(float vv1, float vv2, float frametime)
	{
		LDist += vv2 * frametime;
		RDist += vv1 * frametime;

		if (LDist > WheelRadius * (2 * M_PI))
			LDist -= WheelRadius * (2 * M_PI);
		if (RDist > WheelRadius * (2 * M_PI))
			RDist -= WheelRadius * (2 * M_PI);

		wheel1L->Rotation = Quat::FromAngleAxis(LDist / WheelRadius, LEFT);
		wheel1R->Rotation = Quat::FromAngleAxis(RDist / WheelRadius, LEFT);

		wheel2L->Rotation = Quat::FromAngleAxis(LDist / WheelRadius, LEFT);
		wheel2R->Rotation = Quat::FromAngleAxis(RDist / WheelRadius, LEFT);

		wheel3L->Rotation = Quat::FromAngleAxis(LDist / WheelRadius, LEFT);
		wheel3R->Rotation = Quat::FromAngleAxis(RDist / WheelRadius, LEFT);
	}
	
};
