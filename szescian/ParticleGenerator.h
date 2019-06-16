#pragma once
#include "Geom.h"
#include "IScene.h"

class ParticleGenerator : public Geom
{
public:
	IScene* _scene;
	Vec3 GeneratorSize = Vec3(10, 10, 0);
	int spawnRate = 100; //(//10/s)
	void AddParticle()
	{
		auto particle = Particle();
		auto posX = rand() / GeneratorSize.X;
		auto posY = rand() / GeneratorSize.Y;
		auto posZ = rand() / GeneratorSize.Z;

		particle.Position = Vec3(posX, posY, posZ);
		_scene->Particles.push_back(particle);
	}
	
	ParticleGenerator(IScene* scene)
	{
		_scene = scene;
		//p = new FireParticle();
		//Shapes.push_back(p);
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

	void PostRender() override
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glPointSize(5.0);
		glBegin(GL_POINTS);
		glColor4f(1, 0.5, 0.3, 0.5);
		for (int i = 0; i < 100; i++)
			glVertex3f(rand() % 10, rand() % 10 + 100, rand() % 10 - 30);
		glEnd();	
		
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

};
