#pragma once
#include <string>
#include <fl/Engine.h>

using namespace std;



class LightFollowerLogic
{
public:
	struct Output
	{
		float Vl, Vr;
	};
	struct Input
	{
		float L, F, R;
	};

	fl::Engine* engine;
	string state = "";
	LightFollowerLogic();
	~LightFollowerLogic();

	Output ProcessLightFollower(Input input);

	
};



