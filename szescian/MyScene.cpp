#include "MyScene.h"
#include <Windows.h>
#include <gl/GL.h>
#include "M33.h"
#include "Grid.h"
#include "Axes.h"
#include "Lazik.h"
#include "Background.h"
#include "ObjFile.h"


MyScene::MyScene()
{
	input = InputHandler::GetInstance();
	this->Geometries.push_back(new Background());
	this->Geometries.push_back(new Grid(500, 50));
	this->Geometries.push_back(new Axes());
	this->Geometries.push_back(new Lazik());
	this->Geometries.push_back(new ObjFile());
}

MyScene::~MyScene() = default;

void MyScene::Update()
{
	if (input->IsDown(VK_UP))
		Rotation.X = (int(Rotation.X) + 5) % 360;
	if (input->IsDown(VK_DOWN))
		Rotation.X = (360 + int(Rotation.X) - 5) % 360;

	if (input->IsDown(VK_LEFT))
		Rotation.Z = (int(Rotation.Z) + 5) % 360;
	if (input->IsDown(VK_RIGHT))
		Rotation.Z = (360 + int(Rotation.Z) - 5) % 360;
}
