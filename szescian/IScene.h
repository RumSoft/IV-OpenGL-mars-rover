#pragma once
#include "InputHandler.h"
#include "Geom.h"
#include "ObjFile.h"
#include "Lazik.h"

class IScene : public Entity {
public:

	virtual ~IScene() = default;
	virtual void Update();

	void RenderScene();
	void UpdateAllGeometries();
	void UpdatePhysics();

	std::vector<Geom*> Geometries;
	std::vector<ObjFile*> PhysicializedGeometries;
	Lazik* Lazikk;
	InputHandler* input;

private:
	void RenderAllObjects();
	void RecursivelyRenderGeometries(Geom* geom, Entity* parent);
	void RecursivelyUpdateGeometries(Geom * geom);

};
