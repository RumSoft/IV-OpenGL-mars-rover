#pragma once

#include <cmath>
#include "Vec3.h"

#define SMALL_float 0.0000000001
#define ANGROT Quat::FromAngleAxis
#define ROT(deg, axis) Quat::FromAngleAxis(D2R(deg), axis)
struct Quat
{
	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};
		float data[4];
	};


	/**
	 * Constructors.
	 */
	inline Quat();
	inline Quat(float data[]);
	inline Quat(Vec3 vector, float scalar);
	inline Quat(float x, float y, float z, float w);


	/**
	 * Constants for common quaternions.
	 */
	static inline Quat Identity();


	/**
	 * Returns the angle between two quaternions.
	 * The quaternions must be normalized.
	 * @param a: The first quaternion.
	 * @param b: The second quaternion.
	 * @return: A scalar value.
	 */
	static inline float Angle(Quat a, Quat b);

	/**
	 * Returns the conjugate of a quaternion.
	 * @param rotation: The quaternion in question.
	 * @return: A new quaternion.
	 */
	static inline Quat Conjugate(Quat rotation);

	/**
	 * Returns the dot product of two quaternions.
	 * @param lhs: The left side of the multiplication.
	 * @param rhs: The right side of the multiplication.
	 * @return: A scalar value.
	 */
	static inline float Dot(Quat lhs, Quat rhs);

	/**
	 * Creates a new quaternion from the angle-axis representation of
	 * a rotation.
	 * @param angle: The rotation angle in radians.
	 * @param axis: The vector about which the rotation occurs.
	 * @return: A new quaternion.
	 */
	static inline Quat FromAngleAxis(float angle, Vec3 axis);

	/**
	 * Create a new quaternion from the euler angle representation of
	 * a rotation. The z, x and y values represent rotations about those
	 * axis in that respective order.
	 * @param rotation: The x, y and z rotations.
	 * @return: A new quaternion.
	 */
	static inline Quat FromEuler(Vec3 rotation);

	/**
	 * Create a new quaternion from the euler angle representation of
	 * a rotation. The z, x and y values represent rotations about those
	 * axis in that respective order.
	 * @param x: The rotation about the x-axis in radians.
	 * @param y: The rotation about the y-axis in radians.
	 * @param z: The rotation about the z-axis in radians.
	 * @return: A new quaternion.
	 */
	static inline Quat FromEuler(float x, float y, float z);


	static inline Quat GetZRotation(Quat q)
	{
		auto rot = Quat::ToEuler(q);
		rot.X = 0; rot.Y = 0;
		return Quat::FromEuler(rot);
	}

	/**
	 * Create a quaternion rotation which rotates "fromVector" to "toVector".
	 * @param fromVector: The vector from which to start the rotation.
	 * @param toVector: The vector at which to end the rotation.
	 * @return: A new quaternion.
	 */
	static inline Quat FromToRotation(Vec3 fromVector,
		Vec3 toVector);

	/**
	 * Returns the inverse of a rotation.
	 * @param rotation: The quaternion in question.
	 * @return: A new quaternion.
	 */
	static inline Quat Inverse(Quat rotation);

	/**
	 * Interpolates between a and b by t, which is clamped to the range [0-1].
	 * The result is normalized before being returned.
	 * @param a: The starting rotation.
	 * @param b: The ending rotation.
	 * @return: A new quaternion.
	 */
	static inline Quat Lerp(Quat a, Quat b, float t);

	/**
	 * Interpolates between a and b by t. This normalizes the result when
	 * complete.
	 * @param a: The starting rotation.
	 * @param b: The ending rotation.
	 * @param t: The interpolation value.
	 * @return: A new quaternion.
	 */
	static inline Quat LerpUnclamped(Quat a, Quat b,
		float t);

	/**
	 * Creates a rotation with the specified forward direction. This is the
	 * same as calling LookRotation with (0, 1, 0) as the upwards vector.
	 * The output is undefined for parallel vectors.
	 * @param forward: The forward direction to look toward.
	 * @return: A new quaternion.
	 */
	static inline Quat LookRotation(Vec3 forward);

	/**
	 * Creates a rotation with the specified forward and upwards directions.
	 * The output is undefined for parallel vectors.
	 * @param forward: The forward direction to look toward.
	 * @param upwards: The direction to treat as up.
	 * @return: A new quaternion.
	 */
	static inline Quat LookRotation(Vec3 forward, Vec3 upwards);

	/**
	 * Returns the norm of a quaternion.
	 * @param rotation: The quaternion in question.
	 * @return: A scalar value.
	 */
	static inline float Norm(Quat rotation);

	/**
	 * Returns a quaternion with identical rotation and a norm of one.
	 * @param rotation: The quaternion in question.
	 * @return: A new quaternion.
	 */
	static inline Quat Normalized(Quat rotation);

	/**
	 * Returns a new Quaternion created by rotating "from" towards "to" by
	 * "maxRadiansDelta". This will not overshoot, and if a negative delta is
	 * applied, it will rotate till completely opposite "to" and then stop.
	 * @param from: The rotation at which to start.
	 * @param to: The rotation at which to end.
	 # @param maxRadiansDelta: The maximum number of radians to rotate.
	 * @return: A new Quaternion.
	 */
	static inline Quat RotateTowards(Quat from, Quat to,
		float maxRadiansDelta);

	/**
	 * Returns a new quaternion interpolated between a and b, using spherical
	 * linear interpolation. The variable t is clamped to the range [0-1]. The
	 * resulting quaternion will be normalized.
	 * @param a: The starting rotation.
	 * @param b: The ending rotation.
	 * @param t: The interpolation value.
	 * @return: A new quaternion.
	 */
	static inline Quat Slerp(Quat a, Quat b, float t);

	/**
	 * Returns a new quaternion interpolated between a and b, using spherical
	 * linear interpolation. The resulting quaternion will be normalized.
	 * @param a: The starting rotation.
	 * @param b: The ending rotation.
	 * @param t: The interpolation value.
	 * @return: A new quaternion.
	 */
	static inline Quat SlerpUnclamped(Quat a, Quat b,
		float t);

	/**
	 * Outputs the angle axis representation of the provided quaternion.
	 * @param rotation: The input quaternion.
	 * @param angle: The output angle.
	 * @param axis: The output axis.
	 */
	static inline void ToAngleAxis(Quat rotation, float &angle,
		Vec3 &axis);

	/**
	 * Returns the Euler angle representation of a rotation. The resulting
	 * vector contains the rotations about the z, x and y axis, in that order.
	 * @param rotation: The quaternion to convert.
	 * @return: A new vector.
	 */
	static inline Vec3 ToEuler(Quat rotation);

	/**
	 * Operator overloading.
	 */
	inline struct Quat& operator+=(const float rhs);
	inline struct Quat& operator-=(const float rhs);
	inline struct Quat& operator*=(const float rhs);
	inline struct Quat& operator/=(const float rhs);
	inline struct Quat& operator+=(const Quat rhs);
	inline struct Quat& operator-=(const Quat rhs);
	inline struct Quat& operator*=(const Quat rhs);
};

