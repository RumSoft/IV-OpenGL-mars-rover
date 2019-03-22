#include "Scene.h"
#include <Windows.h>
#include <gl/GL.h>

auto TypeToGlMode(ShapeType type)
{
	switch (type)
	{
	case Line:
		return GL_LINE_STRIP;
	case Triangle:
		return GL_TRIANGLES;
	case TriangleStrip:
		return GL_TRIANGLE_STRIP;
	case TriangleFan:
		return GL_TRIANGLE_FAN;
	}
	return GL_LINE_STRIP;
}

void IScene::RenderGeometries()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(Orientation.X, 1.0f, 0.0f, 0.0f);
	glRotatef(Orientation.Y, 0.0f, 1.0f, 0.0f);
	glRotatef(Orientation.Z, 0.0f, 0.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (auto g : Geometries)
	{
		for (auto s : g->Shapes)
		{
			glBegin(TypeToGlMode(s.Type));
			for (const auto p : s.Points)
				glVertex3f(p.X, p.Y, p.Z);
			glEnd();
		}
	}

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glFlush();
}

MyScene::MyScene()
{
	input = InputHandler::GetInstance();
	int a = 50;
	auto s1 = Shape();
	s1.Type = TriangleStrip;
	s1.Points.emplace_back(0, 0, 0);
	s1.Points.emplace_back(0, a, 0);
	s1.Points.emplace_back(a, a, 0);
	s1.Points.emplace_back(a, 0, 0);
	auto g1 = new Geom();
	g1->Shapes.push_back(s1);
	this->Geometries.push_back(g1);
}


MyScene::~MyScene()
{
}



void MyScene::Update()
{
	if (input->IsDown('W'))
		Orientation.X = ((int)Orientation.X + 5) % 360;
	if (input->IsDown('S'))
		Orientation.X = (360 + (int)Orientation.X - 5) % 360;

	if (input->IsDown('A'))
		Orientation.Z = ((int)Orientation.Z + 5) % 360;
	if (input->IsDown('D'))
		Orientation.Z = (360 + (int)Orientation.Z - 5) % 360;

	if (input->IsDown('Q'))
		Orientation.Y = ((int)Orientation.Y + 5) % 360;
	if (input->IsDown('E'))
		Orientation.Y = (360 + (int)Orientation.Y - 5) % 360;


}
