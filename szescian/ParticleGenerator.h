#pragma once
#include "Geom.h"
#include "IScene.h"

class ParticleGenerator : public Geom
{
public:
	bool IsActive = true;
	Entity* _entity;
	IScene* _scene;
	Vec3 _offset;
	Particle _p;

	Vec3 GeneratorSize = Vec3(10, 10, 0);
	int spawnRate = 300; //per second

	Vec3 PositionRandom = ONE * 30;
	Vec3 VelocityRandom = ONE *10;
	float LifeTimeRandom = 0.8;

private:
	
	void AddParticle()
	{
		const auto particle = _p
		.WithPosition(_entity->Origin + _entity->Rotation * _offset)
		.Randomized(PositionRandom, VelocityRandom, LifeTimeRandom);
		_scene->Particles.push_back(particle);
	}

public:

	ParticleGenerator(IScene* scene, Particle p, Entity* entityToFollow, Vec3 offset = ZERO)
	{
		_scene = scene;
		_entity = entityToFollow;
		_p = p;
		_offset = offset;
	}

	float particlesLeftToDraw = 0;
	void Update(float frametime) override
	{
		if (!IsActive)
			return;
		const auto particlesToDrawFloat = particlesLeftToDraw + spawnRate * frametime;
		const auto particlesToDraw = int(particlesToDrawFloat);
		particlesLeftToDraw = particlesToDrawFloat - particlesToDraw;

		for(int i = 0; i< particlesToDraw; i++)
			AddParticle();
	}
};
