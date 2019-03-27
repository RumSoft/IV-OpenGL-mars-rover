#pragma once
#include "Shape.h"

class Geom : public Entity
{
public:
	std::vector<Shape*> Shapes;

	void SetShapesOrigin(const Vec3 newOrigin) { for (auto shape : Shapes) shape->Origin = newOrigin; }
	void AddShapesOrigin(const Vec3 newOrigin) { for (auto shape : Shapes) shape->Origin += newOrigin; }

	void SetShapesRotation(const Quat newRotation) { for (auto shape : Shapes) shape->Rotation = newRotation; }
	void AddShapesRotation(const Quat newRotation) { for (auto shape : Shapes) shape->Rotation += newRotation; }

};
