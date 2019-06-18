#include "Proxy.h"
#include "ObjFile.h"
#include "Lazik.h"
#include "Map.h"

void Proxy::Update(float frametime)
{
	if (!isColliding && !LastCollided)
		isColliding = false;

	Acceleration *= 0.7;
	_acc *= 0.7;
	_acc += Acceleration * pow(atan(Vec3::SqrMagnitude(Acceleration)), 2) * 5;

	if (!isColliding)
	{
		Velocity += _acc * MaxSpeed * 0.4;
		Velocity = Vec3::Scale(Velocity, 1 - 10 / Mass);
		parent->Origin += Velocity;
	}

	isColliding = false;
	isColliding2 = LastCollided;
	LastCollided = isColliding;
	LastPos = parent->Origin;
	LastRot = parent->Rotation;
}

void Proxy::DrawProxy()
{
	float a = 0.5;
	auto pos = Origin;
	auto ppos = parent->Origin;
	auto rot = Rotation;
	auto prot = parent->Rotation;
	auto sca = Scale;
	auto psca = parent->Scale;

	Vec3 pro[] = {

		Vec3(-a, a, -a),
		Vec3(-a, -a, -a),
		Vec3(a, a, -a),
		Vec3(a, -a, -a),
		Vec3(a, a, a),
		Vec3(a, -a, a),
		Vec3(-a, a, a),
		Vec3(-a, -a, a),
		Vec3(-a, a, -a),
		Vec3(-a, -a, -a),
	};
	glLineWidth(5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUAD_STRIP);
	glColor4fv(isColliding ? debugColor.GL() : debugColor2.GL());
	for (const auto p : pro)
	{
		const auto pt = prot * (rot * Vec3::Scale(Vec3::Scale(p, sca), psca) + pos) + ppos;
		glVertex3f(pt.X, pt.Y, pt.Z);
	}
	glEnd();
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Proxy::OnCollision(Proxy* obj)
{
	//p1 = p2
	//mv = mv
	//v(t) = a'(t)
	//mv = m * da 

	// this - lazik
	// obj - kamień


	auto lazik = (Lazik*)this->parent;
	//
	auto dir = obj->parent->Origin - this->parent->Origin;
	dir = Vec3::Normalized(dir);
	isColliding = true;
	//obj->Acceleration += dir / obj->Mass;
	////this->Velocity *= 0.95;
	////this->Acceleration *= 0.95;
	obj->parent->Origin += dir;
	////lazik->Velocity
	obj->parent->Origin.Z = lazik->_scene->map->GetHeight(obj->parent->Origin) + obj->heightOffset;
}
