#pragma once

#include "Vec3.h"
#include "Quat.h"
using namespace std;

class CollisionDetectorHelper
{
public:
	static bool Intersects(
		Vec3 a[], Vec3 b[],
		Quat arot = Quat::Identity(),
		Quat brot = Quat::Identity());

	static bool Separated(Vec3 vertsA[], Vec3 vertsB[], Vec3 axis);
};



