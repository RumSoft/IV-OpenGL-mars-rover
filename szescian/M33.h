#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include "Quat.h"
#include "Vec3.h"

struct M33
{
	union
	{
		struct
		{
			float D00;
			float D01;
			float D02;
			float D10;
			float D11;
			float D12;
			float D20;
			float D21;
			float D22;
		};
		float data[3][3];
	};


	/**
	 * Constructors.
	 */
	inline M33();
	inline M33(float data[]);
	inline M33(Vec3 row0, Vec3 row1, Vec3 row2);
	inline M33(float d00, float d01, float d02, float d10, float d11,
		float d12, float d20, float d21, float d22);


	/**
	 * Constants for common Matrix3x3.
	 */
	static inline M33 Identity();
	static inline M33 Zero();
	static inline M33 One();


	/**
	 * Returns the determinate of a matrix.
	 * @param matrix: The input matrix.
	 * @return: A scalar value.
	 */
	static inline float Determinate(M33 matrix);

	/**
	 * Converts a Quat to a rotation matrix.
	 * @param rotation: The input Quat.
	 * @return: A new rotation matrix.
	 */
	static inline M33 FromQuat(Quat rotation);

	/**
	 * Returns the inverse of a matrix.
	 * @param matrix: The input matrix.
	 * @return: A new matrix.
	 */
	static inline M33 Inverse(M33 matrix);

	/**
	 * Returns true if a matrix is invertible.
	 * @param matrix: The input matrix.
	 * @return: A new matrix.
	 */
	static inline bool IsInvertible(M33 matrix);

	/**
	 * Multiplies two matrices element-wise.
	 * @param a: The left-hand side of the multiplication.
	 * @param b: The right-hand side of the multiplication.
	 * @return: A new matrix.
	 */
	static inline M33 Scale(M33 a, M33 b);

	/**
	 * Converts a rotation matrix to a Quat.
	 * @param rotation: The input rotation matrix.
	 * @return: A new Quat.
	 */
	static inline Quat ToQuat(M33 rotation);

	/**
	 * Returns the transpose of a matrix.
	 * @param matrix: The input matrix.
	 * @return: A new matrix.
	 */
	static inline M33 Transpose(M33 matrix);

	/**
	 * Operator overloading.
	 */
	inline struct M33& operator+=(const float rhs);
	inline struct M33& operator-=(const float rhs);
	inline struct M33& operator*=(const float rhs);
	inline struct M33& operator/=(const float rhs);
	inline struct M33& operator+=(const M33 rhs);
	inline struct M33& operator-=(const M33 rhs);
	inline struct M33& operator*=(const M33 rhs);
};

inline M33 operator-(M33 rhs);
inline M33 operator+(M33 lhs, const float rhs);
inline M33 operator-(M33 lhs, const float rhs);
inline M33 operator*(M33 lhs, const float rhs);
inline M33 operator/(M33 lhs, const float rhs);
inline M33 operator+(const float lhs, M33 rhs);
inline M33 operator-(const float lhs, M33 rhs);
inline M33 operator*(const float lhs, M33 rhs);
inline M33 operator+(M33 lhs, const M33 rhs);
inline M33 operator-(M33 lhs, const M33 rhs);
inline M33 operator*(M33 lhs, const M33 rhs);
inline Vec3 operator*(M33 lhs, const Vec3 rhs);
inline bool operator==(const M33 lhs, const M33 rhs);
inline bool operator!=(const M33 lhs, const M33 rhs);



/*******************************************************************************
 * Implementation
 */

M33::M33() : D00(1), D01(0), D02(0), D10(0), D11(1), D12(0), D20(0),
D21(0), D22(1) {}
M33::M33(float data[]) : D00(data[0]), D01(data[1]), D02(data[2]),
D10(data[3]), D11(data[4]), D12(data[5]), D20(data[6]), D21(data[7]),
D22(data[8]) {}
M33::M33(Vec3 row0, Vec3 row1, Vec3 row2) : D00(row0.X),
D01(row0.Y), D02(row0.Z), D10(row1.X), D11(row1.Y), D12(row1.Z),
D20(row2.X), D21(row2.Y), D22(row2.Z) {}
M33::M33(float d00, float d01, float d02, float d10, float d11,
	float d12, float d20, float d21, float d22) : D00(d00), D01(d01),
	D02(d02), D10(d10), D11(d11), D12(d12), D20(d20), D21(d21), D22(d22) {}


M33 M33::Identity()
{
	return M33(1, 0, 0, 0, 1, 0, 0, 0, 1);
}

M33 M33::Zero()
{
	return M33(0, 0, 0, 0, 0, 0, 0, 0, 0);
}

M33 M33::One()
{
	return M33(1, 1, 1, 1, 1, 1, 1, 1, 1);
}


float M33::Determinate(M33 matrix)
{
	float v1 = matrix.D00 * (matrix.D22 * matrix.D11 -
		matrix.D21 * matrix.D12);
	float v2 = matrix.D10 * (matrix.D22 * matrix.D01 -
		matrix.D21 * matrix.D02);
	float v3 = matrix.D20 * (matrix.D12 * matrix.D01 -
		matrix.D11 * matrix.D02);
	return v1 - v2 + v3;
}

