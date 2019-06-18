#pragma once
#include "Geom.h"
#include "Meteor.h"
#include "Mineral.h"
#include "Rakieta.h"
#include "Fabryka.h"

inline int rand(const int a, const int b)
{
	return rand() % (b - a + 1) + a;
}

inline float randf()
{
	return rand() / RAND_MAX;
}

inline float randf(const float a, const float b)
{
	return a + rand() / (RAND_MAX / (b - a));
}


class Fabula : public Geom
{
public:
	IScene* _scene;
	int points = 0;
	int requiredPoints = 10;
	string RocketFuel = "";

	Rocket* rocket;

	Fabula(IScene* scene)
	{
		_scene = scene;
		SpawnMinerals();
		auto pos = Vec3(500, 100, -80);
		auto scale = ONE * 150;

		rocket = (Rocket*)(new Rocket(_scene))
			->WithPosition(pos)
			->WithScale(scale)
			->WithRotation(ROT(90, RIGHT));
		this->Children.push_back(rocket);


		auto pos2 = Vec3(700, 200, -80);
		auto factory = (new Factory(_scene))
			->WithPosition(pos2)
			->WithScale(100);
		this->Children.push_back(factory);
		UpdateRocketFuel();
	}

	void GatherMineral(Mineral* mineral)
	{
		
		mineral->Delete = true;
		points += 1;

		UpdateRocketFuel();

		if (points >= requiredPoints)
		{
			this->RocketFuel = "PELNE, JEDZ DO RAKIETY";
			this->rocket->enabled = true;
		}

	}

	void UpdateRocketFuel()
	{

		RocketFuel.clear();
		RocketFuel.push_back('[');
		const float fuel = points / (float)requiredPoints;
		const int length = 35;
		const int fuell = fuel * length;
		for(auto i = 0; i<length; i++)
			if (i < fuell)
				RocketFuel.push_back('[');
			else 
				RocketFuel.push_back('.');
		RocketFuel.push_back(']');
	}

	void SpawnMinerals()
	{
		const int mineralCount = 30;
		for(int i = 0; i< mineralCount; i++)
		{
			auto pos = Vec3::RandomSym(FLAT * 500);
			pos *= 10;
			pos.Z = _scene->map->GetHeight(pos) + 18;
			auto obj = (Mineral*)(new Mineral(_scene))->WithPosition(pos);
			this->Children.push_back(obj);
			obj->OnDrop();

		}
	}

	// map boundaries: xy = [-2500, 2000]
	void SlowUpdate()
	{
		const auto pos = Vec3::RandomSym(ONE * 1000) + _scene->lazik->Origin;
		const auto meteor = new Meteor(_scene, pos);
		this->Children.push_back(meteor);
	}

	float time = 0;
	float slowUpdateTime = 1;

	void Update(float frametime) override
	{
		time += frametime;
		if(time > slowUpdateTime)
		{
			SlowUpdate();
			time -= slowUpdateTime;
		}
	
		if (_scene->input->IsPressed('N'))
			GatherMineral(new Mineral(nullptr));
	}
};
