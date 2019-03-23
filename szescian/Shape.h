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
	Shape() = default;
	Shape(ShapeType type) : Type(type) {}
	Shape(ShapeType type, ColorF color) : Type(type), Color(color) {}
	std::vector<Vec3> Points;
	ShapeType Type = LineStrip;
	ColorF Color = BLACK;
};