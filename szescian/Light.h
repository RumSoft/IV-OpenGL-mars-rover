#pragma once
#include "Geom.h"
#include "Sphere.h"

class Light : public Geom
{
	
public:
	Shape* body;
	InputHandler* input;
	Light()
	{
		body = (new Sphere(Vec3::Zero(), 5, 15, ColorF(0xff6600)));
		this->Shapes.push_back(body);
		input = InputHandler::GetInstance();
	}

	void Update(float frametime)
	{
		if (input->IsDown('W'))
			this->Origin += FORWARD * 150 * frametime;
		if (input->IsDown('S'))
			this->Origin += BACKWARD * 150 * frametime;
		if (input->IsDown('A'))
			this->Origin += LEFT * 150 * frametime;
		if (input->IsDown('D'))
			this->Origin += RIGHT * 150 * frametime;
	}

};