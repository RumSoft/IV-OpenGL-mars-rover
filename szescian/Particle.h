#pragma once
#include "ColorF.h"
#include "Vec3.h"

struct Particle {
	Vec3 Position = Vec3::Zero();
	Vec3 Velocity = UP;
	ColorF StartColor = WHITE;
	ColorF EndColor = WHITE.Opacity(0);
	float StartSize = 10;
	float EndSize = 2;
	float Lifetime = 2.0f;
	float Life = 0.0f;

	void Update(float frametime) { Position += Velocity * frametime; }
	
	Particle(Vec3 position = ZERO,
		Vec3 velocity = ZERO,
		ColorF startColor = BLACK,
		ColorF endColor = WHITE,
		float lifeTime = 1)
		:
		Position(position),
		Velocity(velocity),
		StartColor(startColor),
		EndColor(endColor),
		Lifetime(lifeTime)
	{
		//this constructor is so funny
	}

	Particle WithPosition(Vec3 position) { Position = position; return *this; }
	Particle WithVelocity(Vec3 velocity) { Velocity = velocity; return *this; }
	Particle WithStartColor(ColorF startColor) { StartColor = startColor; return *this; }
	Particle WithEndColor(ColorF endColor) { EndColor = endColor; return *this; }
	Particle WithLifetime(float lifetime) { Lifetime = lifetime; return *this; }
	Particle Randomized(Vec3 pos, Vec3 vel, float time)
	{
		Velocity += Vec3::RandomSym(vel);
		Position += Vec3::RandomSym(pos);
		Lifetime *= 1 + -time + rand() / (RAND_MAX / (2 * time));
		return *this;
	}
};
