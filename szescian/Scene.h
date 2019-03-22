#pragma once
#include "InputHandler.h"
#include <vector>
#include "Geom.h"
#include "Quat.h"

class IScene : public Entity {
public:
	virtual ~IScene() = default;
	virtual void Update() = 0;

	void RenderGeometries();

	std::vector<Geom*> Geometries;
	InputHandler* input;
};

class MyScene : public IScene
{
public:
	MyScene();
	~MyScene();
	
	void Update() override;
};

