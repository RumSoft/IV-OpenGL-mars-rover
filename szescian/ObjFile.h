#pragma once
#include "Shape.h"
#include "Proxy.h"

using namespace std;


#define smaller(a, b) if (b < a) a = b;
#define bigger(a, b) if (b > a) a = b;

class ObjFile : public Geom
{
	Shape* loadOBJ();

public:
	Proxy* proxy = nullptr;
	Shape* shape = nullptr;

	string _folder;
	string _filename;
	string _texture;
	ColorF _color;
	string fullname() const { return (!_folder.empty() ? _folder + "/" : "") + _filename; }

	ObjFile(string folder, string filename, ColorF color, bool proxyPhysics = false);

	ObjFile(string folder, string filename, bool proxyPhysics = false);

	void PostRender() override;


	void Init() override;

	void Update(float frametime) override;
};
