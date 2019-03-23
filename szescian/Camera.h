#pragma once
#include "Geom.h"
#include <string>

class Camera : public Geom
{
public:
	InputHandler* input;
	Camera()
	{
		input = InputHandler::GetInstance();
		this->Origin = Vec3(-100, -50, 100);
	}
	
	void translate(Vec3 v) { Origin += Rotation * v; }

	void rotate(float angle, Vec3 axis) { Rotation *= Quat::FromAngleAxis(angle, Rotation * axis); }
	void Yaw	(float angle) { rotate(angle, Vec3(0, 1, 0)); }
	void Pitch	(float angle) { rotate(angle, Vec3(1, 0, 0)); }
	void Roll	(float angle) { rotate(angle, Vec3(0, 0, 1)); }

	void Update() override
	{
		auto pos = this->Origin;
		auto pos2 = Rotation * Vec3(1, 0, 0) + pos;

		if (input->IsDown('W'))
			Yaw(0.1);
		if (input->IsDown('S'))
			Yaw(-0.1);
		if (input->IsDown('A'))
			Roll(0.1);
		if (input->IsDown('D'))
			Roll(-0.1);
		Rotation = Quat::Normalized(Rotation);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(70.0, 1.0, 1.0, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(
			pos.X, pos.Y, pos.Z,
			pos2.X, pos2.Y, pos2.Z,
			0.0, 0.0, 1.0);

		std::string str;
		str.append(std::to_string(pos2.X)); str.append(" ");
		str.append(std::to_string(pos2.Y)); str.append(" ");
		str.append(std::to_string(pos2.Z)); str.append("\n");
		OutputDebugStringA(LPCSTR(str.c_str()));
	}
};
