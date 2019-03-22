#pragma once
#include "InputHandler.h"

class IScene {
public:
	virtual ~IScene() = default;
	virtual void RenderScene() = 0;
};

class MyScene : public IScene
{
public:
	MyScene();
	~MyScene();

	int yRot = 0;
	int xRot = 0;
	
	// Inherited via IScene
	void RenderScene() override;

	InputHandler* input;
};

