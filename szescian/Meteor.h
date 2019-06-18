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

		this->Origin = hitPosition + Vec3(1,1,1) * 500;
		gen = new ParticleGenerator(scene, Particles::Fire(), this);
		this->Children.push_back(gen);
		const auto x = new Sphere(ZERO, 10, BLACK);
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

			auto diff = this->Origin - this->_scene->lazik->Origin;
			if (Vec3::SqrMagnitude(diff) < 2000)
				_scene->lazik->Rozpierdol();
		}

		const float speed = 200;
		this->Origin -= Vec3(1, 1, 1) * speed * frametime;
	}

#ifdef DEBUG
	void PostRender() override
	{
		float r = 33;
		int steps = 20;
		float f = 2 * M_PI / steps;
		glLineWidth(5);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i <= steps; i++)
			glVertex3f(this->Origin.X + r * sin(f * i), this->Origin.Y+ r * cos(f * i), this->Origin.Z);
		glEnd();
	}
#endif

};
