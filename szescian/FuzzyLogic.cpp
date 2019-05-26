#include "FuzzyLogic.h"
#include "fl/Headers.h"
#include <fstream>
using namespace fl;

FuzzyLogic::FuzzyLogic()
{
	engine = fl::FisImporter().fromFile("D:\\swiatlo.fis"); 
	string status="";
	if (!engine->isReady(&status))
		state = status;
	else
		state = "ready";

	ofstream myfile;
	myfile.open("log.txt");
	myfile << status << endl;
	myfile << state << endl;
	myfile << fl::FllExporter().toString(engine) << endl;
	myfile.close();
}

FuzzyOutput FuzzyLogic::Process(FuzzyInput input)
{
	auto left = engine->getInputVariable("left");
	auto front = engine->getInputVariable("front");
	auto right = engine->getInputVariable("right");

	left->setValue(input.L);
	front->setValue(input.F);
	right->setValue(input.R);

	auto Vleft = engine->getOutputVariable("Vleft");
	auto Vright = engine->getOutputVariable("Vright");

	engine->process();

	FuzzyOutput output{};
	output.Vl = Vleft->getValue();
	output.Vr = Vright->getValue();
	return output;
}


FuzzyLogic::~FuzzyLogic()
= default;
