#include "MyScene.h"
#include <Windows.h>
#include <gl/GL.h>
#include "M33.h"
#include "Grid.h"


MyScene::MyScene()
{
	input = InputHandler::GetInstance();
	int a = 50;
	auto s1 = Shape();
	s1.Type = TriangleStrip;
	s1.Points.emplace_back(0, 0, 0);
	s1.Points.emplace_back(0, a, 0);
	s1.Points.emplace_back(a, 0, 0);
	s1.Points.emplace_back(a, a, 0);
	s1.Points.emplace_back(a, 0, a);
	s1.Points.emplace_back(a, a, a);
	s1.Rotation = Quat::FromAngleAxis(Deg2Rad(30), Vec3(0, 0, 1));
	auto g1 = new Geom();
	g1->Shapes.push_back(s1);
	this->Geometries.push_back(g1);

	this->Geometries.push_back(new Grid());
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
}
