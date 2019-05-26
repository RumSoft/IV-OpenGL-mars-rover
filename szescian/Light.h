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
		this->Origin = Vec3(100, 100);
		body = (new Sphere(Vec3::Zero(), 10, 15, ColorF(0xff6600)));
		this->Shapes.push_back(body);
		input = InputHandler::GetInstance();
	}

	void Update(float frametime)
	{
		auto move = Vec3::Zero();
		
		if (input->IsDown('W'))
			move += FORWARD;
		if (input->IsDown('S'))
			move += BACKWARD;
		if (input->IsDown('A'))
			move += LEFT;
		if (input->IsDown('D'))
			move += RIGHT;

		move *= frametime * 150;

		if (input->IsDown(VK_SHIFT))
			move *= 3;

		this->Origin += move;
	}

};