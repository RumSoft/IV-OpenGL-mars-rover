#include "MyScene.h"
#include <Windows.h>
#include "Grid.h"
#include "Lazik.h"
#include "Background.h"
#include "ObjFile.h"
#include "Camera.h"
#include <ctime>




MyScene::MyScene()
{
	TwInit(TW_OPENGL, NULL);
	bar = TwNewBar("OGLDEV");
	TwWindowSize(1280, 720);
	
	input = InputHandler::GetInstance();
	this->Geometries.push_back(new Background());
	this->Geometries.push_back(new Grid(500, 50));
	//this->Geometries.push_back(new Axes());
	const auto lazik = new Lazik();
	this->Geometries.push_back(lazik);
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
	TwAddVarRO(bar, "Kat skretu", TW_TYPE_FLOAT, &lazik->angle, "Kat skretu kol");
	TwAddVarRO(bar, "Predkosc", TW_TYPE_FLOAT, &lazik->speedAcc, "Aktualna predkosc lazika");
	TwAddVarRO(bar, "V1", TW_TYPE_FLOAT, &lazik->VelocityL, "v1");
	TwAddVarRO(bar, "V2", TW_TYPE_FLOAT, &lazik->VelocityR, "v2");
	TwAddVarRO(bar, "R", TW_TYPE_FLOAT, &lazik->TurnRadius, "R");

	TwAddSeparator(bar, "rot", "rot");
	TwAddVarRO(bar, "rotX", TW_TYPE_FLOAT, &lazik->Rotation.X, "Rotx");
	TwAddVarRO(bar, "rotY", TW_TYPE_FLOAT, &lazik->Rotation.Y, "Roty");
	TwAddVarRO(bar, "rotZ", TW_TYPE_FLOAT, &lazik->Rotation.Z, "Rotz");
	TwAddVarRO(bar, "rotW", TW_TYPE_FLOAT, &lazik->Rotation.W, "Rotw");

	TwAddSeparator(bar, "ang", "speed");
	TwAddVarRO(bar, "ang1", TW_TYPE_FLOAT, &lazik->LWheelAngle, "ang1");
	TwAddVarRO(bar, "ang2", TW_TYPE_FLOAT, &lazik->RWheelAngle, "ang2");



	int kolory[] = { 0x99857a, 0xc67b5c, 0xe27b58, 0xff9d6f, 0x663926, 0x8e6a5a};
	srand(time(NULL));

	//this->Geometries.push_back((new ObjFile("objects", "MarsGround", GRAY))
	//		->WithScale(120)
	//		->WithPosition(Vec3(0,0,-100))
	//	->WithRotation(Quat::FromAngleAxis(D2R(90), Vec3(1,0,0))));

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