inline Quat operator-(Quat rhs);
inline Quat operator+(Quat lhs, const float rhs);
inline Quat operator-(Quat lhs, const float rhs);
inline Quat operator*(Quat lhs, const float rhs);
inline Quat operator/(Quat lhs, const float rhs);
inline Quat operator+(const float lhs, Quat rhs);
inline Quat operator-(const float lhs, Quat rhs);
inline Quat operator*(const float lhs, Quat rhs);
inline Quat operator/(const float lhs, Quat rhs);
inline Quat operator+(Quat lhs, const Quat rhs);
inline Quat operator-(Quat lhs, const Quat rhs);
inline Quat operator*(Quat lhs, const Quat rhs);
inline Vec3 operator*(Quat lhs, const Vec3 rhs);
inline bool operator==(const Quat lhs, const Quat rhs);
inline bool operator!=(const Quat lhs, const Quat rhs);



/*******************************************************************************
 * Implementation
 */

Quat::Quat() : X(0), Y(0), Z(0), W(1) {}
Quat::Quat(float data[]) : X(data[0]), Y(data[1]), Z(data[2]),
W(data[3]) {}
Quat::Quat(Vec3 vector, float scalar) : X(vector.X),
Y(vector.Y), Z(vector.Z), W(scalar) {}
Quat::Quat(float x, float y, float z, float w) : X(x), Y(y),
Z(z), W(w) {}


