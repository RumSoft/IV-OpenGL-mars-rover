#pragma once
#include "Shape.h"
#include "Proxy.h"

using namespace std;


#define smaller(a, b) if (b < a) a = b;
#define bigger(a, b) if (b > a) a = b;

class ObjFile : public Geom
{
protected:
	Shape* loadOBJ();

public:
	Shape* shape = nullptr;

	string _folder;
	string _filename;
	string _texture;
	ColorF _color;
	string fullname() const { return (!_folder.empty() ? _folder + "/" : "") + _filename; }

	ObjFile(string folder, string filename, ColorF color, float proxyPhysics = 0, float heightOffset=0);

	ObjFile(string folder, string filename, float proxyPhysics = 0, float heightOffset=0);

	void PostRender() override;

	void Init() override;

	void Update(float frametime) override;
};
