#pragma once
#include "InputHandler.h"
#include "Geom.h"

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

	std::vector<Geom*> Geometries;
	InputHandler* input;

private:
	void RenderAllObjects();
	void RecursivelyRenderGeometries(Geom* geom, Entity* parent);
	void RecursivelyUpdateGeometries(Geom * geom, float frametime);

};
