#pragma once
#include <string>
#include <fl/Engine.h>

using namespace std;

struct FuzzyOutput
{
	float Vl, Vr;
};
struct FuzzyInput
{
	float L, F, R;
};
class FuzzyLogic
{
public:
	fl::Engine* engine;
	string state = "";
	FuzzyLogic();
	~FuzzyLogic();

	FuzzyOutput Process(FuzzyInput input);
	
};



