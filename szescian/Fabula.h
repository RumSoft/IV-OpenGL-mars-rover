#pragma once
#include "Geom.h"
#include "Meteor.h"

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
