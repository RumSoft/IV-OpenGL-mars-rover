#pragma once
#include "Geom.h"
#include "IScene.h"
#include "ObjFile.h"
#include "CollisionDetector.h"
#include "Fabryka.h"
#include <functional>

//class Fabula;

class Mineral : public ObjFile
{
	IScene* _scene;
	Factory* _factory;
	std::function<void()> _func;
	
public:
	//Mineral(IScene* scene, Fabula* fabula)
	Mineral(IScene* scene ,std::function<void()> func = {}, Factory* factory = nullptr)
		: ObjFile("objects", "mineral", 1), _func(func)
	{
		_scene = scene;
		_factory = factory;
		this->Scale = 17;
		this->proxy->Mass = 10;
		this->proxy->heightOffset = 18;

	}
	bool IsPickedUp = false;

	void OnPickUp()
	{
		IsPickedUp = true;
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
		this->Origin.Z = _scene->map->GetHeight(Origin)  + proxy->heightOffset;
		auto diff = this->Origin - _factory->Origin;
		auto dist = Vec3::Magnitude(diff);
		if(dist < 100)
		{
			(_func)();
			this->Delete = true;
		}
			
	}
};
