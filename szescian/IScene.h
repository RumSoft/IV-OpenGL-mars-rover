#pragma once
#include "InputHandler.h"
#include "Geom.h"

class Lazik;
class Map;
class ObjFile;

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
	InputHandler* input;
	
	Lazik* lazik;
	//vector<Lazik*> laziki;
	Map* map;
	ObjFile* ground;

private:
	void RenderAllObjects();
	void RecursivelyRenderGeometries(Geom* geom, Entity* parent);
	void RecursivelyUpdateGeometries(Geom * geom, float frametime);

};
