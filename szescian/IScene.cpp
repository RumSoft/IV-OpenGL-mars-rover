#include "IScene.h"
#include <gl/gl.h>

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
	}
	return GL_LINE_STRIP;
}

void IScene::Render()
{
	for (auto geom : Geometries)
	{
		for (auto shape : geom->Shapes)
		{
			geom->PreRender();
			shape->PreRender();
			glBegin(TypeToGlMode(shape->Type));
			glColor4fv(shape->Color.GL());
			for (const auto point : shape->Points) {
				const auto o = shape->Origin + geom->Origin;
				const auto p = Vec3::Scale(Vec3::Scale(point, shape->Scale), geom->Scale);
				const auto p2 = geom->Rotation * shape->Rotation * (p + o);
				glVertex3f(p2.X, p2.Y, p2.Z);
			}
			glEnd();
			shape->PostRender();
			geom->PostRender();
		}
	}

}

void IScene::RenderGeometries()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(Rotation.X, 1.0f, 0.0f, 0.0f);
	glRotatef(Rotation.Y, 0.0f, 1.0f, 0.0f);
	glRotatef(Rotation.Z, 0.0f, 0.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GLU_FILL);
	Render();

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glFlush();
}

void IScene::UpdateChildren()
{
	for (auto geom : Geometries)
	{
		geom->Update();
		for (auto shape : geom->Shapes)
			shape->Update();
	}
}
