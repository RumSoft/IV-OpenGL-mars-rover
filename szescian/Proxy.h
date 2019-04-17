#pragma once
#include "Entity.h"

class Proxy : public Geom
{
public:
	Geom* parent;
	float Mass = 50;
	Vec3 Velocity = Vec3::Zero();
	Vec3 Acceleration = Vec3::Zero();
	Proxy(Geom* pparent)
	{
		parent = pparent;
	}


	void Update() override
	{
		parent->Origin += Acceleration;
		Acceleration = Vec3::Scale(Acceleration, 1 - 10/Mass);
	}

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
		glColor4fv(GREEN.Opacity(0.5).GL());
		for (const auto p : pro)
		{
			const auto pt = prot * (rot * Vec3::Scale(Vec3::Scale(p, sca), psca) + pos) + ppos;
			glVertex3f(pt.X, pt.Y, pt.Z);
		}
		glEnd();
		glLineWidth(1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}



	void OnCollision(Geom* obj)
	{
		OutputDebugStringA("coll, ");
	}
};
