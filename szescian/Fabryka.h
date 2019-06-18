#pragma once
#include "ObjFile.h"


class Factory : public ObjFile {
	
public:
	Factory(IScene* scene) : ObjFile("objects", "fabryka", 0)
	{
		

	}
};
