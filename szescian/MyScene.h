#pragma once
#include "IScene.h"
#include "../AntTweakBar.h"

class MyScene : public IScene
{
public:
	TwBar* bar;
	MyScene();
	~MyScene();
	
	void Update(float frametime) override;
};

