#pragma once
#include "Geom.h"

class Ramie : public Geom
{
public:
	Shape* SphereP1;
	Shape* SphereP2;
	Shape* Body;
	Vec3 From;
	Vec3 To;
	int Steps;
	float Radius;
	float JointRadius;
	ColorF Color;

	Ramie(Vec3 p1, Vec3 p2, int steps = 3, float r = 2, ColorF color = RED) : Ramie(p1, p2, steps, r, 0, color)
	{
	}

	Ramie(Vec3 p1, Vec3 p2, int steps = 3, float r = 2, float r2 = 0, ColorF color = RED)
	{
		From = p1;
		To = p2;
		Steps = steps;
		Radius = r;
		JointRadius = r2;
		Color = color;
		Build();
	}

	void Build()
	{

		Body = new Shape(TriangleStrip, RED);
		auto rot = Quat::FromToRotation(From, To);

		const float f = 2 * M_PI / Steps;
		for (int i = 0; i <= Steps; i++)
		{
			Body->Points.push_back(To + rot*Vec3(Radius * sin(i * f), Radius * cos(i * f)));
			Body->Points.push_back(From + rot*Vec3(Radius * sin(i * f), Radius * cos(i * f)));
		}
		this->Shapes.push_back(Body);

		if (JointRadius > 0)
		{
			SphereP1 = new Sphere(From, JointRadius, 5, Color);
			SphereP2 = new Sphere(To, JointRadius, 5, Color);
			this->Shapes.push_back(SphereP1);
			this->Shapes.push_back(SphereP2);
		}
	}
};
