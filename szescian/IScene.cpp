#include "IScene.h"
#include <gl/gl.h>
#include <string>
#include "M33.h"
#include "../AntTweakBar.h"
#include "ObjFile.h"
#include "Camera.h"
#include <cmath>
#include "CollisionDetector.h"

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

void IScene::Update(float frametime)
{
}


void IScene::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glPolygonMode(GL_FRONT_FACE, GLU_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	RenderAllObjects();
	TwDraw();
	UpdatePhysics();

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
}


void IScene::UpdateAllGeometries(float frametime)
{
	//for (auto geom : this->Geometries)
	//	RecursivelyUpdateGeometries(geom, frametime);

	auto it = this->Geometries.begin();
	while (it != this->Geometries.end())
	{
		if ((*it)->Delete)
		{
			delete* it;
			this->Geometries.erase(it);
		}
		else
			RecursivelyUpdateGeometries(*it, frametime);
		if (it != this->Geometries.end())
			++it;
	}

	auto it2 = Particles.begin();
	while (it2 != Particles.end()) {
		it2->Life += frametime;
		if (it2->Life > it2->Lifetime) 
			it2 = Particles.erase(it2);	
		else
			it2->Update(frametime);
		if(it2 != Particles.end())
			++it2;
	}
}

void IScene::UpdatePhysics()
{
	const auto a = lazik;
	const auto apos = a->proxy->Origin + a->Origin;
	const auto asize1 = a->proxy->Scale;
	const auto asize2 = a->Scale;
	const auto asize = Vec3::Scale(asize1, asize2);
	const auto arot = a->Rotation;

	for (auto geom : PhysicializedGeometries)
	{
		if (!geom->proxy->Enabled)
			continue;

		const auto b = geom;
		const auto bpos = b->proxy->Origin + b->Origin;
		const auto bsize1 = b->proxy->Scale;
		const auto bsize2 = b->Scale;
		const auto bsize = Vec3::Scale(bsize1, bsize2);
		const auto brot = b->Rotation;

		auto distSqr = Vec3::SqrMagnitude(bpos - apos);
		if (distSqr > 200000) continue;
		//method1 : simple cubes
		//if (abs((apos - bpos).X) < (asize + bsize).X)
		//	if (abs((apos - bpos).Y) < (asize + bsize).Y)
		//		if (abs((apos - bpos).Z) < (asize + bsize).Z)
		//			return Lazikk->proxy->OnCollision(geom);

		//method 2: if any of points inside another
		//https://gamedev.stackexchange.com/questions/44500/how-many-and-which-axes-to-use-for-3d-obb-collision-with-sat
		Vec3 apts[] = {
			Vec3(-asize.X, -asize.Y, asize.Z) / 2,
			Vec3(asize.X, -asize.Y, asize.Z) / 2,
			Vec3(-asize.X, asize.Y, asize.Z) / 2,
			Vec3(asize.X, asize.Y, asize.Z) / 2,
			Vec3(-asize.X, -asize.Y, -asize.Z) / 2,
			Vec3(asize.X, -asize.Y, -asize.Z) / 2,
			Vec3(-asize.X, asize.Y, -asize.Z) / 2,
			Vec3(asize.X, asize.Y, -asize.Z) / 2
		};

		Vec3 bpts[] = {
			Vec3(-bsize.X, -bsize.Y, bsize.Z) / 2,
			Vec3(bsize.X, -bsize.Y, bsize.Z) / 2,
			Vec3(-bsize.X, bsize.Y, bsize.Z) / 2,
			Vec3(bsize.X, bsize.Y, bsize.Z) / 2,
			Vec3(-bsize.X, -bsize.Y, -bsize.Z) / 2,
			Vec3(bsize.X, -bsize.Y, -bsize.Z) / 2,
			Vec3(-bsize.X, bsize.Y, -bsize.Z) / 2,
			Vec3(bsize.X, bsize.Y, -bsize.Z) / 2
		};

		Vec3 a_pts[8];
		Vec3 b_pts[8];

		for (int i = 0; i < 8; i++)
			a_pts[i] = arot * apts[i] + apos;

		for (int i = 0; i < 8; i++)
			b_pts[i] = brot * bpts[i] + bpos;

		if (CollisionDetectorHelper::Intersects(a_pts, b_pts, arot, brot))
			return lazik->proxy->OnCollision(geom->proxy);
	}
}

void IScene::RecursivelyUpdateGeometries(Geom * geom, float frametime)
{
	geom->Update(frametime);
	for (auto shape : geom->Shapes)
		shape->Update(frametime);

	auto it = geom->Children.begin();
	while(it != geom->Children.end())
	{
		if((*it)->Delete)
		{
			delete* it;
			geom->Children.erase(it);
		}
		else
			RecursivelyUpdateGeometries(*it, frametime);
		if (it != geom->Children.end())
			++it;
	}

}

float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

void IScene::RenderParticle(Particle particle)
{
	if(particle.Additive)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	const auto c1 = particle.StartColor.rgba;
	const auto c2 = particle.EndColor.rgba;
	const auto t = particle.Life / particle.Lifetime;
	ColorF color = ColorF(
		lerp(c1[0], c2[0], t),
		lerp(c1[1], c2[1], t),
		lerp(c1[2], c2[2], t),
		lerp(c1[3], c2[3], t));
	const auto size = lerp(particle.StartSize, particle.EndSize, t);
	glPointSize(size);

	glBegin(GL_POINTS);
	glColor4f(TAB4(color.rgba));
	glVertex3f(XYZ(particle.Position));
	glEnd();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void IScene::RenderAllObjects()
{
	for (auto geom : Geometries)
		RecursivelyRenderGeometries(geom, new Entity());
	for (const auto particle : Particles)
		RenderParticle(particle);
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
			const auto nn = Vec3::Normalized(n);
			glNormal3f(XYZ(nn));
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
