#pragma once
#include "IScene.h"
#include "../AntTweakBar.h"

class MyScene : public IScene
{
public:
	TwBar* bar;
	TwBar* bar2;
	MyScene();
	~MyScene();

	

	void Update(float frametime) override;
};

