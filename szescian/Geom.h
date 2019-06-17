#pragma once
#include "Shape.h"
#include "Face.h"

class Proxy;

class Geom : public Entity
{
public:
	Geom()
	{
		auto z = Vec3::Zero();
		this->Shapes.push_back(new Face(z,z,z,z, LIGHTGRAY));
	}

	void Init() override
	{
		for (auto geoms : Children)
			geoms->Init();
		for (auto shapes : Shapes)
			shapes->Init();
	}
	bool Delete = false;
	std::vector<Shape*> Shapes;
	std::vector<Geom*> Children;
	//virtual void PostInit() {}
	Proxy* proxy = nullptr;

	void SetShapesOrigin(const Vec3 newOrigin) { for (auto shape : Shapes) shape->Origin = newOrigin; }
	void AddShapesOrigin(const Vec3 newOrigin) { for (auto shape : Shapes) shape->Origin += newOrigin; }

	void SetShapesRotation(const Quat newRotation) { for (auto shape : Shapes) shape->Rotation = newRotation; }
	void AddShapesRotation(const Quat newRotation) { for (auto shape : Shapes) shape->Rotation += newRotation; }

	Geom* WithPosition(Vec3 pos) {
		this->Origin = pos;
		//PostInit();
		return this;
	}

	Geom* WithScale(Vec3 scale) {
		this->Scale = scale;
		//PostInit();
		return this;
	}

	Geom* WithScale(float scale) {
		this->Scale = Vec3(scale, scale, scale);
		//PostInit();
		return this;
	}

	Geom* WithRotation(Quat rotation) {
		this->Rotation = rotation;
		//PostInit();
		return this;
	}
};
