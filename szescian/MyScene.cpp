#include "MyScene.h"
#include <Windows.h>
#include "Grid.h"
#include "Axes.h"
#include "Lazik.h"
#include "Background.h"
#include "ObjFile.h"
#include "Camera.h"
#include <ctime>

MyScene::MyScene()
{
	input = InputHandler::GetInstance();
	this->Geometries.push_back(new Background());
	this->Geometries.push_back(new Grid(500, 50));
	this->Geometries.push_back(new Axes());
	const auto lazik = new Lazik();
	this->Geometries.push_back(lazik);
	this->Geometries.push_back(new Camera(lazik));

	Vec3 kamienie[] = {
		Vec3(50, -300, -20),
		Vec3(100, 100, 0)
	};
	int kolory[] = { 0x99857a, 0xc67b5c, 0xe27b58, 0xff9d6f, 0x663926, 0x8e6a5a};
	srand(time(NULL));

	for(const auto k : kamienie)
		this->Geometries.push_back((new ObjFile("marsrock2.obj", kolory[rand() % 6]))
			->WithScale(Vec3(
				rand() % 20 + 30, 
				rand() % 20 + 30, 
				rand() % 20 + 30))
			->WithPosition(k)
			->WithRotation(Quat::FromEuler(
				rand() % 100 / 100.f, 
				rand() % 100 / 100.f, 
				rand() % 100 / 100.f)));;

	this->Geometries.push_back((new ObjFile("marsground.obj", kolory[rand() % 6]))
		->WithScale(120)
		->WithPosition(Vec3(0,0,-100)));
}

MyScene::~MyScene() = default;

void MyScene::Update()
{

}
