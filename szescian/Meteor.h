#pragma once
#include "Geom.h"
#include "ParticleGenerator.h"
#include "Sphere.h"

class Meteor : public Geom
{
public:
	ParticleGenerator* gen;
	IScene* _scene;
	Vec3 _hitPosition;

	Meteor(IScene* scene, Vec3 hitPosition) {
		_scene = scene; 
		hitPosition.Z = _scene->map->GetHeight(hitPosition);
		_hitPosition = hitPosition;

		this->Origin = hitPosition + Vec3(1,1,1) * 1000;
		gen = new ParticleGenerator(scene, this);
		this->Children.push_back(gen);
		const auto x = new Sphere(ZERO, 10, GRAY);
		this->Shapes.push_back(x);
	}

	void Update(float frametime) override
	{
		if (Origin.Z < _hitPosition.Z)
			Delete = true;

		const float speed = 5;
		this->Origin -= Vec3(1, 1, 1) * speed;
	}
};