Quat Quat::Identity() { return Quat(0, 0, 0, 1); }


float Quat::Angle(Quat a, Quat b)
{
	float dot = Dot(a, b);
	return acos(fmin(fabs(dot), 1)) * 2;
}

Quat Quat::Conjugate(Quat rotation)
{
	return Quat(-rotation.X, -rotation.Y, -rotation.Z, rotation.W);
}

float Quat::Dot(Quat lhs, Quat rhs)
{
	return lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z + lhs.W * rhs.W;
}

Quat Quat::FromAngleAxis(float angle, Vec3 axis)
{
	Quat q;
	float m = sqrt(axis.X * axis.X + axis.Y * axis.Y + axis.Z * axis.Z);
	float s = sin(angle / 2) / m;
	q.X = axis.X * s;
	q.Y = axis.Y * s;
	q.Z = axis.Z * s;
	q.W = cos(angle / 2);
	return q;
}

Quat Quat::FromEuler(Vec3 rotation)
{
	return FromEuler(rotation.X, rotation.Y, rotation.Z);
}

Quat Quat::FromEuler(float x, float y, float z)
{
	float cx = cos(x * 0.5);
	float cy = cos(y * 0.5);
	float cz = cos(z * 0.5);
	float sx = sin(x * 0.5);
	float sy = sin(y * 0.5);
	float sz = sin(z * 0.5);
	Quat q;
	q.X = cx * sy * sz + cy * cz * sx;
	q.Y = cx * cz * sy - cy * sx * sz;
	q.Z = cx * cy * sz - cz * sx * sy;
	q.W = sx * sy * sz + cx * cy * cz;
	return q;
}

Quat Quat::FromToRotation(Vec3 fromVector, Vec3 toVector)
{
	float dot = Vec3::Dot(fromVector, toVector);
	float k = sqrt(Vec3::SqrMagnitude(fromVector) *
		Vec3::SqrMagnitude(toVector));
	if (fabs(dot / k + 1) < 0.00001)
	{
		Vec3 ortho = Vec3::Orthogonal(fromVector);
		return Quat(Vec3::Normalized(ortho), 0);
	}
	Vec3 cross = Vec3::Cross(fromVector, toVector);
	return Normalized(Quat(cross, dot + k));
}

Quat Quat::Inverse(Quat rotation)
{
	float n = Norm(rotation);
	return Conjugate(rotation) / (n * n);
}

Quat Quat::Lerp(Quat a, Quat b, float t)
{
	if (t < 0) return Normalized(a);
	else if (t > 1) return Normalized(b);
	return LerpUnclamped(a, b, t);
}

Quat Quat::LerpUnclamped(Quat a, Quat b, float t)
{
	Quat quaternion;
	if (Dot(a, b) >= 0)
		quaternion = a * (1 - t) + b * t;
	else
		quaternion = a * (1 - t) - b * t;
	return Normalized(quaternion);
}

Quat Quat::LookRotation(Vec3 forward)
{
	return LookRotation(forward, UP);
}

