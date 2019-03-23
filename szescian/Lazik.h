#pragma once
#include "Geom.h"
#include "Kadlubek.h"

class Lazik : public Geom
{
public:
	Lazik()
	{
		Geom* parts[] = {
			new Kadlubek(15, 25, 10)
			//kolo1(Pozycjakola1)
			//kolo2(pozycjakola2)
			//mozesz dodac zmienne typu Vec3 okre?laj?ce pozycje kola
		};
		for(auto part : parts)
			Shapes.insert(Shapes.end(), part->Shapes.begin(), part->Shapes.end());
	}
};
