#pragma once
#include "Geom.h"
#include "Meteor.h"
#include "Mineral.h"

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
	IScene* _scene;
public:
	Fabula(IScene* scene)
	{
		_scene = scene;
		SpawnMinerals();
	}

	void SpawnMinerals()
	{
		const int mineralCount = 30;
		for(int i = 0; i< mineralCount; i++)
		{
			auto pos = Vec3::RandomSym(FLAT * 500);
			pos *= 10;
			pos.Z = _scene->map->GetHeight(pos) + 18;
			//this->Children.push_back((new ObjFile("objects", "mineral", 1))
			//	->WithScale(17)
			//	->WithPosition(pos));
			this->Children.push_back((new Mineral(_scene))->WithPosition(pos));
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
	}
};
