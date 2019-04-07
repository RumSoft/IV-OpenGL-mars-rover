#pragma once
#include "Geom.h"
#include "Ramie.h"

class Chwytak : public Geom
{
public:
	float R, H, HR;

	Chwytak(float r, float h, float hr) : R(r), H(h), HR(hr)
	{
		float len = 25;
		
		float angl0 = Deg2Rad(10);
		Quat rot0 = Quat::FromAngleAxis(angl0, Vec3(-1, 0, 0));
		Vec3 p2 = rot0 * Vec3::Up() * len;
		this->Children.push_back(new Ramie(Vec3::Zero(), p2, 14, 2, 3, DARKGRAY));

		float angl = Deg2Rad(50);
		Quat rot1 = Quat::FromAngleAxis(angl, Vec3(1, 0, 0));
		Vec3 p3 = p2 + rot1 * Vec3::Forward() * len;
		this->Children.push_back(new Ramie(p2, p3, 14, 1.5, 2.5, DARKGRAY));

		int steps = 10;
		float f = 2 * M_PI / steps;

		float angl2 = Deg2Rad(45);	
		auto c1 = new Ramie(p3, p3 + Vec3(0, cos((M_PI / 6) + angl2) * 10, sin((M_PI / 6) + angl2) * 10),
			10, 1, 0, DARKGRAY);
		auto c2 = new Ramie(p3 + Vec3(0, cos((M_PI / 6) + angl2) * 10, sin((M_PI / 6) + angl2) * 10),
		                    p3 + Vec3(0, cos((M_PI / 6) + angl2) * 10, sin((M_PI / 6) + angl2) * 10) + Vec3(
			                    0, cos(M_PI / -6) * 10, sin(M_PI / -6) * 10), 
			10, 1, 1.5, DARKGRAY);
		auto c3 = new Ramie(p3, p3 + Vec3(0, cos((M_PI / -6) - angl2) * 10, sin((M_PI / -6) - angl2) * 10),
			10, 1, 0, DARKGRAY);
		auto c4 = new Ramie(p3 + Vec3(0, cos((M_PI / -6) - angl2) * 10, 
			sin((M_PI / -6) - angl2) * 10),
			p3 + Vec3(0, cos((M_PI / -6) - angl2) * 10, sin((M_PI / -6) - angl2) * 10) +	
			Vec3(0, cos(M_PI / 6) * 10, sin(M_PI / 6) * 10),
			10, 1, 1.5, DARKGRAY);

		this->Children.push_back(c1);
		this->Children.push_back(c2);
		this->Children.push_back(c3);
		this->Children.push_back(c4);	
	}
};