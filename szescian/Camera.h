#pragma once
#include "Geom.h"

#define XYZ(o) o.X, o.Y, o.Z

class Camera : public Geom
{
public:
	Geom* entity;
	InputHandler* input;
	Camera(Geom* ent)
	{
		entity = ent;
		input = InputHandler::GetInstance();
		Rotation = Quat::Identity();
	}

	void Update() override
	{
		auto offset = Rotation * Vec3(-100, -100, 100);
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

		if (input->IsDown(VK_LEFT))
			Rotation *= Quat::FromAngleAxis(Deg2Rad(5), Vec3::Up());
		if (input->IsDown(VK_RIGHT))
			Rotation *= Quat::FromAngleAxis(Deg2Rad(-5), Vec3::Up());

		//auto forwardDir = Quat::Lerp()
		if (input->IsDown(VK_UP))
			Rotation *= Quat::FromAngleAxis(Deg2Rad(5), Vec3::Right());
		if (input->IsDown(VK_DOWN))
			Rotation *= Quat::FromAngleAxis(Deg2Rad(-5), Vec3::Right());
	}
};
