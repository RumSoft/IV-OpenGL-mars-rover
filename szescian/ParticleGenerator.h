#pragma once
#include "Geom.h"
#include "IScene.h"

class ParticleGenerator : public Geom
{
public:
	Entity* _entity;
	IScene* _scene;
	Vec3 _offset;

	Vec3 GeneratorSize = Vec3(10, 10, 0);
	int spawnRate = 300; //per second

	Vec3 PositionRandom = ONE * 50;
	Vec3 VelocityRandom = Vec3::One();
	float LifeTimeRandom = 0.8;

private:
	
	void AddParticle()
	{
		const auto particle = Particle()
		.WithPosition(_entity->Origin + _offset)
		.WithVelocity(UP * 100)
		.WithLifetime(0.5)
		.WithStartColor(ColorF(0xffcc00))
		.WithEndColor(ColorF(1, 0,0, 10))
		.Randomized(PositionRandom, VelocityRandom, LifeTimeRandom);
		_scene->Particles.push_back(particle);
	}

public:

	ParticleGenerator(IScene* scene, Entity* entityToFollow, Vec3 offset = ZERO)
	{
		_scene = scene;
		_entity = entityToFollow;
	}

	float particlesLeftToDraw = 0;
	void Update(float frametime) override
	{
		const auto particlesToDrawFloat = particlesLeftToDraw + spawnRate * frametime;
		const auto particlesToDraw = int(particlesToDrawFloat);
		particlesLeftToDraw = particlesToDrawFloat - particlesToDraw;

		for(int i = 0; i< particlesToDraw; i++)
			AddParticle();
	}
};