Quat Quat::LookRotation(Vec3 forward, Vec3 upwards)
{
	// Normalize inputs
	forward = Vec3::Normalized(forward);
	upwards = Vec3::Normalized(upwards);
	// Don't allow zero vectors
	if (Vec3::SqrMagnitude(forward) < SMALL_float || Vec3::SqrMagnitude(upwards) < SMALL_float)
		return Quat::Identity();
	// Handle alignment with up direction
	if (1 - fabs(Vec3::Dot(forward, upwards)) < SMALL_float)
		return FromToRotation(Vec3::Forward(), forward);
	// Get orthogonal vectors
	Vec3 right = Vec3::Normalized(Vec3::Cross(upwards, forward));
	upwards = Vec3::Cross(forward, right);
	// Calculate rotation
	Quat quaternion;
	float radicand = right.X + upwards.Y + forward.Z;
	if (radicand > 0)
	{
		quaternion.W = sqrt(1.0 + radicand) * 0.5;
		float recip = 1.0 / (4.0 * quaternion.W);
		quaternion.X = (upwards.Z - forward.Y) * recip;
		quaternion.Y = (forward.X - right.Z) * recip;
		quaternion.Z = (right.Y - upwards.X) * recip;
	}
	else if (right.X >= upwards.Y && right.X >= forward.Z)
	{
		quaternion.X = sqrt(1.0 + right.X - upwards.Y - forward.Z) * 0.5;
		float recip = 1.0 / (4.0 * quaternion.X);
		quaternion.W = (upwards.Z - forward.Y) * recip;
		quaternion.Z = (forward.X + right.Z) * recip;
		quaternion.Y = (right.Y + upwards.X) * recip;
	}
	else if (upwards.Y > forward.Z)
	{
		quaternion.Y = sqrt(1.0 - right.X + upwards.Y - forward.Z) * 0.5;
		float recip = 1.0 / (4.0 * quaternion.Y);
		quaternion.Z = (upwards.Z + forward.Y) * recip;
		quaternion.W = (forward.X - right.Z) * recip;
		quaternion.X = (right.Y + upwards.X) * recip;
	}
	else
	{
		quaternion.Z = sqrt(1.0 - right.X - upwards.Y + forward.Z) * 0.5;
		float recip = 1.0 / (4.0 * quaternion.Z);
		quaternion.Y = (upwards.Z + forward.Y) * recip;
		quaternion.X = (forward.X + right.Z) * recip;
		quaternion.W = (right.Y - upwards.X) * recip;
	}
	return quaternion;
}

float Quat::Norm(Quat rotation)
{
	return sqrt(rotation.X * rotation.X +
		rotation.Y * rotation.Y +
		rotation.Z * rotation.Z +
		rotation.W * rotation.W);
}

Quat Quat::Normalized(Quat rotation)
{
	return rotation / Norm(rotation);
}

Quat Quat::RotateTowards(Quat from, Quat to,
	float maxRadiansDelta)
{
	float angle = Quat::Angle(from, to);
	if (angle == 0)
		return to;
	maxRadiansDelta = fmax(maxRadiansDelta, angle - M_PI);
	float t = fmin(1, maxRadiansDelta / angle);
	return Quat::SlerpUnclamped(from, to, t);
}

Quat Quat::Slerp(Quat a, Quat b, float t)
{
	if (t < 0) return Normalized(a);
	else if (t > 1) return Normalized(b);
	return SlerpUnclamped(a, b, t);
}

Quat Quat::SlerpUnclamped(Quat a, Quat b, float t)
{
	float n1;
	float n2;
	float n3 = Dot(a, b);
	bool flag = false;
	if (n3 < 0)
	{
		flag = true;
		n3 = -n3;
	}
	if (n3 > 0.999999)
	{
		n2 = 1 - t;
		n1 = flag ? -t : t;
	}
	else
	{
		float n4 = acos(n3);
		float n5 = 1 / sin(n4);
		n2 = sin((1 - t) * n4) * n5;
		n1 = flag ? -sin(t * n4) * n5 : sin(t * n4) * n5;
	}
	Quat quaternion;
	quaternion.X = (n2 * a.X) + (n1 * b.X);
	quaternion.Y = (n2 * a.Y) + (n1 * b.Y);
	quaternion.Z = (n2 * a.Z) + (n1 * b.Z);
	quaternion.W = (n2 * a.W) + (n1 * b.W);
	return Normalized(quaternion);
}

void Quat::ToAngleAxis(Quat rotation, float &angle, Vec3 &axis)
{
	if (rotation.W > 1)
		rotation = Normalized(rotation);
	angle = 2 * acos(rotation.W);
	float s = sqrt(1 - rotation.W * rotation.W);
	if (s < 0.00001) {
		axis.X = 1;
		axis.Y = 0;
		axis.Z = 0;
	}
	else {
		axis.X = rotation.X / s;
		axis.Y = rotation.Y / s;
		axis.Z = rotation.Z / s;
	}
}

