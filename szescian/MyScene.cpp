#include "MyScene.h"
#include <Windows.h>
#include "Grid.h"
#include "Lazik.h"
#include "Background.h"
#include "ObjFile.h"
#include "Camera.h"
#include <ctime>
#include "Light.h"


MyScene::MyScene()
{
	TwInit(TW_OPENGL, NULL);
	bar = TwNewBar("OGLDEV"); 
	bar2 = TwNewBar("fuzzy");
	TwWindowSize(1280, 720);
	
	input = InputHandler::GetInstance();
	this->Geometries.push_back(new Background());
	this->Geometries.push_back(new Grid(500, 50));
	//this->Geometries.push_back(new Axes());
	const auto light = new Light();
	const auto lazik = new Lazik(light);
	this->Geometries.push_back(lazik);
	this->Geometries.push_back(light);
	this->Geometries.push_back(new Camera(lazik));

	TwAddButton(bar, "Lazik", NULL, NULL, "");
	TwAddVarRO(bar, "V", TW_TYPE_FLOAT, &lazik->V, "V");
	TwAddVarRO(bar, "V1", TW_TYPE_FLOAT, &lazik->Vl, "v1");
	TwAddVarRO(bar, "V2", TW_TYPE_FLOAT, &lazik->Vr, "v2");
	TwAddVarRO(bar, "R", TW_TYPE_FLOAT, &lazik->R, "R");

	TwAddSeparator(bar, "ang", "ang");
	TwAddVarRO(bar, "angl", TW_TYPE_FLOAT, &lazik->angle, "angl");

	TwAddSeparator(bar, "sensors", "sensors");
	TwAddVarRO(bar, "senL", TW_TYPE_FLOAT, &lazik->sensL, "senL");
	TwAddVarRO(bar, "senM", TW_TYPE_FLOAT, &lazik->sensM, "senM");
	TwAddVarRO(bar, "senR", TW_TYPE_FLOAT, &lazik->sensR, "senR");
	TwAddVarRO(bar, "sensAngl", TW_TYPE_FLOAT, &lazik->sensAngl, "sensAngl");
	
	TwAddSeparator(bar2, "fuz", "fuz");
	TwAddVarRO(bar2, "state", TW_TYPE_STDSTRING, &lazik->lightFollowerFuzzy->state, "state");
	TwAddVarRO(bar2, "vl", TW_TYPE_FLOAT, &lazik->lightFollowerOutput.Vl, "vl");
	TwAddVarRO(bar2, "vr", TW_TYPE_FLOAT, &lazik->lightFollowerOutput.Vr, "vr");
	int bar2pos[] = { 10,300 };
	int bar2size[] = { 300,100 };

	TwSetParam(bar2, NULL, "position", TW_PARAM_INT32, 2, bar2pos);
	TwSetParam(bar2, NULL, "size", TW_PARAM_INT32, 2, bar2size);
	TwSetParam(bar2, NULL, "valueswidth", TW_PARAM_CSTRING, 1, "fit");

	srand(time(NULL));

}

MyScene::~MyScene() = default;

void MyScene::Update(float frametime)
{
	TwRefreshBar(bar);
	TwRefreshBar(bar2);
}
