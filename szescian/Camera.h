#pragma once
#include "Geom.h"

class Camera : public Geom
{
public:
	Geom* entity;
	InputHandler* input;
	double t = 100;
	double anim_t = 0.3;
	Quat from;
	Quat to;
	double zoom = 1;
	Vec3 Offset = Vec3(-50, -100, 70);
	Camera(Geom* ent)
	{
		entity = ent;
		input = InputHandler::GetInstance();
		Rotation = Quat::Identity();
	}

	void Update(float frametime) override
	{
		auto offset = Rotation * Offset * zoom *2;
		auto obj = entity->Origin;
		auto eyes = obj + offset;
		
		glLoadIdentity();
		gluLookAt(XYZ(eyes), XYZ(obj), XYZ(UP));

		if(t < anim_t)
		{
			t += frametime;
			auto f = (float)t / anim_t;
			Rotation = Quat::Lerp(from, to, sinf(f * 3.14 * 0.5f));
		}

		if (input->IsDown(VK_LEFT))
			RequestRotationBy(Quat::FromAngleAxis(D2R(30), axisZ));

		if (input->IsDown(VK_RIGHT)) 
			RequestRotationBy(Quat::FromAngleAxis(D2R(-30), axisZ));

		if (input->IsDown('X'))
			RequestRotationTo(entity->Rotation);

		if (input->IsDown('V'))
			RequestRotationTo(entity->Rotation * Quat::FromAngleAxis(D2R(-120), axisZ));

		if (input->IsDown(VK_UP))
			zoom -= 1 * frametime;
		if (input->IsDown(VK_DOWN))
			zoom += 1 * frametime;
	}

private:
	void RequestRotationBy(Quat by)
	{
		RequestRotationTo(Rotation * by);
	}

	void RequestRotationTo(Quat _to)
	{
		t = 0;
		from = Rotation;
		to = _to;
	}
};
