#pragma once
#include "Geom.h"
#include "Kadlubek.h"
#include "Kolo.h"

class Lazik : public Geom
{
public:
	Lazik()
	{
		Geom* parts[] = {
			new Kolo(5, -18, -15, 7, 10),
			new Kolo(5, 0, -15, 7, 10),
			new Kolo(5, 18, -15, 7, 10),
			new Kolo(-15, -18, -15, 7, 10),
			new Kolo(-15, 0, -15, 7, 10),
			new Kolo(-15, 18, -15, 7, 10),
			new Kadlubek(15, 25, 10)
			//kolo1(Pozycjakola1)
			//kolo2(pozycjakola2)
			//mozesz dodac zmienne typu Vec3 określające pozycje kola
		};
		for(auto part : parts)
			Shapes.insert(Shapes.end(), part->Shapes.begin(), part->Shapes.end());
	}
};
