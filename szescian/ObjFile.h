#pragma once
#include "Geom.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "ObjShapeMemory.h"
#include "Proxy.h"
using namespace std;

struct objFace
{
	int v1;
	int v2;
	int v3;
	int vt1;
	int vt2;
	int vt3;
	int vn1;
	int vn2;
	int vn3;

	objFace(int vv1,
		int vv2,
		int vv3,
		int vvt1,
		int vvt2,
		int vvt3,
		int vvn1,
		int vvn2,
		int vvn3)
	{
		v1 = vv1;
		v2 = vv2;
		v3 = vv3;
		vt1 = vvt1;
		vt2 = vvt2;
		vt3 = vvt3;
		vn1 = vvn1;
		vn2 = vvn2;
		vn3 = vvn3;
	}
};

#define smaller(a, b) if (b < a) a = b;
#define bigger(a, b) if (b > a) a = b;

class ObjFile : public Geom
{
public:
	Proxy* proxy = nullptr;
	Shape* shape = nullptr;

	ObjFile(const char* str, ColorF color = RED, bool proxyPhysics = true)
	{
		auto memory = ObjShapeMemory::Instance();
		if (!memory.Exists(str))
			memory.AddShape(loadOBJ(str), str);
		shape = memory.GetShape(str)->WithColor(color);
		this->Shapes.push_back(shape);

		if (proxyPhysics) {
			proxy = (new Proxy(this));
		}

		if (proxy != nullptr) {
			float maxX = 0, minX = 0, maxY = 0, minY = 0, maxZ = 0, minZ = 0;
			for (auto p : shape->Points)
			{
				smaller(minX, p.X);
				smaller(minY, p.Y);
				smaller(minZ, p.Z);
				bigger(maxX, p.X);
				bigger(maxY, p.Y);
				bigger(maxZ, p.Z);
			}
			proxy->Scale = Vec3::Scale(Vec3(
				maxX - minX,
				maxY - minY,
				maxZ - minZ
			), 0.7);
		}
	}

	void PostRender() override
	{
		this->proxy->DrawProxy();
	}

	Shape* loadOBJ(const char* path)
	{
		OutputDebugStringA("LOADING OBJ: ");
		OutputDebugStringA(path);
		OutputDebugStringA("\n");

		vector<Vec3> vertices;
		vector<Vec3> normals;
		vector<objFace> faces;

		ifstream in(path, ios::in);
		if (!in)
		{
			throw exception("obj file not found");
		}
		string line;

		while (getline(in, line))
		{
			if (line.substr(0, 2) == "v ")
			{
				istringstream s(line.substr(2));
				Vec3 v;
				s >> v.X;
				s >> v.Z;
				s >> v.Y;
				vertices.push_back(v);
			}
			if (line.substr(0, 3) == "vn ")
			{
				istringstream s(line.substr(3));
				Vec3 vn;
				s >> vn.X;
				s >> vn.Z;
				s >> vn.Y;
				normals.push_back(vn);
			}
			else if (line.substr(0, 2) == "f ")
			{
				istringstream s(line.substr(2));
				int vv[3], vt[3], vn[3];


				int r = sscanf_s(s.str().c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d",
					&vv[0], &vt[0], &vn[0],
					&vv[1], &vt[1], &vn[1],
					&vv[2], &vt[2], &vn[2]);
				if (r == 9)
				{
					vv[0]--; vv[1]--; vv[2]--;
					vt[0]--; vt[1]--; vt[2]--;
					vn[0]--; vn[1]--; vn[2]--;
				}
				else {
					r = sscanf_s(s.str().c_str(), "%d//%d %d//%d %d//%d",
						&vv[0], &vn[0],
						&vv[1], &vn[1],
						&vv[2], &vn[2]);

					vv[0]--; vv[1]--; vv[2]--;
					vn[0]--; vn[1]--; vn[2]--;
					vt[0] = vt[1] = vt[2] = 0;
				}


				faces.emplace_back(
					vv[0], vv[1], vv[2],
					vt[0], vt[1], vt[2],
					vn[0], vn[1], vn[2]);
			}
			else if (line[0] == '#')
			{
				/* ignoring this line */
			}
			else
			{
				/* ignoring this line */
			}
		}

		auto s1 = new Shape(Triangle);
		for (auto f : faces)
		{
			const int v = vertices.size();
			const int n = normals.size();
			if (f.v1 < v
				&& f.v2 < v
				&& f.v3 < v
				&& f.vn1 < n
				&& f.vn2 < n
				&& f.vn3 < n)
			{
				s1->AddPoint(vertices[f.v1], normals[f.vn1]);
				s1->AddPoint(vertices[f.v2], normals[f.vn2]);
				s1->AddPoint(vertices[f.v3], normals[f.vn3]);
			}
		}

		vertices.clear();
		normals.clear();
		faces.clear();

		return s1;
	}

	void Update() override
	{
		proxy->Update();
	}
};
