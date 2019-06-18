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
		this->proxy->Mass = 10;
		this->proxy->groundOffset = 18;

	}
	bool IsPickedUp = false;

	void OnPickUp()
	{
		IsPickedUp = true;
		//this->proxy->Enabled = false;
	}
	const float r = 30;
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
			{
				OnDrop();
				return;
			}

			this->Rotation = _scene->lazik->Rotation;
				this->Origin = magnetPos;
		}


	}

	void OnDrop()
	{
		IsPickedUp = false;
		this->Origin.Z = _scene->map->GetHeight(Origin)  + proxy->groundOffset;
	}
};
