#pragma once
#include "Entity.h"

class Proxy : public Geom
{
public:
	Vec3 LastPos;
	Quat LastRot;
	bool LastCollided;

	Geom* parent;
	float Mass = 50;
	float 
	MaxSpeed = 5;
	Vec3 Velocity = Vec3::Zero();
	Vec3 Acceleration = Vec3::Zero();
	Proxy(Geom* pparent)
	{
		parent = pparent;
	}


	void Update() override
	{
		
		Acceleration = Vec3::Zero();
		//if (!isColliding) {

			Velocity += Acceleration * MaxSpeed * 0.4;
			Velocity = Vec3::Scale(Velocity, 1 - 10 / Mass);
			parent->Origin += Velocity;
		//}


		isColliding2 = LastCollided;
		LastCollided = isColliding;
		LastPos = parent->Origin;
		LastRot = parent->Rotation;
	}
	bool isColliding = false;
	bool isColliding2 = false;
	int sleep = 0;

	ColorF debugColor = GREEN.Opacity(0.5);
	ColorF debugColor2 = RED.Opacity(0.5);
	void DrawProxy()
	{
		float a = 0.5;
		auto pos = Origin;		auto ppos = parent->Origin;
		auto rot = Rotation;	auto prot = parent->Rotation;
		auto sca = Scale;		auto psca = parent->Scale;

		Vec3 pro[] = {
			
			Vec3(-a,a,-a),
			Vec3(-a,-a,-a),
			Vec3(a,a,-a),
			Vec3(a,-a,-a),
			Vec3(a,a,a),
			Vec3(a,-a,a),
			Vec3(-a,a,a),
			Vec3(-a,-a,a),
			Vec3(-a,a,-a),
			Vec3(-a,-a,-a),
		};
		glLineWidth(5);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_QUAD_STRIP);
		glColor4fv(isColliding ? debugColor.GL() : debugColor2.GL());
		for (const auto p : pro)
		{
			const auto pt = prot * (rot * Vec3::Scale(Vec3::Scale(p, sca), psca) + pos) + ppos;
			glVertex3f(pt.X, pt.Y, pt.Z);
		}
		glEnd();
		glLineWidth(1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void OnCollision(Proxy* obj)
	{
		//p1 = p2
		//mv = mv
		//v(t) = a'(t)
		//mv = m * da 
		
		// this - lazik
		// obj - kamień
		
		isColliding = true;
		obj->Velocity = this->Velocity;
		this->Velocity *= 0;
		this->Acceleration *= 0;
	}
};
