#pragma once
#include "InputHandler.h"
#include "Geom.h"

class IScene : public Entity {
public:
	virtual ~IScene() = default;
	virtual void Update() = 0;

	void RenderGeometries();
	void UpdateChildren();

	std::vector<Geom*> Geometries;
	InputHandler* input;
};
