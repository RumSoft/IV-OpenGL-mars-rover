#include "MyScene.h"
#include <Windows.h>
#include "Grid.h"
#include "Lazik.h"
#include "Background.h"
#include "ObjFile.h"
#include <ctime>
#include "Map.h"
#include "Meteor.h"
#include "Camera.h"

#define smaller(a, b) if (b < a) a = b;
#define bigger(a, b) if (b > a) a = b;

void MyScene::InitUI()
{
	TwInit(TW_OPENGL, nullptr);
	bar = TwNewBar("bar");
	
	TwWindowSize(1280, 720);
	
	TwDefine(" bar position='20 400' "); // resize bar

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
	TwAddVarRO(bar, "Paliwko", TW_TYPE_FLOAT, &lazik->Fuel->_currentValue, "precision=1");

	TwAddSeparator(bar, "particles:", "particles:");
	TwAddVarRO(bar, "particles", TW_TYPE_INT32, &particles, "particles");


	bar2 = TwNewBar("bar2");


	TwDefine(" bar2 size='400 240' "); // resize bar
	TwDefine(" bar2 valueswidth=200 ");

	TwDefine(" GLOBAL contained=true ");


	TwAddSeparator(bar2, "particles:", "particles:");
	TwAddVarRO(bar2, "Paliwo Rakiety", TW_TYPE_STDSTRING, &fabula->RocketFuel, "");
	TwAddVarRO(bar2, "Bateria Lazika", TW_TYPE_STDSTRING, &lazik->BatteryLevel, "");

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
		this->Geometries.push_back((new ObjFile("objects", "marsrock", 0.7, 15))
		                           ->WithScale(Vec3(
			                           rand() % 20 + 30,
			                           rand() % 20 + 30,
			                           rand() % 20 + 30))
		                           ->WithPosition(k)
		                           ->WithRotation(Quat::FromEuler(
			                           rand() % 100 / 100.f,
			                           rand() % 100 / 100.f,
			                           rand() % 100 / 100.f)));

	this->Geometries.push_back((new ObjFile("objects", "marsrock", 0.6))
	                           ->WithScale(100)
	                           ->WithPosition(Vec3(500, 500, -50))
	);
	this->Geometries.push_back((new ObjFile("objects", "marsrock", true, 0.6))
	                           ->WithScale(108)
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
	camera = new Camera(lazik);
	this->Geometries.push_back(camera);
	this->Geometries.push_back(lazik);
	map = new Map(this);
	this->Geometries.push_back(map->WithPosition(Vec3::Zero()));
	
	fabula = new Fabula(this);
	this->Geometries.push_back(fabula);

	auto par = new ParticleGenerator(this, Particles::Ambient(), this->lazik, ZERO);
	par->PositionRandom = FLAT * 2000 + UP * 500;
	par->VelocityRandom = ONE * 100;
	this->Geometries.push_back(par);

	for (auto geom : Geometries)
	{
		if (geom != nullptr ) {
			if (geom->proxy != nullptr) {
				PhysicializedGeometries.push_back(geom);
				geom->Origin.Z = map->GetHeight(geom->Origin) + geom->proxy->heightOffset; // align to ground
			}
			for (auto geomChildren : geom->Children)
				if (geomChildren != nullptr && geomChildren->proxy != nullptr) {
					PhysicializedGeometries.push_back(geomChildren);
					geomChildren->Origin.Z = map->GetHeight(geomChildren->Origin) + geomChildren->proxy->heightOffset; // align to ground

				}
		}

	
	}

	InitUI();
}

MyScene::~MyScene() = default;



void MyScene::Update(float frametime)
{
	TwRefreshBar(bar);
	TwRefreshBar(bar2);
	particles = Particles.size();


	
	if(input->IsPressed('V'))
	{
		this->Geometries.push_back(new Meteor(this, lazik->Origin));
	}
}
