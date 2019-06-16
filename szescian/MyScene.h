#pragma once
#include "IScene.h"
#include "../AntTweakBar.h"
#include "Map.h"

class MyScene : public IScene
{
public:
	TwBar* bar;
	void InitUI();
	void InitRocks();
	void InitGround();
	MyScene();
	~MyScene();
	void Update(float frametime) override;
};

