#pragma once
#include "ObjFile.h"


class Factory : public ObjFile {
	
public:
	Factory(IScene* scene) : ObjFile("objects", "box", 1, 30)
	{
		
	}
};
