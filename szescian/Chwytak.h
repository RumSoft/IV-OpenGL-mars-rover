#pragma once
#include "Geom.h"
#include "Ramie.h"
#include "Magnet.h"



class Chwytak : public Geom
{
	IScene* _scene;
public:
	Chwytak(IScene* scene)
	{
		_scene = scene;
		auto pos = UP * 20 + FORWARD * 10;
		auto pos2 = pos + DOWN * 10 + FORWARD * 20;
		Children.push_back((new Ramie(ZERO, pos, 7, 2.5, 3, GRAY)));
		Children.push_back((new Ramie(pos, pos2, 7, 2, 2.5, GRAY)));
		Children.push_back((new Magnet(_scene))
			->WithPosition(pos2 + DOWN * 15 + FORWARD * 4 + RIGHT)
			->WithScale(5)
			->WithRotation(ROT(30, RIGHT) * ROT(90, UP)));
	}

	void Update(float frametime) override
	{
	}
};