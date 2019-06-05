#pragma once
#include "InputHandler.h"
#include "Geom.h"
#include "Lazik.h"
#include "ObjFile.h"

class IScene : public Entity {
public:

	virtual ~IScene() = default;
	void Init() override
	{
		for (auto geom : Geometries)
			geom->Init();

	}

	void RenderScene();
	void UpdateAllGeometries(float frametime);
	void Update(float frametime);
	void UpdatePhysics();

	std::vector<Geom*> Geometries;
	std::vector<ObjFile*> PhysicializedGeometries;
	Lazik* Lazikk;
	InputHandler* input;

	void UpdatePhysics();
	std::vector<ObjFile*> PhysicializedGeometries;
	Lazik* Lazikk;

private:
	void RenderAllObjects();
	void RecursivelyRenderGeometries(Geom* geom, Entity* parent);
	void RecursivelyUpdateGeometries(Geom * geom, float frametime);

};
