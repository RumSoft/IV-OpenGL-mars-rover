#pragma once
#include "IScene.h"
#include "../AntTweakBar.h"
#include "Lazik.h"


class MyScene : public IScene
{
public:
	TwBar* bar;
	TwBar* bar2;
	MyScene();
	~MyScene();


	void drawMapCube(int x, int y)
	{
		auto geom = new Geom();
		geom->Shapes.push_back((new Face(
			Vec3(0, 0, 0),
			Vec3(0, 0.9, 0),
			Vec3(0.9, 0, 0),
			Vec3(0.9, 0.9, 0), GRAY))
			->WithPosition(Vec3(x,y) * mapUnit)
			->WithScale(mapUnit));
		geom->Origin = -mapOffset * mapUnit;

		this->Geometries.push_back(geom);
	}

	void Update(float frametime) override;
};

