#include "MyScene.h"
#include <Windows.h>
#include <gl/GL.h>
#include "M33.h"
#include "Grid.h"
#include "Axes.h"
#include "Lazik.h"
#include "Background.h"


MyScene::MyScene()
{
	input = InputHandler::GetInstance();
	this->Geometries.push_back(new Background());
	this->Geometries.push_back(new Grid());
	this->Geometries.push_back(new Axes());
	this->Geometries.push_back(new Lazik());
}

MyScene::~MyScene() = default;

void MyScene::Update()
{
	if (input->IsDown('W'))
		Rotation.X = (int(Rotation.X) + 5) % 360;
	if (input->IsDown('S'))
		Rotation.X = (360 + int(Rotation.X) - 5) % 360;

	if (input->IsDown('A'))
		Rotation.Z = (int(Rotation.Z) + 5) % 360;
	if (input->IsDown('D'))
		Rotation.Z = (360 + int(Rotation.Z) - 5) % 360;

	if (input->IsDown('Q'))
		Rotation.Y = (int(Rotation.Y) + 5) % 360;
	if (input->IsDown('E'))
		Rotation.Y = (360 + int(Rotation.Y) - 5) % 360;

	if (input->IsDown(VK_UP))
		Geometries[3]->Origin += Vec3(0, 5, 0);
	if (input->IsDown(VK_DOWN))
		Geometries[3]->Origin -= Vec3(0, 4, 0);
}
