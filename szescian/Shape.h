#pragma once
#include <vector>
#include "Entity.h"
#include "ColorF.h"


enum ShapeType
{
	Line,
	LineStrip,
	Triangle,
	TriangleStrip,
	TriangleFan
};

class Shape : public Entity
{
public:
	std::vector<Vec3> Points;
	ShapeType Type = LineStrip;
	ColorF Color = BLACK;
};