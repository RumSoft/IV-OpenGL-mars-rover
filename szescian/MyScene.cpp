#include "MyScene.h"
#include <Windows.h>
#include "Grid.h"
#include "Axes.h"
#include "Lazik.h"
#include "Background.h"
#include "ObjFile.h"
#include "Camera.h"


MyScene::MyScene()
{
	input = InputHandler::GetInstance();
	this->Geometries.push_back(new Background());
	this->Geometries.push_back(new Grid(500, 50));
	this->Geometries.push_back(new Axes());
	const auto lazik = new Lazik();
	this->Geometries.push_back(lazik);
	this->Geometries.push_back(new Camera(lazik));
	this->Geometries.push_back(new ObjFile());
}

MyScene::~MyScene() = default;

void MyScene::Update()
{

}
