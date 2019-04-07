#pragma once
#include "Geom.h"

#define XYZ(o) o.X, o.Y, o.Z

class Camera : public Geom
{
public:
	Geom* entity;
	InputHandler* input;
	int anim = 100;
	int size = 15;
	Quat from;
	Quat to;
	Camera(Geom* ent)
	{
		entity = ent;
		input = InputHandler::GetInstance();
		Rotation = Quat::Identity();
	}

	void Update() override
	{
		auto offset = Rotation * Vec3(-50, -100, 70)*2;
		auto obj = entity->Origin;
		auto eyes = obj + offset;
		glLoadIdentity();
		gluLookAt(XYZ(eyes), XYZ(obj), 0, 0, 1);

		auto dir = Quat::ToEuler(Rotation);
		string str;
		str.append(to_string(dir.X)); str.append(", ");
		str.append(to_string(dir.Y)); str.append(", ");
		str.append(to_string(dir.Z)); str.append("\n");
		OutputDebugStringA(str.c_str());

		if(anim < size)
		{
			anim++;
			auto f = (float)anim / size;
			Rotation = Quat::Lerp(from, to, sin(f * 3.14 * 0.5f));
		}

		if (input->IsDown(VK_LEFT))
			RequestRotationBy(Quat::FromAngleAxis(D2R(30), axisZ));

		if (input->IsDown(VK_RIGHT)) 
			RequestRotationBy(Quat::FromAngleAxis(D2R(-30), axisZ));

		if (input->IsDown('X'))
			RequestRotationTo(entity->Rotation);

		if (input->IsDown('V'))
			RequestRotationTo(entity->Rotation * Quat::FromAngleAxis(D2R(-120), axisZ));

		//to je krzyweee 
		//if (input->IsDown(VK_UP))
		//	RequestAnim(Rotation * Quat::FromAngleAxis(Deg2Rad(-25), Vec3::Right()));
		//if (input->IsDown(VK_DOWN))
		//	RequestAnim(Rotation * Quat::FromAngleAxis(Deg2Rad(-25), Vec3::Right()));
	}

private:
	void RequestRotationBy(Quat by)
	{
		RequestRotationTo(Rotation * by);
	}

	void RequestRotationTo(Quat _to)
	{
		anim = 0;
		from = Rotation;
		to = _to;
	}
};
