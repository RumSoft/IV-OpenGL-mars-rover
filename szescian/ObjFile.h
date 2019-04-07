#pragma once
#include "Geom.h"
#include <fstream>
#include <sstream>
#include "Vec2.h"
using namespace std;

class ObjFile : public Geom
{
public:
	ObjFile()
	{
		bool res = loadOBJ("cube.obj");
		this->Scale = Vec3::One() * 10;
	}

	bool loadOBJ(const char* path)
	{
		vector<Vec3> vertices;
		vector<GLushort> elements;
		vector<Vec3> normals;


		ifstream in(path, ios::in);
		if (!in)
		{
			cerr << "Cannot open " << path << endl;
			exit(1);
		}
		string line;
		
		auto s1 = new Shape(Triangle, GREEN);
		while (getline(in, line))
		{
			if(line.substr(0,2) == "o ")
			{
				
			}
			if (line.substr(0, 2) == "v ")
			{
				istringstream s(line.substr(2));
				Vec3 v;
				s >> v.X;
				s >> v.Y;
				s >> v.Z;
				vertices.push_back(v);
			}
			if (line.substr(0, 3) == "vn ")
			{
				istringstream s(line.substr(3));
				Vec3 vn;
				s >> vn.X;
				s >> vn.Y;
				s >> vn.Z;
				normals.push_back(vn);
			}
			else if (line.substr(0, 2) == "f ")
			{
				istringstream s(line.substr(2));
				int v[3], vt[3], vn[3];

				sscanf_s(s.str().c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d",
				         &v[0], &vt[0], &vn[0],
				         &v[1], &vt[1], &vn[1],
				         &v[2], &vt[2], &vn[2]);
				v[0]--;
				v[1]--;
				v[2]--;
				vt[0]--;
				vt[1]--;
				vt[2]--;
				vn[0]--;
				vn[1]--;
				vn[2]--;

				s1->AddPoint(vertices[v[0]], normals[vn[0]]);
				s1->AddPoint(vertices[v[1]], normals[vn[1]]);
				s1->AddPoint(vertices[v[2]], normals[vn[2]]);
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
		this->Shapes.push_back(s1);

		/*normals.resize(vertices.size(), Vec3(0.0, 0.0, 0.0));
		for (int i = 0; i < elements.size(); i += 3)
		{
			GLushort ia = elements[i];
			GLushort ib = elements[i + 1];
			GLushort ic = elements[i + 2];
			Vec3 normal = Vec3::Normalized(Vec3::Cross(
				Vec3(vertices[ib]) - Vec3(vertices[ia]),
				Vec3(vertices[ic]) - Vec3(vertices[ia])));
			normals[ia] = normals[ib] = normals[ic] = normal;
		}*/
	}

};
