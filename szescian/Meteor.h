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
		gen = new ParticleGenerator(scene, Particles::Fire(), this);
		this->Children.push_back(gen);
		const auto x = new Sphere(ZERO, 10, GRAY);
		this->Shapes.push_back(x);
	}

	void Update(float frametime) override
	{
		if (Origin.Z < _hitPosition.Z - 5) {
			for (auto i = 0; i < 100; i++) {
				auto particle = Particles::ExplosionDerbis()
					.WithPosition(_hitPosition);
				_scene->Particles.push_back(particle.Randomized(ONE, ONE * 150 + UP * 50, 0.1));
			}
			for (auto i = 0; i < 100; i++) {
				auto particle = Particles::Fire()
					.WithPosition(_hitPosition);
				_scene->Particles.push_back(particle.Randomized(ONE  * 20, ONE * 150 + UP * 50, 0.1));
			}
			Delete = true;

		}

		const float speed = 5;
		this->Origin -= Vec3(1, 1, 1) * speed;
	}
};
