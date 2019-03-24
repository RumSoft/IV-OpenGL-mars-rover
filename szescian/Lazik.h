#pragma once
#include "Geom.h"
#include "Kadlubek.h"
#include "Kolo.h"

class Lazik : public Geom
{
public:
	Lazik()
	{
		float r = 7, h = 10;
		Vec3 k[6] = {
			Vec3(5,-18,-15),
			Vec3(5, 0,-15),
			Vec3(5, 18,-15),
			Vec3(-15,-18,-15),
			Vec3(-15,0,-15),
			Vec3(-15,18,-15),
		};
		Geom* parts[] = {
			new Kolo(k[0],r,h),
			new Kolo(k[1],r,h),
			new Kolo(k[2],r,h),
			new Kolo(k[3],r,h),
			new Kolo(k[4],r,h),
			new Kolo(k[5],r,h),	
			new Kadlubek(15, 25, 10),
		};
		for(auto part : parts)
			Shapes.insert(Shapes.end(), part->Shapes.begin(), part->Shapes.end());
	}
};
