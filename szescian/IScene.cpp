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

void IScene::RecursivelyUpdateGeometries(Geom * geom)
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

void IScene::RecursivelyRenderGeometries(Geom * geom, Entity * parent)
{

	auto pos = new Entity();
	for (auto shape : geom->Shapes)
	{

		geom->PreRender();
		shape->PreRender();
		
		if (shape->texture > 0) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, shape->texture);
		}
		
		glBegin(TypeToGlMode(shape->Type));
		glColor4fv(shape->Color.GL());
		
		for (const auto v : shape->Vertices)
		{
			const auto p = parent->Rotation * Vec3::Scale(
				geom->Rotation * Vec3::Scale(
					shape->Rotation * Vec3::Scale(v.Position, shape->Scale) + shape->Origin,
					geom->Scale) + geom->Origin,
				parent->Scale) + parent->Origin;

			const auto n = parent->Rotation * geom->Rotation * shape->Rotation * v.Normal;

			glNormal3f(XYZ(Vec3::Normalized(n)));
			glTexCoord2d(XY(v.TextureCoordinate));
			glVertex3f(XYZ(p));
		}

		glEnd();
		glDisable(GL_TEXTURE_2D);
		shape->PostRender();
		geom->PostRender();
	}


	pos->Rotation = geom->Rotation * parent->Rotation;
	pos->Origin = parent->Rotation * geom->Origin + parent->Origin;
	pos->Scale = Vec3::Scale(Vec3::Scale(Vec3::One(), parent->Scale), geom->Scale);

	for (auto child : geom->Children)
		RecursivelyRenderGeometries(child, pos);
}
