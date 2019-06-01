#pragma once
#include <string>
#include <fl/Engine.h>

using namespace std;



class LightFollowerLogic
{
public:
	struct FuzzyOutput
	{
		float Vl, Vr;
	};
	struct FuzzyInput
	{
		float L, F, R;
	};

	fl::Engine* engine;
	string state = "";
	LightFollowerLogic();
	~LightFollowerLogic();

	FuzzyOutput ProcessSwiatlo(FuzzyInput input);

	
};



