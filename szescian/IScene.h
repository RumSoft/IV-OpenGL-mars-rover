#pragma once
#include "InputHandler.h"
#include "Geom.h"
#include "Particle.h"

class Lazik;
class Map;
class ObjFile;
class Camera;
//class Fabula;

class IScene : public Entity {
public:

	virtual ~IScene() = default;
	void Init() override
	{
		for (auto geom : Geometries)
			geom->Init();

	}

	void RenderScene();
	void UpdateParticle(Particle particle, float frametime);
	void UpdateAllGeometries(float frametime);
	void Update(float frametime);
	void UpdatePhysics();

	std::vector<Particle> Particles = std::vector<Particle>(1000);

	std::vector<Geom*> Geometries;
	std::vector<Geom*> PhysicializedGeometries;
	InputHandler* input;
	
	Lazik* lazik;
	//vector<Lazik*> laziki;
	//Fabula* fabula;
	Camera* camera;
	Map* map;
	ObjFile* ground;
	int particles = 0;
private:
	void RenderParticle(Particle particle);
	void RenderAllObjects();
	void RecursivelyRenderGeometries(Geom* geom, Entity* parent);
	void RecursivelyUpdateGeometries(Geom * geom, float frametime);

};
