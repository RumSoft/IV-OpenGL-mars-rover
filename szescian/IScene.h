#pragma once
#include "InputHandler.h"
#include "Geom.h"

class IScene : public Entity {
public:

	virtual ~IScene() = default;
	virtual void Update();

	void RenderScene();
	void UpdateAllGeometries();

	std::vector<Geom*> Geometries;
	InputHandler* input;

private:
	void RenderAllObjects();
	void RecursivelyRenderGeometries(Geom* geom, Entity* parent);
	void RecursivelyUpdateGeometries(Geom * geom);

};
