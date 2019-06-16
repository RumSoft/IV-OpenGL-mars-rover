#pragma once
#include <gl/gl.h>
#include "ColorF.h"
#include "Vec3.h"

struct Particle {
	Vec3 Position = Vec3::Zero();
	Vec3 PositionRandom = Vec3::Zero();

	Vec3 Velocity = Vec3::Zero();
	Vec3 VelocityRandom = Vec3::Zero();

	ColorF StartColor = WHITE;
	ColorF EndColor = WHITE.Opacity(0);

	float LifeTime = 2.0f;
	float LifeTimeRandom = 1;

	float life = 0.0f;

	void Update(float frametime)
	{
		Position += Velocity * frametime;
	}

	Particle()
	{
	}

protected:
	void Randomize()
	{
		Velocity += Vec3::RandomSym(VelocityRandom);
		Position += Vec3::RandomSym(PositionRandom);
		auto var = -LifeTimeRandom + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * LifeTimeRandom)));
		LifeTime *= 1 + var;

		std::string str = std::to_string(Position.X) + " " + std::to_string(Position.Y) + " " + std::to_string(Position.Z) + "\n";
		OutputDebugStringA(LPCSTR(str.c_str()));
	}
};

struct FireParticle : Particle
{
	FireParticle(Vec3 position)
	{
		Position = position;

		Velocity = UP * 50;
		StartColor = ColorF(1, 0.5, 0.2, 2.0);
		EndColor = ColorF(1, 0.3, 0.1, 0.0);
		LifeTime = 1;
		VelocityRandom = Vec3::One() * 5;
		PositionRandom = Vec3(30, 30, 5);
		Randomize();
	}
};