M33 M33::FromQuat(Quat rotation)
{
	M33 m;
	float sqw = rotation.W * rotation.W;
	float sqx = rotation.X * rotation.X;
	float sqy = rotation.Y * rotation.Y;
	float sqz = rotation.Z * rotation.Z;

	float invSqr = 1 / (sqx + sqy + sqz + sqw);
	m.D00 = (sqx - sqy - sqz + sqw) * invSqr;
	m.D11 = (-sqx + sqy - sqz + sqw) * invSqr;
	m.D22 = (-sqx - sqy + sqz + sqw) * invSqr;

	float tmp1 = rotation.X * rotation.Y;
	float tmp2 = rotation.Z * rotation.W;
	m.D10 = 2.0 * (tmp1 + tmp2) * invSqr;
	m.D01 = 2.0 * (tmp1 - tmp2) * invSqr;

	tmp1 = rotation.X * rotation.Z;
	tmp2 = rotation.Y * rotation.W;
	m.D20 = 2.0 * (tmp1 - tmp2) * invSqr;
	m.D02 = 2.0 * (tmp1 + tmp2) * invSqr;
	tmp1 = rotation.Y * rotation.Z;
	tmp2 = rotation.X * rotation.W;
	m.D21 = 2.0 * (tmp1 + tmp2) * invSqr;
	m.D12 = 2.0 * (tmp1 - tmp2) * invSqr;
	return m;
}

M33 M33::Inverse(M33 matrix)
{
	M33 a;
	a.D00 = matrix.D22 * matrix.D11 - matrix.D21 * matrix.D12;
	a.D01 = matrix.D21 * matrix.D02 - matrix.D22 * matrix.D01;
	a.D02 = matrix.D12 * matrix.D01 - matrix.D11 * matrix.D02;
	a.D10 = matrix.D20 * matrix.D12 - matrix.D22 * matrix.D10;
	a.D11 = matrix.D22 * matrix.D00 - matrix.D20 * matrix.D02;
	a.D12 = matrix.D10 * matrix.D02 - matrix.D12 * matrix.D00;
	a.D20 = matrix.D21 * matrix.D10 - matrix.D20 * matrix.D11;
	a.D21 = matrix.D20 * matrix.D01 - matrix.D21 * matrix.D00;
	a.D22 = matrix.D11 * matrix.D00 - matrix.D10 * matrix.D01;
	return 1 / Determinate(matrix) * a;
}

bool M33::IsInvertible(M33 matrix)
{
	return fabs(Determinate(matrix)) > 0.00001;
}

M33 M33::Scale(M33 a, M33 b)
{
	M33 m;
	m.D00 = a.D00 * b.D00;
	m.D01 = a.D01 * b.D01;
	m.D02 = a.D02 * b.D02;
	m.D10 = a.D10 * b.D10;
	m.D11 = a.D11 * b.D11;
	m.D12 = a.D12 * b.D12;
	m.D20 = a.D20 * b.D20;
	m.D21 = a.D21 * b.D21;
	m.D22 = a.D22 * b.D22;
	return m;
}

Quat M33::ToQuat(M33 rotation)
{
	Quat q;
	float trace = rotation.D00 + rotation.D11 + rotation.D22;
	if (trace > 0)
	{
		float s = 0.5 / sqrt(trace + 1);
		q.W = 0.25 / s;
		q.X = (rotation.D21 - rotation.D12) * s;
		q.Y = (rotation.D02 - rotation.D20) * s;
		q.Z = (rotation.D10 - rotation.D01) * s;
	}
	else
	{
		if (rotation.D00 > rotation.D11 && rotation.D00 > rotation.D22)
		{
			float s = 2 * sqrt(1 + rotation.D00 - rotation.D11 - rotation.D22);
			q.W = (rotation.D21 - rotation.D12) / s;
			q.X = 0.25 * s;
			q.Y = (rotation.D01 + rotation.D10) / s;
			q.Z = (rotation.D02 + rotation.D20) / s;
		}
		else if (rotation.D11 > rotation.D22)
		{
			float s = 2 * sqrt(1 + rotation.D11 - rotation.D00 - rotation.D22);
			q.W = (rotation.D02 - rotation.D20) / s;
			q.X = (rotation.D01 + rotation.D10) / s;
			q.Y = 0.25 * s;
			q.Z = (rotation.D12 + rotation.D21) / s;
		}
		else
		{
			float s = 2 * sqrt(1 + rotation.D22 - rotation.D00 - rotation.D11);
			q.W = (rotation.D10 - rotation.D01) / s;
			q.X = (rotation.D02 + rotation.D20) / s;
			q.Y = (rotation.D12 + rotation.D21) / s;
			q.Z = 0.25 * s;
		}
	}
	return q;
}

M33 M33::Transpose(M33 matrix)
{
	float tmp;
	tmp = matrix.D01;
	matrix.D01 = matrix.D10;
	matrix.D10 = tmp;
	tmp = matrix.D02;
	matrix.D02 = matrix.D20;
	matrix.D20 = tmp;
	tmp = matrix.D12;
	matrix.D12 = matrix.D21;
	matrix.D21 = tmp;
	return matrix;
}


