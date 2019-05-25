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

	Vec3 kamienie[] = {
		Vec3(50, -300, -60),
		Vec3(100, 100, 0),
		Vec3(600, 600, -45),
		Vec3(-250, -550, -70),
		Vec3(1000, -500, -80),
		Vec3(1850, 300, -150),
		Vec3(1400, -900, -50),
		Vec3(550, -800, -50),
		Vec3(-100, -950, -50)
	};

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

	int kolory[] = { 0x99857a, 0xc67b5c, 0xe27b58, 0xff9d6f, 0x663926, 0x8e6a5a};
	srand(time(NULL));

	for(const auto k : kamienie)
		this->Geometries.push_back((new ObjFile("objects", "marsrock"))
			->WithScale(Vec3(
				rand() % 20 + 30, 
				rand() % 20 + 30, 
				rand() % 20 + 30))
			->WithPosition(k)
			->WithRotation(Quat::FromEuler(
				rand() % 100 / 100.f, 
				rand() % 100 / 100.f, 
				rand() % 100 / 100.f)));

	this->Geometries.push_back((new ObjFile("objects", "marsrock"))
		->WithScale(100)
		->WithPosition(Vec3(500,500,0))
	); 
	this->Geometries.push_back((new ObjFile("objects", "marsrock"))
		->WithScale(170)
		->WithPosition(Vec3(-20, -900, 0))
	);
	//this->Geometries.push_back((new ObjFile("","marsground2", kolory[rand() % 6]))
}

MyScene::~MyScene() = default;

void MyScene::Update(float frametime)
{
	TwRefreshBar(bar);
}
