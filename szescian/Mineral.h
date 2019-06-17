#pragma once
#include "Geom.h"
#include "IScene.h"
#include "ObjFile.h"

class Mineral : public ObjFile
{
	IScene* _scene;
public:
	Mineral(IScene* scene)
		: ObjFile("objects", "mineral", 1)
	{
		_scene = scene;
		this->Scale = 17;
		//this->Shapes.push_back(new Face(ZERO, UP * 50, FORWARD * 100, FORWARD * 100 + UP * 10)
		/*_scene = scene;
		auto obj = new ObjFile("objects", "mineral", 1);
		this->proxy = obj->proxy;
		obj->Origin = this->Origin;
		proxy->Origin = this->Origin;
		this->Children.push_back(obj->WithScale(17));*/

	}
	bool IsPickedUp = false;

	void OnPickUp()
	{
		IsPickedUp = true;
		this->proxy->Enabled = false;
	}
	const int r = 30;
	void Update(float frametime) override
	{
		const auto magnetPos = _scene->lazik->Origin + UP * 30 + _scene->lazik->Rotation * FORWARD * 80;

		if (!IsPickedUp) {
			if (_scene->input->IsDown(VK_SPACE)) {
				const auto diff = magnetPos - this->Origin;
				const auto dist = Vec3::Magnitude(diff);
				if (dist < r)
					OnPickUp();
			}
		}

		if (IsPickedUp)
		{
			if (!_scene->input->IsDown(VK_SPACE))
				OnDrop();

			this->Rotation = _scene->lazik->Rotation;
				this->Origin = magnetPos;
		}

	}

	void OnDrop()
	{
		IsPickedUp = false;
		Origin.Z = _scene->map->GetHeight(Origin) + 10;
		this->proxy->Enabled = true;
	}

	void PostRender() override
	{
		glLineWidth(5);

		if(IsPickedUp)
		{
			glColor4fv(BLUE.GL());
			glBegin(GL_LINE_LOOP);
			glVertex3f(
				this->Origin.X + 21,
				this->Origin.Y + 21,
				this->Origin.Z); 
			glVertex3f(			 
				this->Origin.X - 21,
				this->Origin.Y + 21,
				this->Origin.Z); 
			glVertex3f(			 
				this->Origin.X - 21,
				this->Origin.Y - 21,
				this->Origin.Z); 
			glVertex3f(			 
				this->Origin.X + 21,
				this->Origin.Y - 21,
				this->Origin.Z + 10);
			glEnd();
		}




		int steps = 50;
		float f = 2* M_PI / steps;
		glColor4fv(BLUE.GL());
		glBegin(GL_LINE_LOOP);

		for (int i = 0; i <= steps; i++)
			glVertex3f(
				this->Origin.X + r * sin(f * i),
				this->Origin.Y + r * cos(f * i),
				this->Origin.Z + 10);
		glEnd();


		
		glLineWidth(1);
	}
};
