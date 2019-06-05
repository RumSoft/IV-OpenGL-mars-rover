#pragma once

#include "Vec3.h"
#include <cmath>
#include "Quat.h"
#include <algorithm>
using namespace std;

class CollisionDetectorHelper
{
public:
	

	static bool Intersects(
		Vec3 a[], Vec3 b[], 
		Quat arot = Quat::Identity(), 
		Quat brot = Quat::Identity())
	{
		if (Separated(a, b, arot * Vec3::Right()))
			return false;
		if (Separated(a, b, arot * Vec3::Up()))
			return false;
		if (Separated(a, b, arot * Vec3::Forward()))
			return false;

		if (Separated(a, b, brot * Vec3::Right()))
			return false;
		if (Separated(a, b, brot * Vec3::Up()))
			return false;
		if (Separated(a, b, brot * Vec3::Forward()))
			return false;

		if (Separated(a, b, Vec3::Cross(arot * Vec3::Right(),  brot * Vec3::Right())))
			return false;
		if (Separated(a, b, Vec3::Cross(arot * Vec3::Right(),  brot * Vec3::Up())))
			return false;
		if (Separated(a, b, Vec3::Cross(arot * Vec3::Right(),  brot * Vec3::Forward())))
			return false;

		if (Separated(a, b, Vec3::Cross(arot * Vec3::Up(),  brot * Vec3::Right())))
			return false;
		if (Separated(a, b, Vec3::Cross(arot * Vec3::Up(), brot *  Vec3::Up())))
			return false;
		if (Separated(a, b, Vec3::Cross(arot * Vec3::Up(),  brot * Vec3::Forward())))
			return false;

		if (Separated(a, b, Vec3::Cross(arot * Vec3::Forward(), brot *  Vec3::Right())))
			return false;
		if (Separated(a, b, Vec3::Cross(arot * Vec3::Forward(),  brot * Vec3::Up())))
			return false;
		if (Separated(a, b, Vec3::Cross(arot * Vec3::Forward(), brot * Vec3::Forward())))
			return false;
		return true;
	}

	static bool Separated(Vec3 vertsA[], Vec3 vertsB[], Vec3 axis)
	{
		// Handles the cross product = {0,0,0} case
		if (axis == Vec3::Zero())
			return false;

		auto aMin = 1000000000000000000000000.00f;
		auto aMax = -1000000000000000000000000.00f;
		auto bMin = 1000000000000000000000000.00f;
		auto bMax = -1000000000000000000000000.00f;

		// Define two intervals, a and b. Calculate their min and max values
		for (auto i = 0; i < 8; i++)
		{
			auto aDist = Vec3::Dot(vertsA[i], axis);
			aMin = aDist < aMin ? aDist : aMin;
			aMax = aDist > aMax ? aDist : aMax;
			auto bDist = Vec3::Dot(vertsB[i], axis);
			bMin = bDist < bMin ? bDist : bMin;
			bMax = bDist > bMax ? bDist : bMax;
		}

		// One-dimensional intersection test between a and b
		auto longSpan = max(aMax, bMax) - min(aMin, bMin);
		auto sumSpan = aMax - aMin + bMax - bMin;
		return longSpan >= sumSpan; // > to treat touching as intersection
	}
};
