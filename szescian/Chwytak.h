#pragma once
#include "Geom.h"
#include "Ramie.h"

class Chwytak : public Geom
{
public:
	std::vector<Geom*> parts;
	float R, H, HR;

	Chwytak(Vec3 pos, float r, float h, float hr) : R(r), H(h), HR(hr)
	{
		float len = 25;
		float angle = 10;
		float angl = Deg2Rad(angle);
		float angle2 = 45;
		float angl2 = Deg2Rad(angle2);
		Quat rot1 = Quat::FromAngleAxis(angl, Vec3(1, 0, 0));
		Vec3 p2 = pos + Vec3::Up() * len;
		Vec3 p3 = p2 + rot1 * Vec3::Forward() * len;
		parts.push_back(new Ramie(pos, p2, 14, 2, 3, BLUE));
		parts.push_back(new Ramie(p2, p3, 14, 2, 3, BLUE));

		int steps = 10;
		float f = 2 * M_PI / steps;

		float firstang = M_PI / 2; // Kat pierwszego ramienia MAX = M_PI/2; MIN = 0;
		float secondang = M_PI / 4;																			//kat miedzy ramieniem 1 i 2
		float thirdang = M_PI / 10;																			//kat chwytaka
		Vec3 chwyts3 = p3;
		auto c1 = new Ramie(chwyts3, chwyts3 + Vec3(0, cos((M_PI / 6) + thirdang) * 10, sin((M_PI / 6) + thirdang) * 10), 3, 2, 0, RED);
		auto c2 = new Ramie(chwyts3 + Vec3(0, cos((M_PI / 6) + thirdang) * 10, sin((M_PI / 6) + thirdang) * 10),
		                    chwyts3 + Vec3(0, cos((M_PI / 6) + thirdang) * 10, sin((M_PI / 6) + thirdang) * 10) + Vec3(
			                    0, cos(M_PI / -6) * 10, sin(M_PI / -6) * 10), 3, 2, 0, GREEN);
		auto c3 = new Ramie(chwyts3, chwyts3 + Vec3(0, cos((M_PI / -6) - thirdang) * 10, sin((M_PI / -6) - thirdang) * 10), 3, 2, 0, RED);
		auto c4 = new Ramie(chwyts3 + Vec3(0, cos((M_PI / -6) - thirdang) * 10, 
			sin((M_PI / -6) - thirdang) * 10),
			chwyts3 + Vec3(0, cos((M_PI / -6) - thirdang) * 10, sin((M_PI / -6) - thirdang) * 10) +	
			Vec3(0, cos(M_PI / 6) * 10, sin(M_PI / 6) * 10), 3, 2, 0, GREEN);


		parts.push_back(c1);
		parts.push_back(c2);
		parts.push_back(c3);
		parts.push_back(c4);

		for (auto part : parts)
			Shapes.insert(Shapes.end(), part->Shapes.begin(), part->Shapes.end());
	}
};