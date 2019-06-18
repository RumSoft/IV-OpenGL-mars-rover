#pragma once
#include "ObjFile.h"
#include "Camera.h"

class Rocket : public ObjFile
{
	IScene* _scene;
public:
	ParticleGenerator* par1;
	ParticleGenerator* par2;
	ParticleGenerator* par3;
	ParticleGenerator* par4;
	Rocket(IScene* scene) : ObjFile("objects", "rakieta", 0)
	{
		_scene = scene;
		par1 = new ParticleGenerator(_scene, Particles::RocketSmoke(), this, UP * 100);
		par2 = new ParticleGenerator(_scene, Particles::RocketSmoke(), this, RIGHT * 50 + UP * 20);
		par3 = new ParticleGenerator(_scene, Particles::RocketSmoke(), this, LEFT * 70 + UP * 10);
		par4 = new ParticleGenerator(_scene, Particles::RocketSmoke().WithStartSize(15).WithLifetime(0.3), this, UP * 40 + FORWARD * 20);
	}

	float speed = 0;
	bool flying = false;
	bool enabled = false;
	void Fly(float frametime)
	{
		_scene->lazik->Origin = this->Origin + UP * 50 + UP * speed * 5;
		speed += 1 * frametime;
		this->Origin.Z += speed;
		par1->Update(frametime);
		par2->Update(frametime);
		par3->Update(frametime);
		par4->Update(frametime);

		_scene->camera->RequestRotationBy(ROT(1,UP));
		
	}

	void EnableFlying()
	{
		flying = true;
		_scene->lazik->Scale *= 0.01;
	}

	void Update(float frametime) override
	{
		if(enabled)
		{
			auto diff = this->Origin - this->_scene->lazik->Origin;
			if (Vec3::SqrMagnitude(diff) < 10000)
				EnableFlying();
		}
		if (flying)
			Fly(frametime);
	}
};
