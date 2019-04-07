#include "IScene.h"
#include <gl/gl.h>
#include <string>
#include "M33.h"

auto TypeToGlMode(ShapeType type)
{
	switch (type)
	{
	case Line:
		return GL_LINES;
	case LineStrip:
		return GL_LINE_STRIP;
	case Triangle:
		return GL_TRIANGLES;
	case TriangleStrip:
		return GL_TRIANGLE_STRIP;
	case TriangleFan:
		return GL_TRIANGLE_FAN;
	case Quad:
		return GL_QUADS;
	case QuadStrip:
		return GL_QUAD_STRIP;
	}
	return GL_LINE_STRIP;
}

void IScene::Update()
{
}


void IScene::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GLU_FILL);

	RenderAllObjects();

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
}

void IScene::UpdateAllGeometries()
{
	for (auto geom : this->Geometries)
		RecursivelyUpdateGeometries(geom);
}

void IScene::RecursivelyUpdateGeometries(Geom* geom)
{
	geom->Update();
	for (auto shape : geom->Shapes)
		shape->Update();
	for (auto child : geom->Children)
		RecursivelyUpdateGeometries(child);
}

void IScene::RenderAllObjects()
{
	for (auto geom : Geometries)
		RecursivelyRenderGeometries(geom, new Entity());
}

void IScene::RecursivelyRenderGeometries(Geom* geom, Entity* parent)
{
	auto pos = new Entity();
	for (auto shape : geom->Shapes)
	{
		geom->PreRender();
		shape->PreRender();
		glBegin(TypeToGlMode(shape->Type));
		glColor4fv(shape->Color.GL());
		int i = 0;
		for(auto pt : shape->Points)
		{
			const auto p =
				parent->Rotation * Vec3::Scale(
					shape->Rotation * Vec3::Scale(
						geom->Rotation * Vec3::Scale(pt, geom->Scale) + geom->Origin,
						shape->Scale) + shape->Origin,
					parent->Scale) + parent->Origin;
			glVertex3f(p.X, p.Y, p.Z);

			i++;
			if(i < shape->Normals.size())
			{
				const auto n = shape->Normals[i];
				glNormal3f(n.X, n.Y, n.Z);
			}

		}
	
		glEnd();
		shape->PostRender();
		geom->PostRender();
	}


	pos->Rotation = geom->Rotation * parent->Rotation;
	pos->Origin = parent->Rotation*geom->Origin + parent->Origin;
	pos->Scale = Vec3::Scale(Vec3::Scale(Vec3::One(), parent->Scale), geom->Scale);

	for (auto child : geom->Children)
		RecursivelyRenderGeometries(child, pos);
}
