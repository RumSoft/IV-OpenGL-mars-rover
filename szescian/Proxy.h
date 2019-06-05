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
	Vec3 _acc = Vec3::Zero();

	Proxy(Geom* pparent)
	{
		parent = pparent;
	}

	void Update(float frametime) override;

	bool isColliding = false;
	bool isColliding2 = false;
	int sleep = 0;

	ColorF debugColor = GREEN.Opacity(0.5);
	ColorF debugColor2 = RED.Opacity(0.5);
	void DrawProxy();

	void OnCollision(Proxy* obj);
};
