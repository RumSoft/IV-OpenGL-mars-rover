#pragma once
#include <map>
#include <string>

class TextureMemory
{
	TextureMemory()
	{

	}
	std::map<std::string, unsigned int> textures;
public:
	static TextureMemory& Instance() {
		static TextureMemory theInstance;
		return theInstance;
	}

	unsigned int GetTexture(const std::string& file)
	{
		if (!TextureMemory::Instance().Exists(file))
			TextureMemory::Instance().AddTexture(Shape::LoadTexture(file.c_str(), 1), file);
		return _GetTexture(file);
	}

private:
	unsigned int _GetTexture(const std::string& name)
	{
		return textures.at(name);
	}

	void AddTexture(unsigned int shape, const std::string& name)
	{
		textures.insert_or_assign(name, shape);
	}

	bool Exists(const std::string& name)
	{
		return textures.count(name) > 0;
	}

};
