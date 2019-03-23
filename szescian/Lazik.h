#pragma once
#include "Geom.h"
#include "Kadlubek.h"

class Lazik : public Geom
{
public:
	Lazik()
	{
		Kadlubek k = Kadlubek(15, 25, 10);
		Shapes.insert(Shapes.end(), k.Shapes.begin(), k.Shapes.end());
	}
};
