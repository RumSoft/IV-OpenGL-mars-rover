#pragma once
#include "Geom.h"

class Magnet : public Geom
{
public:
	Magnet()
	{
		auto shape = new Shape(TriangleStrip, RED);
		shape->AddPoint(Vec3(1, 0, 1), -BACKWARD);
		shape->AddPoint(Vec3(0, 0, 1), -BACKWARD);
		shape->AddPoint(Vec3(1, 0, 2), -BACKWARD);
		shape->AddPoint(Vec3(0, 0, 2.5), -BACKWARD);
		shape->AddPoint(Vec3(1.25, 0, 2.75), -BACKWARD);
		shape->AddPoint(Vec3(1, 0, 3.5), -BACKWARD);
		shape->AddPoint(Vec3(2, 0, 3), -BACKWARD);
		shape->AddPoint(Vec3(2, 0, 4), -BACKWARD);
		shape->AddPoint(Vec3(2.75, 0, 2.75), -BACKWARD);
		shape->AddPoint(Vec3(3, 0, 3.5), -BACKWARD);
		shape->AddPoint(Vec3(3, 0, 2), -BACKWARD);
		shape->AddPoint(Vec3(4, 0, 2.5), -BACKWARD);
		shape->AddPoint(Vec3(3, 0, 1), -BACKWARD);
		shape->AddPoint(Vec3(4, 0, 1), -BACKWARD);

		float h = 0.5;
		auto shape2 = new Shape(TriangleStrip, RED);
		shape2->AddPoint(Vec3(1, h, 1), FORWARD);
		shape2->AddPoint(Vec3(0, h, 1), FORWARD);
		shape2->AddPoint(Vec3(1, h, 2), FORWARD);
		shape2->AddPoint(Vec3(0, h, 2.5), FORWARD);
		shape2->AddPoint(Vec3(1.25, h, 2.75), FORWARD);
		shape2->AddPoint(Vec3(1, h, 3.5), FORWARD);
		shape2->AddPoint(Vec3(2, h, 3), FORWARD);
		shape2->AddPoint(Vec3(2, h, 4), FORWARD);
		shape2->AddPoint(Vec3(2.75, h, 2.75), FORWARD);
		shape2->AddPoint(Vec3(3, h, 3.5), FORWARD);
		shape2->AddPoint(Vec3(3, h, 2), FORWARD);
		shape2->AddPoint(Vec3(4, h, 2.5), FORWARD);
		shape2->AddPoint(Vec3(3, h, 1), FORWARD);
		shape2->AddPoint(Vec3(4, h, 1), FORWARD);

		auto shape3 = new Shape(TriangleStrip, RED);
		shape3->AddPoint(Vec3(1, 0, 1), RIGHT);
		shape3->AddPoint(Vec3(1, h, 1), RIGHT);
		shape3->AddPoint(Vec3(1, 0, 2), RIGHT);
		shape3->AddPoint(Vec3(1, h, 2), RIGHT);
		shape3->AddPoint(Vec3(1.25, 0, 2.75), DOWN);
		shape3->AddPoint(Vec3(1.25, h, 2.75), DOWN);
		shape3->AddPoint(Vec3(2, 0, 3), DOWN);
		shape3->AddPoint(Vec3(2, h, 3), DOWN);
		shape3->AddPoint(Vec3(2.75, 0, 2.75), DOWN);
		shape3->AddPoint(Vec3(2.75, h, 2.75), DOWN);
		shape3->AddPoint(Vec3(3, 0, 2), LEFT);
		shape3->AddPoint(Vec3(3, h, 2), LEFT);
		shape3->AddPoint(Vec3(3, 0, 1), LEFT);
		shape3->AddPoint(Vec3(3, h, 1), LEFT);
		
		auto shape4 = new Shape(TriangleStrip, RED);		
		shape4->AddPoint(Vec3(0, 0, 1), -LEFT);
		shape4->AddPoint(Vec3(0, h, 1), -LEFT);
		shape4->AddPoint(Vec3(0, 0, 2.5), -LEFT);
		shape4->AddPoint(Vec3(0, h, 2.5), -LEFT);
		shape4->AddPoint(Vec3(1, 0, 3.5), -UP);
		shape4->AddPoint(Vec3(1, h, 3.5), -UP);
		shape4->AddPoint(Vec3(2, 0, 4), -UP);
		shape4->AddPoint(Vec3(2, h, 4), -UP);
		shape4->AddPoint(Vec3(3, 0, 3.5), -UP);
		shape4->AddPoint(Vec3(3, h, 3.5), -UP);		
		shape4->AddPoint(Vec3(4, 0, 2.5), -RIGHT);
		shape4->AddPoint(Vec3(4, h, 2.5), -RIGHT);
		shape4->AddPoint(Vec3(4, 0, 1), -RIGHT);
		shape4->AddPoint(Vec3(4, h, 1), -RIGHT);

		this->Shapes.push_back(shape);
		this->Shapes.push_back(shape2);
		this->Shapes.push_back(shape3);
		this->Shapes.push_back(shape4);
		this->Shapes.push_back(new Face(Vec3(0.5, 0, 0), Vec3(0,0,1), Vec3(1.5, 0, 0), Vec3(1, 0, 1), LIGHTGRAY, true));
		this->Shapes.push_back(new Face(Vec3(0.5, h, 0), Vec3(0,h,1), Vec3(1.5, h, 0), Vec3(1, h, 1), LIGHTGRAY));
	}

	void Update(float frametime) override
	{
		
	}
};
