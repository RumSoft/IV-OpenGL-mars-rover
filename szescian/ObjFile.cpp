#include "ObjFile.h"
#include "obj_loader.h"
#include "ObjShapeMemory.h"

#define STB_IMAGE_IMPLEMENTATION
#include "image_loader.h"
#include "TextureMemory.h"

Shape* ObjFile::loadOBJ()
{
	const auto obj = fullname() + ".obj";
	auto loader = objl::Loader();
	if (!loader.LoadFile(obj))
		return nullptr;

	auto shape = new Shape(Triangle);
	shape->MeshMaterial = loader.LoadedMeshes[0].MeshMaterial;
	for (const auto v : loader.LoadedMeshes[0].Vertices)
		shape->AddPoint(v);
	_texture = (!_folder.empty() ? _folder + "/" : "") + loader.LoadedMeshes[0].MeshMaterial.map_Kd;
	return shape;
}

ObjFile::ObjFile(string folder, string filename, ColorF color, float proxyPhysics): ObjFile(
	folder, filename, proxyPhysics)
{
	_color = color;
}

ObjFile::ObjFile(string folder, string filename, float proxyPhysics): _folder(move(folder)), _filename(move(filename))
{
	auto memory = ObjShapeMemory::Instance();
	if (!memory.Exists(fullname()))
		memory.AddShape(loadOBJ(), fullname());
	shape = memory.GetShape(fullname());
	this->Shapes.push_back(shape);


	if (proxyPhysics > 0)
	{
		proxy = (new Proxy(this));
	}

	if (proxy != nullptr)
	{
		float maxX = 0, minX = 0, maxY = 0, minY = 0, maxZ = 0, minZ = 0;
		for (auto p : shape->Vertices)
		{
			smaller(minX, p.Position.X);
			smaller(minY, p.Position.Y);
			smaller(minZ, p.Position.Z);
			bigger(maxX, p.Position.X);
			bigger(maxY, p.Position.Y);
			bigger(maxZ, p.Position.Z);
		}
		proxy->Scale = Vec3::Scale(Vec3(
			                           maxX - minX,
			                           maxY - minY,
			                           maxZ - minZ
		                           ), proxyPhysics);
	}
}

void ObjFile::PostRender()
{
	if (proxy != nullptr)

	this->proxy->DrawProxy();
}

void ObjFile::Init()
{
	const auto shape = this->Shapes[1];
	if (shape == nullptr)
		return;
	if (!_texture.empty())
		shape->texture = TextureMemory::Instance().GetTexture(_texture);

	if (shape->texture > 0)
		shape->Color = ColorF(XYZ((shape->MeshMaterial.Ks)));
	else
		shape->Color = _color;
}

void ObjFile::Update(float frametime)
{
	if(proxy != nullptr)
		proxy->Update(frametime);
}
