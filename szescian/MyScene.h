#pragma once
#include "IScene.h"

class MyScene : public IScene
{
public:
	MyScene();
	~MyScene();
	
	void Update() override;
};

