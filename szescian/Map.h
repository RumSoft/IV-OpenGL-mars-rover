#pragma once
#include "Shape.h"

const int MAP_SIZE = 100;
const int MAP_LENGTH = MAP_SIZE + MAP_SIZE + 1;
const int MAP_SCALE = 20; // one map[x][y] = 10 units in opengl

class Map : public Geom
{
	float _map[MAP_LENGTH][MAP_LENGTH];
	Lazik* _lazik;

	Vec3 midpoint;
public:
	Map(Lazik* lazik, Geom* mapGeom)
	{
		//init with 0s
		for (int i = 0; i < MAP_LENGTH; i++)

			for (int j = 0; j < MAP_LENGTH; j++)
				_map[i][j] =  20 * sin(i / 2.f) * cos(j / 2.f) - 10;



		_lazik = lazik;
	}

	Quat lastRot = Quat::Identity();
	//update lazik to align to ground
	void Update(float frametime) override
	{
		auto wheel1 = _lazik->Origin + _lazik->Rotation * _lazik->wheel1L->Origin;
		auto wheel2 = _lazik->Origin + _lazik->Rotation * _lazik->wheel1R->Origin;
		auto wheel3 = _lazik->Origin + _lazik->Rotation * _lazik->wheel3L->Origin;
		auto wheel4 = _lazik->Origin + _lazik->Rotation * _lazik->wheel3R->Origin;

		wheel1.Z = GetHeight(wheel1);
		wheel2.Z = GetHeight(wheel2);
		wheel3.Z = GetHeight(wheel3);
		wheel4.Z = GetHeight(wheel4);

		midpoint = (wheel1 + wheel2 + wheel3 + wheel4) / 4;

		wheel1 -= midpoint;
		wheel2 -= midpoint;
		wheel3 -= midpoint;
		wheel4 -= midpoint;

		const auto wheel12 = (wheel1 + wheel2) / 2;
		const auto wheel13 = (wheel1 + wheel3) / 2;
		const auto wheel24 = (wheel2 + wheel4) / 2;
		const auto wheel34 = (wheel3 + wheel4) / 2;

		const auto cr1 = Vec3::Cross(wheel12, wheel13);
		const auto cr2 = Vec3::Cross(wheel24, wheel12);
		const auto cr3 = Vec3::Cross(wheel34, wheel24);
		const auto cr4 = Vec3::Cross(wheel13, wheel34);

		const auto rot = Quat::FromEuler(Vec3::Normalized(cr1 + cr2 + cr3 + cr4));
		_lazik->Rotation = Quat::FromAngleAxis(D2R(90), UP) * rot;
		_lazik->Origin.Z = midpoint.Z;
	}

	float GetHeight(const float x, const float y)
	{
		return GetHeight(Vec3(x, y, 0));
	}

	float GetHeight(const Vec3 p)
	{
		/*

	   Y,   h3-----h4
	   /|\  |       |
		|   |  *    |
		|	h1-----h2
		|
		'------------->> X

		*/
		const auto mapPos = ToMap(p);
		const int l = floor(mapPos.X);
		const int r = ceil(mapPos.X);
		const int b = floor(mapPos.Y);
		const int t = ceil(mapPos.Y);

		const auto xw = mapPos.X - floor(mapPos.X);
		const auto yw = mapPos.Y - floor(mapPos.Y);

		const auto
			h1 = _map[l][b],
			h2 = _map[r][b],
			h3 = _map[l][t],
			h4 = _map[r][t];

		const auto h12 = h1 * (1 - xw) + h2 * xw;
		const auto h34 = h3 * (1 - xw) + h4 * xw;
		const auto h = h12 * (1 - yw) + h34 * yw;
		return h;
	};

	void PostRender() override
	{
		for (auto i = 0; i < MAP_LENGTH - 1; i++)
			for (auto j = 0; j < MAP_LENGTH - 1; j++)
				DrawSquare(i, j);


		glLineWidth(5);
		glColor3fv(ColorF(0x66900).GL());
		glBegin(GL_LINE_LOOP);
		glVertex3f(XYZ((midpoint + UP * 100)));
		glVertex3f(XYZ((midpoint - UP * 100)));
		glEnd();
	}

private:
	void DrawSquare(int x, int y)
	{
		Vec3
			p1 = ToWorld(Vec3(x, y, 0)),
			p2 = ToWorld(Vec3(x, y + 1, 0)),
			p3 = ToWorld(Vec3(x + 1, y, 0)),
			p4 = ToWorld(Vec3(x + 1, y + 1, 0));
		p1.Z = GetHeight(p1);
		p2.Z = GetHeight(p2);
		p3.Z = GetHeight(p3);
		p4.Z = GetHeight(p4);

		glBegin(GL_QUADS);
		glVertex3f(XYZ((p1 + Vec3(1, 1, 0))));
		glVertex3f(XYZ((p2 + Vec3(1, -1, 0))));
		glVertex3f(XYZ((p4 + Vec3(-1, -1, 0))));
		glVertex3f(XYZ((p3 + Vec3(-1, 1, 0))));
		glEnd();
	}

	/// convert world position to map coordinates
	Vec3 ToMap(const Vec3 worldPos) const
	{
		return worldPos / MAP_SCALE + MAP_SIZE;
	}

	/// convert map coordinates to world position
	Vec3 ToWorld(const Vec3 mapPos) const
	{
		return (mapPos - MAP_SIZE) * MAP_SCALE;
	}
};