#pragma once
#include "Geom.h"
#include "Ramie.h"


class Chwytak3 : public Geom
{
public:
	Chwytak3()
	{
		Vec3 p = Vec3(0, 10, 8);
		Vec3 p2 = Vec3(0, 20, 4);

		this->Children.push_back(new Ramie(ZERO, p, 14, 1, 0, DARKGRAY));
		this->Children.push_back(new Ramie(p, p2, 14, 1, 1.5, DARKGRAY));
		
	}
};

class Chwytak2 : public Geom
{
	public:
	void Update(float frametime) override
	{
		//this->Children[1]->Rotation *= Quat::FromAngleAxis(D2R(180) * frametime, Vec3(1,1, 1));
	}
	Chwytak2()
	{
		Vec3 p = Vec3(0, 35, 0);
		this->Children.push_back(new Ramie(ZERO, p, 14, 1.5, 2.5, DARKGRAY));

		auto raczka1 = (new Chwytak3)->WithPosition(p);
		auto raczka2 = (new Chwytak3)->WithPosition(p);
		//raczka2->Rotation *= Quat::FromAngleAxis(D2R(180), FORWARD);
		this->Children.push_back(raczka1);
		this->Children.push_back(raczka2);
		/*
		int steps = 10;
		float f = 2 * M_PI / steps;

		float angl2 = Deg2Rad(45);
		auto c1 = new Ramie(p3, p3 + Vec3(0, cos((M_PI / 6) + angl2) * 10, sin((M_PI / 6) + angl2) * 10),
			10, 1, 0, DARKGRAY);
		auto c2 = new Ramie(p3 + Vec3(0, cos((M_PI / 6) + angl2) * 10, sin((M_PI / 6) + angl2) * 10),
			p3 + Vec3(0, cos((M_PI / 6) + angl2) * 10, sin((M_PI / 6) + angl2) * 10) + Vec3(
				0, cos(M_PI / -6) * 10, sin(M_PI / -6) * 10),
			10, 1, 1.5, DARKGRAY);
		auto c3 = new Ramie(p3, p3 + Vec3(0, cos((M_PI / -6) - angl2) * 10, sin((M_PI / -6) - angl2) * 10),
			10, 1, 0, DARKGRAY);
		auto c4 = new Ramie(p3 + Vec3(0, cos((M_PI / -6) - angl2) * 10,
			sin((M_PI / -6) - angl2) * 10),
			p3 + Vec3(0, cos((M_PI / -6) - angl2) * 10, sin((M_PI / -6) - angl2) * 10) +
			Vec3(0, cos(M_PI / 6) * 10, sin(M_PI / 6) * 10),
			10, 1, 1.5, DARKGRAY);

		this->Children.push_back(c1);
		this->Children.push_back(c2);
		this->Children.push_back(c3);
		this->Children.push_back(c4);*/

	}
};

class Chwytak : public Geom
{
public:
	float R, H, HR;

	Chwytak(float r, float h, float hr) : R(r), H(h), HR(hr)
	{
		float len = 25;
		float angl0 = Deg2Rad(10);
		Quat rot0 = Quat::FromAngleAxis(angl0, Vec3(-1, 0, 0));
		Vec3 p2 = rot0 * Vec3::Up() * len;
		this->Children.push_back(new Ramie(Vec3::Zero(), p2, 14, 2, 3, DARKGRAY));
		this->Children.push_back((new Chwytak2())->WithPosition(p2));
	}

	void Update(float frametime) override
	{
		this->Children[0]->Rotation = this->Rotation;
		//this->Children[4]->Rotation *= Quat::FromAngleAxis(0.01, FORWARD);
		//this->Children[2]->Rotation *= Quat::FromAngleAxis(0.01, FORWARD);
		//
		//this->Children[3]->Origin = ((Ramie*)this->Children[2])->Rotation * ((Ramie*)this->Children[2])->To + ((Ramie*)this->Children[2])->Origin;
		//this->Children[5]->Origin = ((Ramie*)this->Children[4])->Rotation * ((Ramie*)this->Children[4])->To + ((Ramie*)this->Children[4])->Origin;
		//this->Children[3]->Rotation *= Quat::FromAngleAxis(0.01, FORWARD);
		//this->Children[5]->Rotation *= Quat::FromAngleAxis(0.01, FORWARD);
	}
};