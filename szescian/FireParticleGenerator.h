#pragma once
#include "Geom.h"

struct Particle {
	Vec2 Position, Velocity;
	ColorF Color;
	GLfloat Life;

	Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};

class ParticleGenerator : public Geom
{
public:
	int size = 100;

	ParticleGenerator()
	{
		this->Shapes.push_back(particle);
		
	}

	void PostRender() override
	{
	}

};
