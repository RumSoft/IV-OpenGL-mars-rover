#pragma once
#include "Geom.h"
#include "Ramie.h"
#include "Magnet.h"


class Chwytak2 : public Geom
{
public:
	Chwytak2()
	{
		this->Shapes.push_back((new Face(ZERO, ZERO + RIGHT * 5, UP * 25, UP * 25 + RIGHT * 5, RED)));

	}

	void Update(float frametime) override
	{
		//this->Children[0]->Rotation *= Quat::FromAngleAxis(0.1, RIGHT);
	}
};

class Chwytak : public Geom
{
public:
	Chwytak()
	{
		/*this->Shapes.push_back((new Face(ZERO, ZERO + RIGHT * 5, UP * 25, UP * 25 + RIGHT * 5, RED)));
		this->Children.push_back((new Chwytak2)
			->WithRotation(Quat::FromAngleAxis(D2R(90), RIGHT))
			->WithPosition(UP * 25));*/
		auto pos = UP * 20 + FORWARD * 10;
		auto pos2 = pos + DOWN * 10 + FORWARD * 20;
		Children.push_back((new Ramie(ZERO, pos, 7, 2.5, 3, GRAY)));
		Children.push_back((new Ramie(pos, pos2, 7, 2, 2.5, GRAY)));
		Children.push_back((new Magnet())
			->WithPosition(pos2 + DOWN * 15 + FORWARD * 4 + RIGHT)
			->WithScale(5)
			->WithRotation(ROT(30, RIGHT) * ROT(90, UP)));
	}

	void Update(float frametime) override
	{
	}
};