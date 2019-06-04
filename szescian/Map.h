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

	float sign(Vec3 p1, Vec3 p2, Vec3 p3)
	{
		return (p1.X - p3.X) * (p2.Y - p3.Y) - (p2.X - p3.X) * (p1.Y - p3.Y);
	}

	bool PointInTriangle(Vec3 pt, Vec3 v1, Vec3 v2, Vec3 v3)
	{
		const auto d1 = sign(pt, v1, v2);
		const auto d2 = sign(pt, v2, v3);
		const auto d3 = sign(pt, v3, v1);

		const auto has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
		const auto has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

		return !(has_neg && has_pos);
	}

	Vec3 scalePoint(Geom* geom, Vec3 v)
	{
		return geom->Rotation * Vec3::Scale(v, geom->Scale) + geom->Origin;
	}

	float InterpolateTraingle(Vec3 p, Vec3 a, Vec3 b, Vec3 c)
	{

		a.Z = 0;

		// calculate vectors from point f to vertices p1, p2 and p3:
		auto f1 = a - p;
		auto f2 = b - p;
		auto f3 = c - p;
		f1.Z = 0;
		f2.Z = 0;
		f3.Z = 0;
		// calculate the areas and factors (order of parameters doesn't matter):
		auto aa = Vec3::Magnitude(Vec3::Cross(a - b, a - c)); // main triangle area a
		auto a1 = Vec3::Magnitude(Vec3::Cross(f2, f3)) / aa; // p1's triangle area / a
		auto a2 = Vec3::Magnitude(Vec3::Cross(f3, f1)) / aa; // p2's triangle area / a 
		auto a3 = Vec3::Magnitude(Vec3::Cross(f1, f2)) / aa; // p3's triangle area / a
		// find the uv corresponding to point f (uv1/uv2/uv3 are associated to p1/p2/p3):
		auto uv = a.Z * a1 + b.Z * a2 + c.Z * a3;

		return uv;
	}


	void InitializeHeightmap(Geom* geom)
	{
		for (int i = 0; i < MAP_LENGTH; i++)
			for (int j = 0; j < MAP_LENGTH; j++)
			{
				for (int k = 0; k < geom->Shapes[1]->Vertices.size(); k += 3)
				{
					const auto a_ = geom->Shapes[1]->Vertices[k];
					const auto b_ = geom->Shapes[1]->Vertices[1 + k];
					const auto c_ = geom->Shapes[1]->Vertices[2 + k];
					const auto a = scalePoint(geom, a_.Position);
					const auto b = scalePoint(geom, b_.Position);
					const auto c = scalePoint(geom, c_.Position);

					auto p = ToWorld(Vec3(i, j));
					p.Z = 0;
					if (PointInTriangle(p, a, b, c))
					{
						_map[i][j] = InterpolateTraingle(p, c, b, a);
					}
				}

			}

		//for (int i = 0; i < MAP_LENGTH; i++)
		//	for (int j = 0; j < MAP_LENGTH; j++)
		//		if (_map[i][j] > 100)
		//			_map[i][j] = 100;
		//		else if (_map[i][j] < -100)
		//			_map[i][j] = -100;
	}
public:
	Map(Lazik* lazik, Geom* mapGeom)
	{
		{
			//init with 0s
			for (auto& i : _map)
				for (auto& j : i)
					j = -10;
		}


		InitializeHeightmap(mapGeom);

		_lazik = lazik;
	}

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


		/*auto wheelML = _lazik->Origin + _lazik->Rotation * _lazik->wheel3R->Origin;
		auto wheelMR = _lazik->Origin + _lazik->Rotation * _lazik->wheel3R->Origin;
		wheel3.Z = GetHeight(wheelML);
		wheel4.Z = GetHeight(wheelMR);
*/
//_lazik->wheel2L->Origin = wheelML;
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
		glVertex3f(XYZ((p1 + 5.5 * Vec3(1, 1, 0))));
		glVertex3f(XYZ((p2 + 5.5 * Vec3(1, -1, 0))));
		glVertex3f(XYZ((p4 + 5.5 * Vec3(-1, -1, 0))));
		glVertex3f(XYZ((p3 + 5.5 * Vec3(-1, 1, 0))));
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