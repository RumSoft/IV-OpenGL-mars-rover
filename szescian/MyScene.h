#pragma once
#include "IScene.h"
#include "../AntTweakBar.h"
#include "Map.h"
#include "Fabula.h"

class MyScene : public IScene
{
public:
	
	TwBar* bar;
	TwBar* bar2;
	Fabula* fab;
	void InitUI();
	void InitRocks();
	void InitGround();
	MyScene();
	~MyScene();
	void Update(float frametime) override;
};

