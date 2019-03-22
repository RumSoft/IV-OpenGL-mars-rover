#pragma once
#include <vector>
#include "Vec3.h"


class Entity
{
public:
	Vec3 Origin;
	Vec3 Orientation;
};

enum ShapeType
{
	Line,
	Triangle,
	TriangleStrip,
	TriangleFan
};

class Shape : public Entity
{
public:
	std::vector<Vec3> Points;
	ShapeType Type;
};