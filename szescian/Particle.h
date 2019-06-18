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
	bool Additive = true;
	float GravityStrength = 1;
	void Update(float frametime) { 
		Position += Velocity * frametime;
		Velocity -= 100 * UP * GravityStrength * frametime;
	}
	
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
	Particle WithStartSize(float startSize) { StartSize =startSize; return *this; }
	Particle WithEndSize(float endSize)  { EndSize = endSize; return *this; }
	Particle WithLifetime(float lifetime) { Lifetime = lifetime; return *this; }
	Particle WithGravity(float gravity = 1) { GravityStrength = gravity; return *this; }
	Particle IsAdditive(bool additive = 1) { Additive = additive; return *this; }
	Particle Randomized(Vec3 pos, Vec3 vel, float time)
	{
		Velocity += Vec3::RandomSym(vel);
		Position += Vec3::RandomSym(pos);
		Lifetime *= 1 + -time + rand() / (RAND_MAX / (2 * time));
		return *this;
	}
};

class Particles
{
public:
	static Particle Fire() {
		return Particle()
			.WithVelocity(UP * 100)
			.WithLifetime(0.5)
			.WithStartColor(ColorF(0xffcc00))
			.WithEndColor(ColorF(1, 0, 0, 10))
			.WithGravity(false)
			.IsAdditive(true);
	}

	static Particle ExplosionDerbis() {
		return Particle()
			.WithLifetime(2)
			.WithVelocity(UP * 200)
			.WithStartColor(ColorF(0x663300))
			.WithEndColor(ColorF(0x331a00))
			.WithGravity(5)
			.IsAdditive(false);
	}

	static Particle Magnet() {
		return Particle()
			.WithLifetime(2)
			//.WithVelocity(UP * 200)
			.WithStartColor(ColorF(0x4286f4, 5))
			.WithEndColor(ColorF(0xf7faff, 0))
			.WithGravity(0)
			.WithStartSize(3)
			.WithEndSize(1)
			.IsAdditive(true);
	}

	static Particle Ambient()
	{
		return Particle()
			.WithLifetime(5)
			.WithVelocity(-Vec3(1,1,0) * 50)
			.WithStartColor(ColorF(0x925001, 0.2))
			.WithEndColor(ColorF(0x653A17, 1))
			.WithGravity(0)
			.WithStartSize(5)
			.WithEndSize(2)
			.IsAdditive(true);
	}

	static Particle RocketSmoke()
	{
		return Particle()
			.WithLifetime(0.2)
			.WithVelocity(DOWN * 200)
			.WithStartColor(ColorF(0xff6666, 1))
			.WithEndColor(ColorF(0xffffff, 1))
			.WithGravity(0)
			.WithStartSize(10)
			.WithEndSize(1)
			.IsAdditive(true);
	}
};


