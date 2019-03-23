#include "MyScene.h"
#include <Windows.h>
#include <gl/GL.h>
#include "M33.h"
#include "Grid.h"
#include "Axes.h"
#include "Camera.h"


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

	this->Geometries.push_back(new Camera());
	this->Geometries.push_back(new Grid());
	this->Geometries.push_back(new Axes());
}

MyScene::~MyScene() = default;

void MyScene::Update()
{

}