struct M33& M33::operator+=(const float rhs)
{
	D00 += rhs; D01 += rhs; D02 += rhs;
	D10 += rhs; D11 += rhs; D12 += rhs;
	D20 += rhs; D21 += rhs; D22 += rhs;
	return *this;
}

struct M33& M33::operator-=(const float rhs)
{
	D00 -= rhs; D01 -= rhs; D02 -= rhs;
	D10 -= rhs; D11 -= rhs; D12 -= rhs;
	D20 -= rhs; D21 -= rhs; D22 -= rhs;
	return *this;
}

struct M33& M33::operator*=(const float rhs)
{
	D00 *= rhs; D01 *= rhs; D02 *= rhs;
	D10 *= rhs; D11 *= rhs; D12 *= rhs;
	D20 *= rhs; D21 *= rhs; D22 *= rhs;
	return *this;
}

struct M33& M33::operator/=(const float rhs)
{
	D00 /= rhs; D01 /= rhs; D02 /= rhs;
	D10 /= rhs; D11 /= rhs; D12 /= rhs;
	D20 /= rhs; D21 /= rhs; D22 /= rhs;
	return *this;
}

struct M33& M33::operator+=(const M33 rhs)
{
	D00 += rhs.D00; D01 += rhs.D01; D02 += rhs.D02;
	D10 += rhs.D10; D11 += rhs.D11; D12 += rhs.D12;
	D20 += rhs.D20; D21 += rhs.D21; D22 += rhs.D22;
	return *this;
}

struct M33& M33::operator-=(const M33 rhs)
{
	D00 -= rhs.D00; D01 -= rhs.D01; D02 -= rhs.D02;
	D10 -= rhs.D10; D11 -= rhs.D11; D12 -= rhs.D12;
	D20 -= rhs.D20; D21 -= rhs.D21; D22 -= rhs.D22;
	return *this;
}

struct M33& M33::operator*=(const M33 rhs)
{
	M33 m;
	m.D00 = D00 * rhs.D00 + D01 * rhs.D10 + D02 * rhs.D20;
	m.D01 = D00 * rhs.D01 + D01 * rhs.D11 + D02 * rhs.D21;
	m.D02 = D00 * rhs.D02 + D01 * rhs.D12 + D02 * rhs.D22;
	m.D10 = D10 * rhs.D00 + D11 * rhs.D10 + D12 * rhs.D20;
	m.D11 = D10 * rhs.D01 + D11 * rhs.D11 + D12 * rhs.D21;
	m.D12 = D10 * rhs.D02 + D11 * rhs.D12 + D12 * rhs.D22;
	m.D20 = D20 * rhs.D00 + D21 * rhs.D10 + D22 * rhs.D20;
	m.D21 = D20 * rhs.D01 + D21 * rhs.D11 + D22 * rhs.D21;
	m.D22 = D20 * rhs.D02 + D21 * rhs.D12 + D22 * rhs.D22;
	*this = m;
	return *this;
}

M33 operator-(M33 rhs) { return rhs * -1; }
M33 operator+(M33 lhs, const float rhs) { return lhs += rhs; }
M33 operator-(M33 lhs, const float rhs) { return lhs -= rhs; }
M33 operator*(M33 lhs, const float rhs) { return lhs *= rhs; }
M33 operator/(M33 lhs, const float rhs) { return lhs /= rhs; }
M33 operator+(const float lhs, M33 rhs) { return rhs += lhs; }
M33 operator-(const float lhs, M33 rhs) { return rhs -= lhs; }
M33 operator*(const float lhs, M33 rhs) { return rhs *= lhs; }
M33 operator+(M33 lhs, const M33 rhs) { return lhs += rhs; }
M33 operator-(M33 lhs, const M33 rhs) { return lhs -= rhs; }
M33 operator*(M33 lhs, const M33 rhs) { return lhs *= rhs; }

Vec3 operator*(M33 lhs, const Vec3 rhs)
{
	Vec3 v;
	v.X = lhs.D00 * rhs.X + lhs.D01 * rhs.Y + lhs.D02 * rhs.Z;
	v.Y = lhs.D10 * rhs.X + lhs.D11 * rhs.Y + lhs.D12 * rhs.Z;
	v.Z = lhs.D20 * rhs.X + lhs.D21 * rhs.Y + lhs.D22 * rhs.Z;
	return v;
}

bool operator==(const M33 lhs, const M33 rhs)
{
	return lhs.D00 == rhs.D00 &&
		lhs.D01 == rhs.D01 &&
		lhs.D02 == rhs.D02 &&
		lhs.D10 == rhs.D10 &&
		lhs.D11 == rhs.D11 &&
		lhs.D12 == rhs.D12 &&
		lhs.D20 == rhs.D20 &&
		lhs.D21 == rhs.D21 &&
		lhs.D22 == rhs.D22;
}

bool operator!=(const M33 lhs, const M33 rhs)
{
	return !(lhs == rhs);
}
