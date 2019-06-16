#include "MyScene.h"
#include <Windows.h>
#include "Grid.h"
#include "Lazik.h"
#include "Background.h"
#include "ObjFile.h"
#include "Camera.h"
#include <ctime>
#include "Map.h"

#define smaller(a, b) if (b < a) a = b;
#define bigger(a, b) if (b > a) a = b;


void MyScene::InitUI()
{
	TwInit(TW_OPENGL, nullptr);
	bar = TwNewBar("OGLDEV");
	TwWindowSize(1280, 720);
	

	TwAddButton(bar, "Lazik", nullptr, nullptr, "");
	TwAddVarRO(bar, "Predkosc", TW_TYPE_FLOAT, &lazik->speedAcc, "Aktualna predkosc lazika");
	TwAddVarRO(bar, "V1", TW_TYPE_FLOAT, &lazik->VelocityL, "precision=1");
	TwAddVarRO(bar, "V2", TW_TYPE_FLOAT, &lazik->VelocityR, "precision=1");

	TwAddSeparator(bar, "rot", "rot");
	TwAddVarRO(bar, "rotX", TW_TYPE_FLOAT, &lazik->Rotation.X, "precision=1");
	TwAddVarRO(bar, "rotY", TW_TYPE_FLOAT, &lazik->Rotation.Y, "precision=1");
	TwAddVarRO(bar, "rotZ", TW_TYPE_FLOAT, &lazik->Rotation.Z, "precision=1");
	TwAddVarRO(bar, "rotW", TW_TYPE_FLOAT, &lazik->Rotation.W, "precision=1");

	TwAddSeparator(bar, "pos", "pos");
	TwAddVarRO(bar, "posX", TW_TYPE_FLOAT, &lazik->Origin.X, "precision=1");
	TwAddVarRO(bar, "posY", TW_TYPE_FLOAT, &lazik->Origin.Y, "precision=1");
	TwAddVarRO(bar, "posZ", TW_TYPE_FLOAT, &lazik->Origin.Z, "precision=1");

	TwAddSeparator(bar, "paliwko", "value");
	TwAddVarRO(bar, "Paliwko", TW_TYPE_FLOAT, &lazik->Fuel->_currentValue, "Paliwko");

	TwAddSeparator(bar, "particles:", "particles:");
	TwAddVarRO(bar, "particles", TW_TYPE_INT32, &particles, "particles");

}

void MyScene::InitRocks()
{
	Vec3 kamienie[] = {
		Vec3(50, -300, -60),
		Vec3(100, 100, 0),
		Vec3(600, 600, -45),
		Vec3(600, 800, -45),
		Vec3(600, 700, -45),
		Vec3(-250, -550, -70),
		Vec3(1000, -500, -80),
		Vec3(1850, 300, -150),
		Vec3(1400, -900, -50),
		Vec3(550, -800, -50),
		Vec3(-100, -950, -50),
		Vec3(-100, -950, -50),
		Vec3(-100, -850, -50),
		Vec3(-100, -750, -50),
		Vec3(-100, -650, -50)
	};
	for (const auto k : kamienie)
		this->Geometries.push_back((new ObjFile("objects", "marsrock", true))
		                           ->WithScale(Vec3(
			                           rand() % 20 + 30,
			                           rand() % 20 + 30,
			                           rand() % 20 + 30))
		                           ->WithPosition(k)
		                           ->WithRotation(Quat::FromEuler(
			                           rand() % 100 / 100.f,
			                           rand() % 100 / 100.f,
			                           rand() % 100 / 100.f)));

	this->Geometries.push_back((new ObjFile("objects", "marsrock", true))
	                           ->WithScale(100)
	                           ->WithPosition(Vec3(500, 500, 0))
	);
	this->Geometries.push_back((new ObjFile("objects", "marsrock", true))
	                           ->WithScale(170)
	                           ->WithPosition(Vec3(-20, -900, 0))
	);
}

void MyScene::InitGround()
{
	ground = new ObjFile("objects", "MarsGround", GRAY);
	this->Geometries.push_back(ground
	                           ->WithScale(200)
	                           ->WithPosition(Vec3(-1500, -1000, -100))
	                           ->WithRotation(Quat::FromAngleAxis(D2R(90), Vec3(1, 0, 0))));
}

MyScene::MyScene()
{
	InitRocks();
	InitGround();

	input = InputHandler::GetInstance();
	this->Geometries.push_back(new Background());
	lazik = new Lazik(this);
	this->Geometries.push_back(new Camera(lazik));
	this->Geometries.push_back(lazik);
	map = new Map(this);
	this->Geometries.push_back(map->WithPosition(Vec3::Zero()));

	for (auto geom : Geometries)
	{
		const auto physGeom = dynamic_cast<ObjFile*>(geom);
		if (physGeom != nullptr && physGeom->proxy != nullptr)
			PhysicializedGeometries.push_back(physGeom);
	}

	InitUI();
}

MyScene::~MyScene() = default;

void MyScene::Update(float frametime)
{
	TwRefreshBar(bar);
	particles = Particles.size();
}