Vec3 Quat::ToEuler(Quat rotation)
{
	float sqw = rotation.W * rotation.W;
	float sqx = rotation.X * rotation.X;
	float sqy = rotation.Y * rotation.Y;
	float sqz = rotation.Z * rotation.Z;
	// If normalized is one, otherwise is correction factor
	float unit = sqx + sqy + sqz + sqw;
	float test = rotation.X * rotation.W - rotation.Y * rotation.Z;
	Vec3 v;
	// Singularity at north pole
	if (test > 0.4995f * unit)
	{
		v.Y = 2 * atan2(rotation.Y, rotation.X);
		v.X = M_PI_2;
		v.Z = 0;
		return v;
	}
	// Singularity at south pole
	if (test < -0.4995f * unit)
	{
		v.Y = -2 * atan2(rotation.Y, rotation.X);
		v.X = -M_PI_2;
		v.Z = 0;
		return v;
	}
	// Yaw
	v.Y = atan2(2 * rotation.W * rotation.Y + 2 * rotation.Z * rotation.X,
		1 - 2 * (rotation.X * rotation.X + rotation.Y * rotation.Y));
	// Pitch
	v.X = asin(2 * (rotation.W * rotation.X - rotation.Y * rotation.Z));
	// Roll
	v.Z = atan2(2 * rotation.W * rotation.Z + 2 * rotation.X * rotation.Y,
		1 - 2 * (rotation.Z * rotation.Z + rotation.X * rotation.X));
	return v;
}

struct Quat& Quat::operator+=(const float rhs)
{
	X += rhs;
	Y += rhs;
	Z += rhs;
	W += rhs;
	return *this;
}

struct Quat& Quat::operator-=(const float rhs)
{
	X -= rhs;
	Y -= rhs;
	Z -= rhs;
	W -= rhs;
	return *this;
}

struct Quat& Quat::operator*=(const float rhs)
{
	X *= rhs;
	Y *= rhs;
	Z *= rhs;
	W *= rhs;
	return *this;
}

struct Quat& Quat::operator/=(const float rhs)
{
	X /= rhs;
	Y /= rhs;
	Z /= rhs;
	W /= rhs;
	return *this;
}

struct Quat& Quat::operator+=(const Quat rhs)
{
	X += rhs.X;
	Y += rhs.Y;
	Z += rhs.Z;
	W += rhs.W;
	return *this;
}

struct Quat& Quat::operator-=(const Quat rhs)
{
	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;
	W -= rhs.W;
	return *this;
}

struct Quat& Quat::operator*=(const Quat rhs)
{
	Quat q;
	q.W = W * rhs.W - X * rhs.X - Y * rhs.Y - Z * rhs.Z;
	q.X = X * rhs.W + W * rhs.X + Y * rhs.Z - Z * rhs.Y;
	q.Y = W * rhs.Y - X * rhs.Z + Y * rhs.W + Z * rhs.X;
	q.Z = W * rhs.Z + X * rhs.Y - Y * rhs.X + Z * rhs.W;
	*this = q;
	return *this;
}

Quat operator-(Quat rhs) { return rhs * -1; }
Quat operator+(Quat lhs, const float rhs) { return lhs += rhs; }
Quat operator-(Quat lhs, const float rhs) { return lhs -= rhs; }
Quat operator*(Quat lhs, const float rhs) { return lhs *= rhs; }
Quat operator/(Quat lhs, const float rhs) { return lhs /= rhs; }
Quat operator+(const float lhs, Quat rhs) { return rhs += lhs; }
Quat operator-(const float lhs, Quat rhs) { return rhs -= lhs; }
Quat operator*(const float lhs, Quat rhs) { return rhs *= lhs; }
Quat operator/(const float lhs, Quat rhs) { return rhs /= lhs; }
Quat operator+(Quat lhs, const Quat rhs)
{
	return lhs += rhs;
}
Quat operator-(Quat lhs, const Quat rhs)
{
	return lhs -= rhs;
}
Quat operator*(Quat lhs, const Quat rhs)
{
	return lhs *= rhs;
}

Vec3 operator*(Quat lhs, const Vec3 rhs)
{
	Vec3 u = Vec3(lhs.X, lhs.Y, lhs.Z);
	float s = lhs.W;
	return u * (Vec3::Dot(u, rhs) * 2)
		+ rhs * (s * s - Vec3::Dot(u, u))
		+ Vec3::Cross(u, rhs) * (2.0 * s);
}

bool operator==(const Quat lhs, const Quat rhs)
{
	return lhs.X == rhs.X &&
		lhs.Y == rhs.Y &&
		lhs.Z == rhs.Z &&
		lhs.W == rhs.W;
}

bool operator!=(const Quat lhs, const Quat rhs)
{
	return !(lhs == rhs);
}
