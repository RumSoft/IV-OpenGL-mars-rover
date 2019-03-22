#pragma once
#include <corecrt_math_defines.h>
#include "Quat.h"

class Entity
{
public:
	Vec3 Origin;
	Quat Rotation;
};

inline float Deg2Rad(const float deg) { return deg * M_PI / 180; }
inline float Rad2Deg(const float rad) { return rad * 180 / M_PI; }
