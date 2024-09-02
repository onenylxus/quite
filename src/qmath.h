// Quite - Programming library for C applications
// Copyright (C) 2024 Nicholas Ng
//
// src/qmath.h
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#ifndef QMATH_H
#define QMATH_H

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif /* defined(_MSC_VER) && (_MSC_VER > 1000) */

//// API ////

#if defined(Q_MATH_IMPLEMENTATION) && defined(Q_MATH_STATIC_INLINE)
	#error "Q_MATH_IMPLEMENTATION and Q_MATH_STATIC_INLINE are contradictory to each other"
#endif /* defined(Q_MATH_IMPLEMENTATION) && defined(Q_MATH_STATIC_INLINE) */

#if defined(Q_MATH_IMPLEMENTATION)
	#if defined(_WIN32) && defined(Q_EXPORT_SHARED_LIBRARY)
		#define QM_API __declspec(dllexport)
	#elif defined(_WIN32) && defined(Q_IMPORT_SHARED_LIBRARY)
		#define QM_API __declspec(dllimport)
	#elif defined(Q_EXPORT_SHARED_LIBRARY)
		#define QM_API __attribute__((visibility("default")))
	#else
		#define QM_API extern inline
	#endif /* defined(_WIN32) && defined(Q_EXPORT_SHARED_LIBRARY)... */
#elif defined(Q_MATH_STATIC_INLINE)
	#define QM_API static inline
#else
	#define QM_API inline
#endif /* defined(Q_MATH_IMPLEMENTATION)... */

#include <math.h>
#include "quite.h"

//// Epsilon ////

#ifndef Q_EPSILON
	#define Q_EPSILON 1.192092896e-7
#endif /* Q_EPSILON */

//// Angles ////

#ifndef Q_PI
	#define Q_PI 3.14159265358979323846
#endif /* Q_PI */

#ifndef Q_DEG
	#define Q_DEG(a) ((a) * 180.0f / Q_PI)
#endif /* Q_DEG */

#ifndef Q_RAD
	#define Q_RAD(a) ((a) * Q_PI / 180.0f)
#endif /* Q_RAD */

//// Vector and matrix types ////

#ifndef Q_VECTOR
	#define Q_VECTOR

	typedef struct q_vector2
	{
		q_float x;
		q_float y;
	} q_vector2;

	typedef struct q_vector3
	{
		q_float x;
		q_float y;
		q_float z;
	} q_vector3;

	typedef struct q_vector4
	{
		q_float x;
		q_float y;
		q_float z;
		q_float w;
	} q_vector4;

	#if defined(Q_ENABLE_TYPE_ALIAS)
		typedef q_vector2 qt_vec2;
		typedef q_vector3 qt_vec3;
		typedef q_vector4 qt_vec4;
	#endif /* defined(Q_ENABLE_TYPE_ALIAS) */
#endif /* Q_VECTOR */

#ifndef Q_MATRIX
	#define Q_MATRIX

	typedef struct q_matrix22
	{
		q_float m0, m2;
		q_float m1, m3;
	} q_matrix22;

	typedef struct q_matrix23
	{
		q_float m0, m2, m4;
		q_float m1, m3, m5;
	} q_matrix23;

	typedef struct q_matrix24
	{
		q_float m0, m2, m4, m6;
		q_float m1, m3, m5, m7;
	} q_matrix24;

	typedef struct q_matrix32
	{
		q_float m0, m3;
		q_float m1, m4;
		q_float m2, m5;
	} q_matrix32;

	typedef struct q_matrix33
	{
		q_float m0, m3, m6;
		q_float m1, m4, m7;
		q_float m2, m5, m8;
	} q_matrix33;

	typedef struct q_matrix34
	{
		q_float m0, m3, m6, m9;
		q_float m1, m4, m7, m10;
		q_float m2, m5, m8, m11;
	} q_matrix34;

	typedef struct q_matrix42
	{
		q_float m0, m4;
		q_float m1, m5;
		q_float m2, m6;
		q_float m3, m7;
	} q_matrix42;

	typedef struct q_matrix43
	{
		q_float m0, m4, m8;
		q_float m1, m5, m9;
		q_float m2, m6, m10;
		q_float m3, m7, m11;
	} q_matrix43;

	typedef struct q_matrix44
	{
		q_float m0, m4, m8, m12;
		q_float m1, m5, m9, m13;
		q_float m2, m6, m10, m14;
		q_float m3, m7, m11, m15;
	} q_matrix44;

	#if defined(Q_ENABLE_TYPE_ALIAS)
		typedef q_matrix22 qt_mat22, qt_mat2;
		typedef q_matrix23 qt_mat23;
		typedef q_matrix24 qt_mat24;
		typedef q_matrix32 qt_mat32;
		typedef q_matrix33 qt_mat33, qt_mat3;
		typedef q_matrix34 qt_mat34;
		typedef q_matrix42 qt_mat42;
		typedef q_matrix43 qt_mat43;
		typedef q_matrix44 qt_mat44, qt_mat4;
	#endif /* defined(Q_ENABLE_TYPE_ALIAS) */
#endif /* Q_MATRIX */

//// Quaternion type ////

#ifndef Q_QUATERNION
	#define Q_QUATERNION

	typedef q_vector4 q_quaternion;

	#if defined(Q_ENABLE_TYPE_ALIAS)
		typedef q_quaternion qt_quat;
	#endif /* defined(Q_ENABLE_TYPE_ALIAS) */
#endif /* Q_QUATERNION */

//// Internal functions ////

// Square function
inline q_float sqf(q_float x)
{
	return x * x;
}

// Cube function
inline q_float cbf(q_float x)
{
	return x * x * x;
}

// Float equal function
inline q_bool equalf(q_float l, q_float r)
{
	return Q_BOOL(fabsf(l - r) <= fmaxf(fmaxf(fabsf(l), fabsf(r)), 1.0f) * Q_EPSILON);
}

//// Functions ////

// Prevent function name mangling
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

//// Float functions ////

// Clamp function
QM_API q_float qmFloatClamp(q_float value, q_float min, q_float max)
{
	if (max < min)
	{
		return value;
	}
	return fminf(fmaxf(value, min), max);
}

// Wrap function
QM_API q_float qmFloatWrap(q_float value, q_float min, q_float max)
{
	if (max <= min)
	{
		return value;
	}
	return value - (max - min) * floorf((value - min) / (max - min));
}

// Linear interpolate function
QM_API q_float qmFloatLerp(q_float value, q_float start, q_float end)
{
	return start + value * (end - start);
}

// Normalize function
QM_API q_float qmFloatNormalize(q_float value, q_float start, q_float end)
{
	return (value - start) * (end - start);
}

// Remap function
QM_API q_float qmFloatRemap(q_float value, q_float inStart, q_float inEnd, q_float outStart, q_float outEnd)
{
	if (inStart == inEnd || outStart == outEnd)
	{
		return value;
	}
	return (value - inStart) * (outEnd - outStart) / (inEnd - inStart) + outStart;
}

// Equal function
QM_API q_bool qmFloatEqual(q_float left, q_float right)
{
	return Q_BOOL(equalf(left, right));
}

//// Vector2 functions ////

// Zero vector function
QM_API q_vector2 qmVector2Zero(q_void)
{
	q_vector2 result = {0.0f, 0.0f};
	return result;
}

// One vector function
QM_API q_vector2 qmVector2One(q_void)
{
	q_vector2 result = {1.0f, 1.0f};
	return result;
}

// Add function
QM_API q_vector2 qmVector2Add(q_vector2 left, q_vector2 right)
{
	q_vector2 result = {
		left.x + right.x,
		left.y + right.y
	};
	return result;
}

// Scalar add function
QM_API q_vector2 qmVector2AddScalar(q_vector2 vec, q_float scl)
{
	q_vector2 result = {
		vec.x + scl,
		vec.y + scl
	};
	return result;
}

// Subtract function
QM_API q_vector2 qmVector2Subtract(q_vector2 left, q_vector2 right)
{
	q_vector2 result = {
		left.x - right.x,
		left.y - right.y
	};
	return result;
}

// Scalar subtract function
QM_API q_vector2 qmVector2SubtractScalar(q_vector2 vec, q_float scl)
{
	q_vector2 result = {
		vec.x - scl,
		vec.y - scl
	};
	return result;
}

// Multiply function
QM_API q_vector2 qmVector2Multiply(q_vector2 left, q_vector2 right)
{
	q_vector2 result = {
		left.x * right.x,
		left.y * right.y
	};
	return result;
}

// Scale function
QM_API q_vector2 qmVector2Scale(q_vector2 vec, q_float scl)
{
	q_vector2 result = {
		vec.x * scl,
		vec.y * scl
	};
	return result;
}

// Negate function
QM_API q_vector2 qmVector2Negate(q_vector2 vec)
{
	q_vector2 result = {
		-vec.x,
		-vec.y
	};
	return result;
}

// Divide function
QM_API q_vector2 qmVector2Divide(q_vector2 left, q_vector2 right)
{
	q_vector2 result = {
		left.x / right.x,
		left.y / right.y
	};
	return result;
}

// Scalar divide function
QM_API q_vector2 qmVector2DivideScalar(q_vector2 vec, q_float scl)
{
	q_vector2 result = {
		vec.x / scl,
		vec.y / scl
	};
	return result;
}

// Normalize function
QM_API q_vector2 qmVector2Normalize(q_vector2 vec)
{
	q_float length = sqrtf(sqf(vec.x) + sqf(vec.y)); // qmVector2Length(vec)
	if (length == 0.0f)
	{
		return vec;
	}

	q_vector2 result = { // qmVector2DivideScale(vec, length)
		vec.x / length,
		vec.y / length
	};
	return result;
}

// Invert function
QM_API q_vector2 qmVector2Invert(q_vector2 vec)
{
	q_vector2 result = {
		1.0f / vec.x,
		1.0f / vec.y
	};
	return result;
}

// Minimum function
QM_API q_vector2 qmVector2Min(q_vector2 left, q_vector2 right)
{
	q_vector2 result = {
		fminf(left.x, right.x),
		fminf(left.y, right.y)
	};
	return result;
}

// Maximum function
QM_API q_vector2 qmVector2Max(q_vector2 left, q_vector2 right)
{
	q_vector2 result = {
		fmaxf(left.x, right.x),
		fmaxf(left.y, right.y)
	};
	return result;
}

// Clamp function
QM_API q_vector2 qmVector2Clamp(q_vector2 vec, q_vector2 min, q_vector2 max)
{
	q_vector2 result = {
		max.x < min.x ? vec.x : fminf(fmaxf(vec.x, min.x), max.x), // qmFloatClamp(vec.x, min.x, max.x)
		max.y < min.y ? vec.y : fminf(fmaxf(vec.y, min.y), max.y)  // qmFloatClamp(vec.y, min.y, max.y)
	};
	return result;
}

// Clamp on vector magnitude function
QM_API q_vector2 qmVector2ClampMag(q_vector2 vec, q_float min, q_float max)
{
	if (max < min)
	{
		return vec;
	}

	q_float length = sqrtf(sqf(vec.x) + sqf(vec.y)); // qmVector2Length(vec)
	if (length == 0.0f)
	{
		return vec;
	}

	q_float scl = 1.0f;
	if (length < min)
	{
		scl = min / length;
	}
	if (length > max)
	{
		scl = max / length;
	}

	q_vector2 result = { // qmVector2Scale(vec, scl)
		vec.x * scl,
		vec.y * scl
	};
	return result;
}

// Linear interpolation function
QM_API q_vector2 qmVector2Lerp(q_float value, q_vector2 start, q_vector2 end)
{
	q_vector2 result = {
		start.x + value * (end.x - start.x), // qmFloatLerp(value, start.x, end.x)
		start.y + value * (end.y - start.y)  // qmFloatLerp(value, start.y, end.y)
	};
	return result;
}

// Reflection function
QM_API q_vector2 qmVector2Reflect(q_vector2 vec, q_vector2 normal)
{
	q_float dot = vec.x * normal.x + vec.y * normal.y; // qmVector2DotProduct(vec, normal)

	q_vector2 result = {
		vec.x - normal.x * 2.0f * dot,
		vec.y - normal.y * 2.0f * dot
	};
	return result;
}

// Refraction function
QM_API q_vector2 qmVector2Refract(q_vector2 vec, q_vector2 normal, q_float index)
{
	q_float dot = vec.x * normal.x + vec.y * normal.y; // qmVector2DotProduct(vec, normal)
	q_float diff = 1.0f - sqf(index) * (1.0f - sqf(dot));
	if (diff < 0)
	{
		return vec;
	}

	q_vector2 result = {
		vec.x * index - normal.x * (dot * index + sqrtf(diff)),
		vec.y * index - normal.y * (dot * index + sqrtf(diff))
	};
	return result;
}

// Move function
QM_API q_vector2 qmVector2Move(q_vector2 vec, q_vector2 target, q_float dist)
{
	if (dist <= 0.0f)
	{
		return vec;
	}

	q_float cdist = sqrtf(sqf(target.x - vec.x) + sqf(target.y - vec.y)); // qmVector2Distance(target, vec)
	if (cdist > dist)
	{
		return vec;
	}

	q_vector2 result = {
		vec.x + dist / cdist * (target.x - vec.x),
		vec.y + dist / cdist * (target.y - vec.y)
	};
	return result;
}

// Rotate function
QM_API q_vector2 qmVector2Rotate(q_vector2 vec, q_float angle)
{
	q_float sin = sinf(angle);
	q_float cos = cosf(angle);

	q_vector2 result = {
		vec.x * cos - vec.y * sin,
		vec.x * sin + vec.y * cos
	};
	return result;
}

// Length function
QM_API q_float qmVector2Length(q_vector2 vec)
{
	return sqrtf(sqf(vec.x) + sqf(vec.y));
}

// Squared length function
QM_API q_float qmVector2LengthSq(q_vector2 vec)
{
	return sqf(vec.x) + sqf(vec.y);
}

// Dot product function
QM_API q_float qmVector2DotProduct(q_vector2 left, q_vector2 right)
{
	return left.x * right.x + left.y * right.y;
}

// Distance function
QM_API q_float qmVector2Distance(q_vector2 left, q_vector2 right)
{
	return sqrtf(sqf(left.x - right.x) + sqf(left.y - right.y));
}

// Squared distance function
QM_API q_float qmVector2DistanceSq(q_vector2 left, q_vector2 right)
{
	return sqf(left.x - right.x) + sqf(left.y - right.y);
}

// Angle function
QM_API q_float qmVector2Angle(q_vector2 left, q_vector2 right)
{
	q_float det = left.x * right.y - left.y * right.x;
	q_float dot = left.x * right.x + left.y * right.y; // qmVector2DotProduct(left, right)
	return atan2f(det, dot);
}

// Line angle function
QM_API q_float qmVector2LineAngle(q_vector2 start, q_vector2 end)
{
	return -atan2f(end.y - start.y, end.x - start.x);
}

// Equal function
QM_API q_bool qmVector2Equal(q_vector2 left, q_vector2 right)
{
	return Q_BOOL(
		equalf(left.x, right.x) &&
		equalf(left.y, right.y)
	);
}

//// Vector3 functions ////

// Zero vector function
QM_API q_vector3 qmVector3Zero(q_void)
{
	q_vector3 result = {0.0f, 0.0f, 0.0f};
	return result;
}

// One vector function
QM_API q_vector3 qmVector3One(q_void)
{
	q_vector3 result = {1.0f, 1.0f, 1.0f};
	return result;
}

// Add function
QM_API q_vector3 qmVector3Add(q_vector3 left, q_vector3 right)
{
	q_vector3 result = {
		left.x + right.x,
		left.y + right.y,
		left.z + right.z
	};
	return result;
}

// Scalar add function
QM_API q_vector3 qmVector3AddScalar(q_vector3 vec, q_float scl)
{
	q_vector3 result = {
		vec.x + scl,
		vec.y + scl,
		vec.z + scl
	};
	return result;
}

// Subtract function
QM_API q_vector3 qmVector3Subtract(q_vector3 left, q_vector3 right)
{
	q_vector3 result = {
		left.x - right.x,
		left.y - right.y,
		left.z - right.z
	};
	return result;
}

// Scalar subtract function
QM_API q_vector3 qmVector3SubtractScalar(q_vector3 vec, q_float scl)
{
	q_vector3 result = {
		vec.x - scl,
		vec.y - scl,
		vec.z - scl
	};
	return result;
}

// Multiply function
QM_API q_vector3 qmVector3Multiply(q_vector3 left, q_vector3 right)
{
	q_vector3 result = {
		left.x * right.x,
		left.y * right.y,
		left.z * right.z
	};
	return result;
}

// Scale function
QM_API q_vector3 qmVector3Scale(q_vector3 vec, q_float scl)
{
	q_vector3 result = {
		vec.x * scl,
		vec.y * scl,
		vec.z * scl
	};
	return result;
}

// Negate function
QM_API q_vector3 qmVector3Negate(q_vector3 vec)
{
	q_vector3 result = {
		-vec.x,
		-vec.y,
		-vec.z
	};
	return result;
}

// Divide function
QM_API q_vector3 qmVector3Divide(q_vector3 left, q_vector3 right)
{
	q_vector3 result = {
		left.x / right.x,
		left.y / right.y,
		left.z / right.z
	};
	return result;
}

// Scalar divide function
QM_API q_vector3 qmVector3DivideScalar(q_vector3 vec, q_float scl)
{
	q_vector3 result = {
		vec.x / scl,
		vec.y / scl,
		vec.z / scl
	};
	return result;
}

// Normalize function
QM_API q_vector3 qmVector3Normalize(q_vector3 vec)
{
	q_float length = sqrtf(sqf(vec.x) + sqf(vec.y) + sqf(vec.z)); // qmVector3Length(vec)
	if (length == 0.0f)
	{
		return vec;
	}

	q_vector3 result = { // qmVector3DivideScale(vec, length)
		vec.x / length,
		vec.y / length,
		vec.z / length
	};
	return result;
}

// Orthonormalize function
QM_API q_void qmVector3Orthonormalize(q_vector3 *left, q_vector3 *right)
{
	q_vector3 vec = *left;
	q_float len = sqrtf(sqf(vec.x) + sqf(vec.y) + sqf(vec.z)); // qmVector3Length(vec)
	if (len > 0.0f) // qmVector3DivideScale(left, len)
	{
		left->x /= len;
		left->y /= len;
		left->z /= len;
	}

	q_vector3 lcross = { // qmVector3CrossProduct(left, right)
		left->y * right->z - left->z * right->y,
		left->z * right->x - left->x * right->z,
		left->x * right->y - left->y * right->x
	};
	vec = lcross;
	len = sqrtf(sqf(vec.x) + sqf(vec.y) + sqf(vec.z)); // qmVector3Length(vec)
	if (len > 0.0f) // qmVector3DivideScale(lcross, len)
	{
		lcross.x /= len;
		lcross.y /= len;
		lcross.z /= len;
	}

	q_vector3 rcross = { // qmVector3CrossProduct(lcross, left)
		lcross.y * left->z - lcross.z * left->y,
		lcross.z * left->x - lcross.x * left->z,
		lcross.x * left->y - lcross.y * left->x
	};
	*right = rcross;
}

// Invert function
QM_API q_vector3 qmVector3Invert(q_vector3 vec)
{
	q_vector3 result = {
		1.0f / vec.x,
		1.0f / vec.y,
		1.0f / vec.z
	};
	return result;
}

// Minimum function
QM_API q_vector3 qmVector3Min(q_vector3 left, q_vector3 right)
{
	q_vector3 result = {
		fminf(left.x, right.x),
		fminf(left.y, right.y),
		fminf(left.z, right.z)
	};
	return result;
}

// Maximum function
QM_API q_vector3 qmVector3Max(q_vector3 left, q_vector3 right)
{
	q_vector3 result = {
		fmaxf(left.x, right.x),
		fmaxf(left.y, right.y),
		fmaxf(left.z, right.z)
	};
	return result;
}

// Clamp function
QM_API q_vector3 qmVector3Clamp(q_vector3 vec, q_vector3 min, q_vector3 max)
{
	q_vector3 result = {
		max.x < min.x ? vec.x : fminf(fmaxf(vec.x, min.x), max.x), // qmFloatClamp(vec.x, min.x, max.x)
		max.y < min.y ? vec.y : fminf(fmaxf(vec.y, min.y), max.y), // qmFloatClamp(vec.y, min.y, max.y)
		max.z < min.z ? vec.z : fminf(fmaxf(vec.z, min.z), max.z)  // qmFloatClamp(vec.z, min.z, max.z)
	};
	return result;
}

// Clamp on vector magnitude function
QM_API q_vector3 qmVector3ClampMag(q_vector3 vec, q_float min, q_float max)
{
	if (max < min)
	{
		return vec;
	}

	q_float length = sqrtf(sqf(vec.x) + sqf(vec.y) + sqf(vec.z)); // qmVector3Length(vec)
	if (length <= 0.0f)
	{
		return vec;
	}

	q_float scl = 1.0f;
	if (length < min)
	{
		scl = min / length;
	}
	if (length > max)
	{
		scl = max / length;
	}

	q_vector3 result = { // qmVector3Scale(vec, scl)
		vec.x * scl,
		vec.y * scl,
		vec.z * scl
	};
	return result;
}

// Linear interpolation function
QM_API q_vector3 qmVector3Lerp(q_float value, q_vector3 start, q_vector3 end)
{
	q_vector3 result = {
		start.x + value * (end.x - start.x), // qmFloatLerp(value, start.x, end.x)
		start.y + value * (end.y - start.y), // qmFloatLerp(value, start.y, end.y)
		start.z + value * (end.z - start.z)  // qmFloatLerp(value, start.z, end.z)
	};
	return result;
}

// Cubic hermite interpolation function
QM_API q_vector3 qmVector3CubicHermite(q_float value, q_vector3 left, q_vector3 ltan, q_vector3 right, q_vector3 rtan)
{
	q_float p0 = cbf(value) * 2.0f - sqf(value) * 3.0f + 1.0f;
	q_float p1 = cbf(value) - sqf(value) * 2.0f + value;
	q_float p2 = cbf(value) * -2.0f + sqf(value) * 3.0f;
	q_float p3 = cbf(value) - sqf(value);

	q_vector3 result = {
		p0 * left.x + p1 * ltan.x + p2 * right.x + p3 * rtan.x,
		p0 * left.y + p1 * ltan.y + p2 * right.y + p3 * rtan.y,
		p0 * left.z + p1 * ltan.z + p2 * right.z + p3 * rtan.z,
	};
	return result;
}

// Cross product function
QM_API q_vector3 qmVector3CrossProduct(q_vector3 left, q_vector3 right)
{
	q_vector3 result = {
		left.y * right.z - left.z * right.y,
		left.z * right.x - left.x * right.z,
		left.x * right.y - left.y * right.x
	};
	return result;
}

// Perpendicular function
QM_API q_vector3 qmVector3Perpendicular(q_vector3 vec)
{
	q_float min = fabsf(vec.x);
	q_vector3 axis = {1.0f, 0.0f, 0.0f};
	if (fabsf(vec.y) < min)
	{
		q_vector3 a = {0.0f, 1.0f, 0.0f};
		min = fabsf(vec.y);
		axis = a;
	}
	if (fabsf(vec.z) < min)
	{
		q_vector3 a = {0.0f, 0.0f, 1.0f};
		axis = a;
	}

	q_vector3 result = { // qmVector3CrossProduct(vec, axis)
		vec.y * axis.z - vec.z * axis.y,
		vec.z * axis.x - vec.x * axis.z,
		vec.x * axis.y - vec.y * axis.x
	};
}

// Barycenter function
QM_API q_vector3 qmVector3Barycenter(q_vector3 plane, q_vector3 v1, q_vector3 v2, q_vector3 v3)
{
	q_vector3 s1 = { // qmVector3Subtract(v2, v1)
		v2.x - v1.x,
		v2.y - v1.y,
		v2.z - v1.z
	};
	q_vector3 s2 = { // qmVector3Subtract(v3, v1)
		v3.x - v1.x,
		v3.y - v1.y,
		v3.z - v1.z
	};
	q_vector3 s3 = { // qmVector3Subtract(plane, v1)
		plane.x - v1.x,
		plane.y - v1.y,
		plane.z - v1.z
	};

	q_float fs1 = sqf(s1.x) + sqf(s1.y) + sqf(s1.z);       // qmVector3DistanceSq(s1)
	q_float fs2 = sqf(s2.x) + sqf(s2.y) + sqf(s2.z);       // qmVector3DistanceSq(s2)
	q_float dot = s1.x * s2.x + s1.y * s2.y + s1.z * s2.z; // qmVector3DotProduct(s1, s2)
	q_float dp1 = s1.x * s3.x + s1.y * s3.y + s1.z * s3.z; // qmVector3DotProduct(s1, s3)
	q_float dp2 = s2.x * s3.x + s2.y * s3.y + s2.z * s3.z; // qmVector3DotProduct(s2, s3)

	q_float y = (fs2 * dp1 - dot * dp2) / (fs1 * fs2 - sqf(dot));
	q_float z = (fs1 * dp2 - dot * dp1) / (fs1 * fs2 - sqf(dot));
	q_vector3 result = {
		1.0f - y - z,
		y,
		z
	};
	return result;
}

// Reflection function
QM_API q_vector3 qmVector3Reflect(q_vector3 vec, q_vector3 normal)
{
	q_float dot = vec.x * normal.x + vec.y * normal.y + vec.z * normal.z; // qmVector3DotProduct(vec, normal)

	q_vector3 result = {
		vec.x - normal.x * 2.0f * dot,
		vec.y - normal.y * 2.0f * dot,
		vec.z - normal.z * 2.0f * dot
	};
	return result;
}

// Refraction function
QM_API q_vector3 qmVector3Refract(q_vector3 vec, q_vector3 normal, q_float index)
{
	q_float dot = vec.x * normal.x + vec.y * normal.y + vec.z * normal.z; // qmVector3DotProduct(vec, normal)
	q_float diff = 1.0f - sqf(index) * (1.0f - sqf(dot));
	if (diff < 0)
	{
		return vec;
	}

	q_vector3 result = {
		vec.x * index - normal.x * (dot * index + sqrtf(diff)),
		vec.y * index - normal.y * (dot * index + sqrtf(diff)),
		vec.z * index - normal.z * (dot * index + sqrtf(diff))
	};
	return result;
}

// Projection function
QM_API q_vector3 qmVector3Project(q_vector3 vec, q_vector3 target)
{
	q_float dot = vec.x * target.x + vec.y * target.y + vec.z * target.z; // qmVector3DotProduct(vec, target)
	q_float len = sqf(target.x) + sqf(target.y) + sqf(target.z);          // qmVector3LengthSq(target)
	q_float mag = dot / len;

	q_vector3 result = { // qmVector3Scale(target, mag)
		target.x * mag,
		target.y * mag,
		target.z * mag
	};
	return result;
}

// Rejection function
QM_API q_vector3 qmVector3Reject(q_vector3 vec, q_vector3 target)
{
	q_float dot = vec.x * target.x + vec.y * target.y + vec.z * target.z; // qmVector3DotProduct(vec, target)
	q_float len = sqf(target.x) + sqf(target.y) + sqf(target.z);          // qmVector3LengthSq(target)
	q_float mag = dot / len;

	q_vector3 result = { // qmVector3Subtract(vec, qmVector3Scale(target, mag))
		vec.x - target.x * mag,
		vec.y - target.y * mag,
		vec.z - target.z * mag
	};
	return result;
}

// Rotate by axis function
QM_API q_vector3 qmVector3RotateByAxis(q_vector3 vec, q_vector3 axis, q_float angle)
{
	q_float alen = sqrtf(sqf(axis.x) + sqf(axis.y) + sqf(axis.z)); // qmVector3Length(axis)
	if (alen > 0.0f) // qmVector3DivideScalar(axis, alen)
	{
		axis.x /= alen;
		axis.y /= alen;
		axis.z /= alen;
	}

	angle /= 2.0f;
	q_float a = sinf(angle);
	q_vector3 w = { // qmVector3Scale(axis, a)
		axis.x * a,
		axis.y * a,
		axis.z * a
	};
	a = cosf(angle);

	q_vector3 cross = { // qmVector3CrossProduct(w, vec)
		w.y * vec.z - w.z * vec.y,
		w.z * vec.x - w.x * vec.z,
		w.x * vec.y - w.y * vec.x
	};
	q_vector3 dcross = { // qmVector3CrossProduct(w, cross)
		w.y * cross.z - w.z * cross.y,
		w.z * cross.x - w.x * cross.z,
		w.x * cross.y - w.y * cross.x
	};

	q_vector3 result = {
		cross.x * 2.0f * a + dcross.x * 2.0f,
		cross.y * 2.0f * a + dcross.y * 2.0f,
		cross.z * 2.0f * a + dcross.z * 2.0f
	};
	return result;
}

// Move function
QM_API q_vector3 qmVector3Move(q_vector3 vec, q_vector3 target, q_float dist)
{
	if (dist <= 0.0f)
	{
		return vec;
	}

	q_float cdist = sqrtf(sqf(target.x - vec.x) + sqf(target.y - vec.y) + sqf(target.z - vec.z)); // qmVector3Distance(target, vec)
	if (cdist > dist)
	{
		return vec;
	}

	q_vector3 result = {
		vec.x + dist / cdist * (target.x - vec.x),
		vec.y + dist / cdist * (target.y - vec.y),
		vec.z + dist / cdist * (target.z - vec.z)
	};
	return result;
}

// Length function
QM_API q_float qmVector3Length(q_vector3 vec)
{
	return sqrtf(sqf(vec.x) + sqf(vec.y) + sqf(vec.z));
}

// Squared length function
QM_API q_float qmVector3LengthSq(q_vector3 vec)
{
	return sqf(vec.x) + sqf(vec.y) + sqf(vec.z);
}

// Dot product function
QM_API q_float qmVector3DotProduct(q_vector3 left, q_vector3 right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

// Distance function
QM_API q_float qmVector3Distance(q_vector3 left, q_vector3 right)
{
	return sqrtf(sqf(left.x - right.x) + sqf(left.y - right.y) + sqf(left.z - right.z));
}

// Squared distance function
QM_API q_float qmVector3DistanceSq(q_vector3 left, q_vector3 right)
{
	return sqf(left.x - right.x) + sqf(left.y - right.y) + sqf(left.z - right.z);
}

// Angle function
QM_API q_float qmVector3Angle(q_vector3 left, q_vector3 right)
{
	q_vector3 cross = { // qmVector3CrossProduct(left, right)
		left.y * right.z - left.z * right.y,
		left.z * right.x - left.x * right.z,
		left.x * right.y - left.y * right.x
  };

	q_float len = sqrtf(sqf(cross.x) + sqf(cross.y) + sqf(cross.z));      // qmVector3Length(cross)
	q_float dot = left.x * right.x + left.y * right.y + left.z * right.z; // qmVector3DotProduct(left, right)
	return atan2f(len, dot);
}

// Equal function
QM_API q_bool qmVector3Equal(q_vector3 left, q_vector3 right)
{
	return Q_BOOL(
		equalf(left.x, right.x) &&
		equalf(left.y, right.y) &&
		equalf(left.z, right.z)
	);
}

//// Vector4 functions ////

// Zero vector function
QM_API q_vector4 qmVector4Zero(q_void)
{
	q_vector4 result = {0.0f, 0.0f, 0.0f, 0.0f};
	return result;
}

// One vector function
QM_API q_vector4 qmVector4One(q_void)
{
	q_vector4 result = {1.0f, 1.0f, 1.0f, 1.0f};
	return result;
}

// Add function
QM_API q_vector4 qmVector4Add(q_vector4 left, q_vector4 right)
{
	q_vector4 result = {
		left.x + right.x,
		left.y + right.y,
		left.z + right.z,
		left.w + right.w
	};
	return result;
}

// Scalar add function
QM_API q_vector4 qmVector4AddScalar(q_vector4 vec, q_float scl)
{
	q_vector4 result = {
		vec.x + scl,
		vec.y + scl,
		vec.z + scl,
		vec.w + scl
	};
	return result;
}

// Subtract function
QM_API q_vector4 qmVector4Subtract(q_vector4 left, q_vector4 right)
{
	q_vector4 result = {
		left.x - right.x,
		left.y - right.y,
		left.z - right.z,
		left.w - right.w
	};
	return result;
}

// Scalar subtract function
QM_API q_vector4 qmVector4SubtractScalar(q_vector4 vec, q_float scl)
{
	q_vector4 result = {
		vec.x - scl,
		vec.y - scl,
		vec.z - scl,
		vec.w - scl
	};
	return result;
}

// Multiply function
QM_API q_vector4 qmVector4Multiply(q_vector4 left, q_vector4 right)
{
	q_vector4 result = {
		left.x * right.x,
		left.y * right.y,
		left.z * right.z,
		left.w * right.w
	};
	return result;
}

// Scale function
QM_API q_vector4 qmVector4Scale(q_vector4 vec, q_float scl)
{
	q_vector4 result = {
		vec.x * scl,
		vec.y * scl,
		vec.z * scl,
		vec.w * scl
	};
	return result;
}

// Negate function
QM_API q_vector4 qmVector4Negate(q_vector4 vec)
{
	q_vector4 result = {
		-vec.x,
		-vec.y,
		-vec.z,
		-vec.w
	};
	return result;
}

// Divide function
QM_API q_vector4 qmVector4Divide(q_vector4 left, q_vector4 right)
{
	q_vector4 result = {
		left.x / right.x,
		left.y / right.y,
		left.z / right.z,
		left.w / right.w
	};
	return result;
}

// Scalar divide function
QM_API q_vector4 qmVector4DivideScalar(q_vector4 vec, q_float scl)
{
	q_vector4 result = {
		vec.x / scl,
		vec.y / scl,
		vec.z / scl,
		vec.w / scl
	};
	return result;
}

// Normalize function
QM_API q_vector4 qmVector4Normalize(q_vector4 vec)
{
	q_float length = sqrtf(sqf(vec.x) + sqf(vec.y) + sqf(vec.z) + sqf(vec.w)); // qmVector4Length(vec)
	if (length == 0.0f)
	{
		return vec;
	}

	q_vector4 result = { // qmVector3DivideScale(vec, length)
		vec.x / length,
		vec.y / length,
		vec.z / length,
		vec.w / length
	};
	return result;
}

// Invert function
QM_API q_vector4 qmVector4Invert(q_vector4 vec)
{
	q_vector4 result = {
		1.0f / vec.x,
		1.0f / vec.y,
		1.0f / vec.z,
		1.0f / vec.w
	};
	return result;
}

// Minimum function
QM_API q_vector4 qmVector4Min(q_vector4 left, q_vector4 right)
{
	q_vector4 result = {
		fminf(left.x, right.x),
		fminf(left.y, right.y),
		fminf(left.z, right.z),
		fminf(left.w, right.w)
	};
	return result;
}

// Maximum function
QM_API q_vector4 qmVector4Max(q_vector4 left, q_vector4 right)
{
	q_vector4 result = {
		fmaxf(left.x, right.x),
		fmaxf(left.y, right.y),
		fmaxf(left.z, right.z),
		fmaxf(left.w, right.w)
	};
	return result;
}

// Clamp function
QM_API q_vector4 qmVector4Clamp(q_vector4 vec, q_vector4 min, q_vector4 max)
{
	q_vector4 result = {
		max.x < min.x ? vec.x : fminf(fmaxf(vec.x, min.x), max.x), // qmFloatClamp(vec.x, min.x, max.x)
		max.y < min.y ? vec.y : fminf(fmaxf(vec.y, min.y), max.y), // qmFloatClamp(vec.y, min.y, max.y)
		max.z < min.z ? vec.z : fminf(fmaxf(vec.z, min.z), max.z), // qmFloatClamp(vec.z, min.z, max.z)
		max.w < min.w ? vec.w : fminf(fmaxf(vec.w, min.w), max.w)  // qmFloatClamp(vec.w, min.w, max.w)
	};
	return result;
}

// Linear interpolation function
QM_API q_vector4 qmVector4Lerp(q_float value, q_vector4 start, q_vector4 end)
{
	q_vector4 result = {
		start.x + value * (end.x - start.x), // qmFloatLerp(value, start.x, end.x)
		start.y + value * (end.y - start.y), // qmFloatLerp(value, start.y, end.y)
		start.z + value * (end.z - start.z), // qmFloatLerp(value, start.z, end.z)
		start.w + value * (end.w - start.w)  // qmFloatLerp(value, start.w, end.w)
	};
	return result;
}

// Move function
QM_API q_vector4 qmVector4Move(q_vector4 vec, q_vector4 target, q_float dist)
{
	if (dist <= 0.0f)
	{
		return vec;
	}

	q_float cdist = sqrtf(sqf(target.x - vec.x) + sqf(target.y - vec.y) + sqf(target.z - vec.z) + sqf(target.w - vec.w)); // qmVector4Distance(target, vec)
	if (cdist > dist)
	{
		return vec;
	}

	q_vector4 result = {
		vec.x + dist / cdist * (target.x - vec.x),
		vec.y + dist / cdist * (target.y - vec.y),
		vec.z + dist / cdist * (target.z - vec.z),
		vec.w + dist / cdist * (target.w - vec.w)
	};
	return result;
}

// Length function
QM_API q_float qmVector4Length(q_vector4 vec)
{
	return sqrtf(sqf(vec.x) + sqf(vec.y) + sqf(vec.z) + sqf(vec.w));
}

// Squared length function
QM_API q_float qmVector4LengthSq(q_vector4 vec)
{
	return sqf(vec.x) + sqf(vec.y) + sqf(vec.z) + sqf(vec.w);
}

// Dot product function
QM_API q_float qmVector4DotProduct(q_vector4 left, q_vector4 right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

// Distance function
QM_API q_float qmVector4Distance(q_vector4 left, q_vector4 right)
{
	return sqrtf(sqf(left.x - right.x) + sqf(left.y - right.y) + sqf(left.z - right.z) + sqf(left.w - right.w));
}

// Squared distance function
QM_API q_float qmVector4DistanceSq(q_vector4 left, q_vector4 right)
{
	return sqf(left.x - right.x) + sqf(left.y - right.y) + sqf(left.z - right.z) + sqf(left.w - right.w);
}

// Equal function
QM_API q_bool qmVector4Equal(q_vector4 left, q_vector4 right)
{
	return Q_BOOL(
		equalf(left.x, right.x) &&
		equalf(left.y, right.y) &&
		equalf(left.z, right.z) &&
		equalf(left.w, right.w)
	);
}

//// Matrix22 functions ////

// Zero matrix function
QM_API q_matrix22 qmMatrix22Zero(q_void)
{
	q_matrix22 result = {
		0.0f, 0.0f,
		0.0f, 0.0f
	};
	return result;
}

// One matrix function
QM_API q_matrix22 qmMatrix22One(q_void)
{
	q_matrix22 result = {
		1.0f, 1.0f,
		1.0f, 1.0f
	};
	return result;
}

// Identity matrix function
QM_API q_matrix22 qmMatrix22Identity(q_void)
{
	q_matrix22 result = {
		1.0f, 0.0f,
		0.0f, 1.0f
	};
	return result;
}

// Add function
QM_API q_matrix22 qmMatrix22Add(q_matrix22 left, q_matrix22 right)
{
	q_matrix22 result = {
		left.m0 + right.m0, left.m2 + right.m2,
		left.m1 + right.m1, left.m3 + right.m3
	};
	return result;
}

// Subtract function
QM_API q_matrix22 qmMatrix22Subtract(q_matrix22 left, q_matrix22 right)
{
	q_matrix22 result = {
		left.m0 - right.m0, left.m2 - right.m2,
		left.m1 - right.m1, left.m3 - right.m3
	};
	return result;
}

// Multiply Vector2 function
QM_API q_vector2 qmMatrix22MultiplyVector2(q_matrix22 mat, q_vector2 vec)
{
	q_vector2 result = {
		mat.m0 * vec.x + mat.m2 * vec.y,
		mat.m1 * vec.x + mat.m3 * vec.y
	};
	return result;
}

// Multiply Matrix22 function
QM_API q_matrix22 qmMatrix22MultiplyMatrix22(q_matrix22 left, q_matrix22 right)
{
	q_float m0 = left.m0 * right.m0 + left.m2 * right.m1;
	q_float m1 = left.m1 * right.m0 + left.m3 * right.m1;
	q_float m2 = left.m0 * right.m2 + left.m2 * right.m3;
	q_float m3 = left.m1 * right.m2 + left.m3 * right.m3;

	q_matrix22 result = {
		m0, m2,
		m1, m3
	};
	return result;
}

// Multiply Matrix23 function
QM_API q_matrix23 qmMatrix22MultiplyMatrix23(q_matrix22 left, q_matrix23 right)
{
	q_float m0 = left.m0 * right.m0 + left.m2 * right.m1;
	q_float m1 = left.m1 * right.m0 + left.m3 * right.m1;
	q_float m2 = left.m0 * right.m2 + left.m2 * right.m3;
	q_float m3 = left.m1 * right.m2 + left.m3 * right.m3;
	q_float m4 = left.m0 * right.m4 + left.m2 * right.m5;
	q_float m5 = left.m1 * right.m4 + left.m3 * right.m5;

	q_matrix23 result = {
		m0, m2, m4,
		m1, m3, m5
	};
	return result;
}

// Multiply Matrix24 function
QM_API q_matrix24 qmMatrix22MultiplyMatrix24(q_matrix22 left, q_matrix24 right)
{
	q_float m0 = left.m0 * right.m0 + left.m2 * right.m1;
	q_float m1 = left.m1 * right.m0 + left.m3 * right.m1;
	q_float m2 = left.m0 * right.m2 + left.m2 * right.m3;
	q_float m3 = left.m1 * right.m2 + left.m3 * right.m3;
	q_float m4 = left.m0 * right.m4 + left.m2 * right.m5;
	q_float m5 = left.m1 * right.m4 + left.m3 * right.m5;
	q_float m6 = left.m0 * right.m6 + left.m2 * right.m7;
	q_float m7 = left.m1 * right.m6 + left.m3 * right.m7;

	q_matrix24 result = {
		m0, m2, m4, m6,
		m1, m3, m5, m7
	};
	return result;
}

// Transpose function
QM_API q_matrix22 qmMatrix22Transpose(q_matrix22 mat)
{
	q_matrix22 result = {
		mat.m0, mat.m1,
		mat.m2, mat.m3
	};
	return result;
}

// Inverse function
QM_API q_matrix22 qmMatrix22Inverse(q_matrix22 mat)
{
	q_float det = mat.m0 * mat.m3 - mat.m1 * mat.m2; // qmMatrix22Determinant(mat)
	q_float inv = 1 / det;

	q_matrix22 result = {
		mat.m3 * inv, -mat.m2 * inv,
		-mat.m1 * inv, mat.m0 * inv
	};
	return result;
}

// Determinant function
QM_API q_float qmMatrix22Determinant(q_matrix22 mat)
{
	return mat.m0 * mat.m3 - mat.m1 * mat.m2;
}

// Trace function
QM_API q_float qmMatrix22Trace(q_matrix22 mat)
{
	return mat.m0 + mat.m3;
}

// Equal function
QM_API q_bool qmMatrix22Equal(q_matrix22 left, q_matrix22 right)
{
	return Q_BOOL(
		equalf(left.m0, right.m0) &&
		equalf(left.m1, right.m1) &&
		equalf(left.m2, right.m2) &&
		equalf(left.m3, right.m3)
	);
}

//// Matrix23 functions ////

// Zero matrix function
QM_API q_matrix23 qmMatrix23Zero(q_void)
{
	q_matrix23 result = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};
	return result;
}

// One matrix function
QM_API q_matrix23 qmMatrix23One(q_void)
{
	q_matrix23 result = {
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};
	return result;
}

// Add function
QM_API q_matrix23 qmMatrix23Add(q_matrix23 left, q_matrix23 right)
{
	q_matrix23 result = {
		left.m0 + right.m0, left.m2 + right.m2, left.m4 + right.m4,
		left.m1 + right.m1, left.m3 + right.m3, left.m5 + right.m5
	};
	return result;
}

// Subtract function
QM_API q_matrix23 qmMatrix23Subtract(q_matrix23 left, q_matrix23 right)
{
	q_matrix23 result = {
		left.m0 - right.m0, left.m2 - right.m2, left.m4 - right.m4,
		left.m1 - right.m1, left.m3 - right.m3, left.m5 - right.m5
	};
	return result;
}

// Multiply Vector3 function
QM_API q_vector2 qmMatrix23MultiplyVector3(q_matrix23 mat, q_vector3 vec)
{
	q_vector2 result = {
		mat.m0 * vec.x + mat.m2 * vec.y + mat.m4 * vec.z,
		mat.m1 * vec.x + mat.m3 * vec.y + mat.m5 * vec.z
	};
	return result;
}

// Multiply Matrix32 function
QM_API q_matrix22 qmMatrix23MultiplyMatrix32(q_matrix23 left, q_matrix32 right)
{
	q_float m0 = left.m0 * right.m0 + left.m2 * right.m1 + left.m4 * right.m2;
	q_float m1 = left.m1 * right.m0 + left.m3 * right.m1 + left.m5 * right.m2;
	q_float m2 = left.m0 * right.m3 + left.m2 * right.m4 + left.m4 * right.m5;
	q_float m3 = left.m1 * right.m3 + left.m3 * right.m4 + left.m5 * right.m5;

	q_matrix22 result = {
		m0, m2,
		m1, m3
	};
	return result;
}

// Multiply Matrix33 function
QM_API q_matrix23 qmMatrix23MultiplyMatrix33(q_matrix23 left, q_matrix33 right)
{
	q_float m0 = left.m0 * right.m0 + left.m2 * right.m1 + left.m4 * right.m2;
	q_float m1 = left.m1 * right.m0 + left.m3 * right.m1 + left.m5 * right.m2;
	q_float m2 = left.m0 * right.m3 + left.m2 * right.m4 + left.m4 * right.m5;
	q_float m3 = left.m1 * right.m3 + left.m3 * right.m4 + left.m5 * right.m5;
	q_float m4 = left.m0 * right.m6 + left.m2 * right.m7 + left.m4 * right.m8;
	q_float m5 = left.m1 * right.m6 + left.m3 * right.m7 + left.m5 * right.m8;

	q_matrix23 result = {
		m0, m2, m4,
		m1, m3, m5
	};
	return result;
}

// Multiply Matrix34 function
QM_API q_matrix24 qmMatrix23MultiplyMatrix34(q_matrix23 left, q_matrix34 right)
{
	q_float m0 = left.m0 * right.m0 + left.m2 * right.m1 + left.m4 * right.m2;
	q_float m1 = left.m1 * right.m0 + left.m3 * right.m1 + left.m5 * right.m2;
	q_float m2 = left.m0 * right.m3 + left.m2 * right.m4 + left.m4 * right.m5;
	q_float m3 = left.m1 * right.m3 + left.m3 * right.m4 + left.m5 * right.m5;
	q_float m4 = left.m0 * right.m6 + left.m2 * right.m7 + left.m4 * right.m8;
	q_float m5 = left.m1 * right.m6 + left.m3 * right.m7 + left.m5 * right.m8;
	q_float m6 = left.m0 * right.m9 + left.m2 * right.m10 + left.m4 * right.m11;
	q_float m7 = left.m1 * right.m9 + left.m3 * right.m10 + left.m5 * right.m11;

	q_matrix24 result = {
		m0, m2, m4, m6,
		m1, m3, m5, m7
	};
	return result;
}

// Transpose function
QM_API q_matrix32 qmMatrix23Transpose(q_matrix23 mat)
{
	q_matrix32 result = {
		mat.m0, mat.m1,
		mat.m2, mat.m3,
		mat.m4, mat.m5
	};
	return result;
}

// Equal function
QM_API q_bool qmMatrix23Equal(q_matrix23 left, q_matrix23 right)
{
	return Q_BOOL(
		equalf(left.m0, right.m0) &&
		equalf(left.m1, right.m1) &&
		equalf(left.m2, right.m2) &&
		equalf(left.m3, right.m3) &&
		equalf(left.m4, right.m4) &&
		equalf(left.m5, right.m5)
	);
}

//// Matrix24 functions ////

// Zero matrix function
QM_API q_matrix24 qmMatrix24Zero(q_void)
{
	q_matrix24 result = {
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	};
	return result;
}

// One matrix function
QM_API q_matrix24 qmMatrix24One(q_void)
{
	q_matrix24 result = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};
	return result;
}

// Add function
QM_API q_matrix24 qmMatrix24Add(q_matrix24 left, q_matrix24 right)
{
	q_matrix24 result = {
		left.m0 + right.m0, left.m2 + right.m2, left.m4 + right.m4, left.m6 + right.m6,
		left.m1 + right.m1, left.m3 + right.m3, left.m5 + right.m5, left.m7 + right.m7
	};
	return result;
}

// Subtract function
QM_API q_matrix24 qmMatrix24Subtract(q_matrix24 left, q_matrix24 right)
{
	q_matrix24 result = {
		left.m0 - right.m0, left.m2 - right.m2, left.m4 - right.m4, left.m6 - right.m6,
		left.m1 - right.m1, left.m3 - right.m3, left.m5 - right.m5, left.m7 - right.m7
	};
	return result;
}

// Multiply Vector4 function
QM_API q_vector2 qmMatrix24MultiplyVector4(q_matrix24 mat, q_vector4 vec)
{
	q_vector2 result = {
		mat.m0 * vec.x + mat.m2 * vec.y + mat.m4 * vec.z + mat.m6 * vec.w,
		mat.m1 * vec.x + mat.m3 * vec.y + mat.m5 * vec.z + mat.m7 * vec.w
	};
	return result;
}

// Multiply Matrix42 function
QM_API q_matrix22 qmMatrix24MultiplyMatrix42(q_matrix24 left, q_matrix42 right)
{
	q_float m0 = left.m0 * right.m0 + left.m2 * right.m1 + left.m4 * right.m2 + left.m6 * right.m3;
	q_float m1 = left.m1 * right.m0 + left.m3 * right.m1 + left.m5 * right.m2 + left.m7 * right.m3;
	q_float m2 = left.m0 * right.m4 + left.m2 * right.m5 + left.m4 * right.m6 + left.m6 * right.m7;
	q_float m3 = left.m1 * right.m4 + left.m3 * right.m5 + left.m5 * right.m6 + left.m7 * right.m7;

	q_matrix22 result = {
		m0, m2,
		m1, m3
	};
	return result;
}

// Multiply Matrix43 function
QM_API q_matrix23 qmMatrix24MultiplyMatrix43(q_matrix24 left, q_matrix43 right)
{
	q_float m0 = left.m0 * right.m0 + left.m2 * right.m1 + left.m4 * right.m2 + left.m6 * right.m3;
	q_float m1 = left.m1 * right.m0 + left.m3 * right.m1 + left.m5 * right.m2 + left.m7 * right.m3;
	q_float m2 = left.m0 * right.m4 + left.m2 * right.m5 + left.m4 * right.m6 + left.m6 * right.m7;
	q_float m3 = left.m1 * right.m4 + left.m3 * right.m5 + left.m5 * right.m6 + left.m7 * right.m7;
	q_float m4 = left.m0 * right.m8 + left.m2 * right.m9 + left.m4 * right.m10 + left.m6 * right.m11;
	q_float m5 = left.m1 * right.m8 + left.m3 * right.m9 + left.m5 * right.m10 + left.m7 * right.m11;

	q_matrix23 result = {
		m0, m2, m4,
		m1, m3, m5
	};
	return result;
}

// Multiply Matrix44 function
QM_API q_matrix24 qmMatrix24MultiplyMatrix44(q_matrix24 left, q_matrix44 right)
{
	q_float m0 = left.m0 * right.m0 + left.m2 * right.m1 + left.m4 * right.m2 + left.m6 * right.m3;
	q_float m1 = left.m1 * right.m0 + left.m3 * right.m1 + left.m5 * right.m2 + left.m7 * right.m3;
	q_float m2 = left.m0 * right.m4 + left.m2 * right.m5 + left.m4 * right.m6 + left.m6 * right.m7;
	q_float m3 = left.m1 * right.m4 + left.m3 * right.m5 + left.m5 * right.m6 + left.m7 * right.m7;
	q_float m4 = left.m0 * right.m8 + left.m2 * right.m9 + left.m4 * right.m10 + left.m6 * right.m11;
	q_float m5 = left.m1 * right.m8 + left.m3 * right.m9 + left.m5 * right.m10 + left.m7 * right.m11;
	q_float m6 = left.m0 * right.m12 + left.m2 * right.m13 + left.m4 * right.m14 + left.m6 * right.m15;
	q_float m7 = left.m1 * right.m12 + left.m3 * right.m13 + left.m5 * right.m14 + left.m7 * right.m15;

	q_matrix24 result = {
		m0, m2, m4, m6,
		m1, m3, m5, m7
	};
	return result;
}

// Transpose function
QM_API q_matrix42 qmMatrix24Transpose(q_matrix24 mat)
{
	q_matrix42 result = {
		mat.m0, mat.m1,
		mat.m2, mat.m3,
		mat.m4, mat.m5,
		mat.m6, mat.m7
	};
	return result;
}

// Equal function
QM_API q_bool qmMatrix24Equal(q_matrix24 left, q_matrix24 right)
{
	return Q_BOOL(
		equalf(left.m0, right.m0) &&
		equalf(left.m1, right.m1) &&
		equalf(left.m2, right.m2) &&
		equalf(left.m3, right.m3) &&
		equalf(left.m4, right.m4) &&
		equalf(left.m5, right.m5) &&
		equalf(left.m6, right.m6) &&
		equalf(left.m7, right.m7)
	);
}

//// Matrix32 functions ////

// Zero matrix function
QM_API q_matrix32 qmMatrix32Zero(q_void)
{
	q_matrix32 result = {
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f
	};
	return result;
}

// One matrix function
QM_API q_matrix32 qmMatrix32One(q_void)
{
	q_matrix32 result = {
		1.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 1.0f
	};
	return result;
}

// Add function
QM_API q_matrix32 qmMatrix32Add(q_matrix32 left, q_matrix32 right)
{
	q_matrix32 result = {
		left.m0 + right.m0, left.m3 + right.m3,
		left.m1 + right.m1, left.m4 + right.m4,
		left.m2 + right.m2, left.m5 + right.m5
	};
	return result;
}

// Subtract function
QM_API q_matrix32 qmMatrix32Subtract(q_matrix32 left, q_matrix32 right)
{
	q_matrix32 result = {
		left.m0 - right.m0, left.m3 - right.m3,
		left.m1 - right.m1, left.m4 - right.m4,
		left.m2 - right.m2, left.m5 - right.m5
	};
	return result;
}

// Multiply Vector2 function
QM_API q_vector3 qmMatrix32MultiplyVector2(q_matrix32 mat, q_vector2 vec)
{
	q_vector3 result = {
		mat.m0 * vec.x + mat.m3 * vec.y,
		mat.m1 * vec.x + mat.m4 * vec.y,
		mat.m2 * vec.x + mat.m5 * vec.y
	};
	return result;
}

// Multiply Matrix22 function
QM_API q_matrix32 qmMatrix32MultiplyMatrix22(q_matrix32 left, q_matrix22 right)
{
	q_float m0 = left.m0 * right.m0 + left.m3 * right.m1;
	q_float m1 = left.m1 * right.m0 + left.m4 * right.m1;
	q_float m2 = left.m2 * right.m0 + left.m5 * right.m1;
	q_float m3 = left.m0 * right.m2 + left.m3 * right.m3;
	q_float m4 = left.m1 * right.m2 + left.m4 * right.m3;
	q_float m5 = left.m2 * right.m2 + left.m5 * right.m3;

	q_matrix32 result = {
		m0, m3,
		m1, m4,
		m2, m5
	};
	return result;
}

// Multiply Matrix23 function
QM_API q_matrix33 qmMatrix32MultiplyMatrix23(q_matrix32 left, q_matrix23 right)
{
	q_float m0 = left.m0 * right.m0 + left.m3 * right.m1;
	q_float m1 = left.m1 * right.m0 + left.m4 * right.m1;
	q_float m2 = left.m2 * right.m0 + left.m5 * right.m1;
	q_float m3 = left.m0 * right.m2 + left.m3 * right.m3;
	q_float m4 = left.m1 * right.m2 + left.m4 * right.m3;
	q_float m5 = left.m2 * right.m2 + left.m5 * right.m3;
	q_float m6 = left.m0 * right.m4 + left.m3 * right.m5;
	q_float m7 = left.m1 * right.m4 + left.m4 * right.m5;
	q_float m8 = left.m2 * right.m4 + left.m5 * right.m5;

	q_matrix33 result = {
		m0, m3, m6,
		m1, m4, m7,
		m2, m5, m8
	};
	return result;
}

// Multiply Matrix24 function
QM_API q_matrix34 qmMatrix32MultiplyMatrix24(q_matrix32 left, q_matrix24 right)
{
	q_float m0 = left.m0 * right.m0 + left.m3 * right.m1;
	q_float m1 = left.m1 * right.m0 + left.m4 * right.m1;
	q_float m2 = left.m2 * right.m0 + left.m5 * right.m1;
	q_float m3 = left.m0 * right.m2 + left.m3 * right.m3;
	q_float m4 = left.m1 * right.m2 + left.m4 * right.m3;
	q_float m5 = left.m2 * right.m2 + left.m5 * right.m3;
	q_float m6 = left.m0 * right.m4 + left.m3 * right.m5;
	q_float m7 = left.m1 * right.m4 + left.m4 * right.m5;
	q_float m8 = left.m2 * right.m4 + left.m5 * right.m5;
	q_float m9 = left.m0 * right.m6 + left.m3 * right.m7;
	q_float m10 = left.m1 * right.m6 + left.m4 * right.m7;
	q_float m11 = left.m2 * right.m6 + left.m5 * right.m7;

	q_matrix34 result = {
		m0, m3, m6, m9,
		m1, m4, m7, m10,
		m2, m5, m8, m11
	};
	return result;
}

// Transpose function
QM_API q_matrix23 qmMatrix32Transpose(q_matrix32 mat)
{
	q_matrix23 result = {
		mat.m0, mat.m1, mat.m2,
		mat.m3, mat.m4, mat.m5
	};
	return result;
}

// Equal function
QM_API q_bool qmMatrix32Equal(q_matrix32 left, q_matrix32 right)
{
	return Q_BOOL(
		equalf(left.m0, right.m0) &&
		equalf(left.m1, right.m1) &&
		equalf(left.m2, right.m2) &&
		equalf(left.m3, right.m3) &&
		equalf(left.m4, right.m4) &&
		equalf(left.m5, right.m5)
	);
}

//// Matrix33 functions ////

// Zero matrix function
QM_API q_matrix33 qmMatrix33Zero(q_void)
{
	q_matrix33 result = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};
	return result;
}

// One matrix function
QM_API q_matrix33 qmMatrix33One(q_void)
{
	q_matrix33 result = {
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};
	return result;
}

// Identity matrix function
QM_API q_matrix33 qmMatrix33Identity(q_void)
{
	q_matrix33 result = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	return result;
}

// Add function
QM_API q_matrix33 qmMatrix33Add(q_matrix33 left, q_matrix33 right)
{
	q_matrix33 result = {
		left.m0 + right.m0, left.m3 + right.m3, left.m6 + right.m6,
		left.m1 + right.m1, left.m4 + right.m4, left.m7 + right.m7,
		left.m2 + right.m2, left.m5 + right.m5, left.m8 + right.m8
	};
	return result;
}

// Subtract function
QM_API q_matrix33 qmMatrix33Subtract(q_matrix33 left, q_matrix33 right)
{
	q_matrix33 result = {
		left.m0 - right.m0, left.m3 - right.m3, left.m6 - right.m6,
		left.m1 - right.m1, left.m4 - right.m4, left.m7 - right.m7,
		left.m2 - right.m2, left.m5 - right.m5, left.m8 - right.m8
	};
	return result;
}

// Multiply Vector3 function
QM_API q_vector3 qmMatrix33MultiplyVector3(q_matrix33 mat, q_vector3 vec)
{
	q_vector3 result = {
		mat.m0 * vec.x + mat.m3 * vec.y + mat.m6 * vec.z,
		mat.m1 * vec.x + mat.m4 * vec.y + mat.m7 * vec.z,
		mat.m2 * vec.x + mat.m5 * vec.y + mat.m8 * vec.z
	};
	return result;
}

// Multiply Matrix32 function
QM_API q_matrix32 qmMatrix33MultiplyMatrix32(q_matrix33 left, q_matrix32 right)
{
	q_float m0 = left.m0 * right.m0 + left.m3 * right.m1 + left.m6 * right.m2;
	q_float m1 = left.m1 * right.m0 + left.m4 * right.m1 + left.m7 * right.m2;
	q_float m2 = left.m2 * right.m0 + left.m5 * right.m1 + left.m8 * right.m2;
	q_float m3 = left.m0 * right.m3 + left.m3 * right.m4 + left.m6 * right.m5;
	q_float m4 = left.m1 * right.m3 + left.m4 * right.m4 + left.m7 * right.m5;
	q_float m5 = left.m2 * right.m3 + left.m5 * right.m4 + left.m8 * right.m5;

	q_matrix32 result = {
		m0, m3,
		m1, m4,
		m2, m5
	};
	return result;
}

// Multiply Matrix33 function
QM_API q_matrix33 qmMatrix33MultiplyMatrix33(q_matrix33 left, q_matrix33 right)
{
	q_float m0 = left.m0 * right.m0 + left.m3 * right.m1 + left.m6 * right.m2;
	q_float m1 = left.m1 * right.m0 + left.m4 * right.m1 + left.m7 * right.m2;
	q_float m2 = left.m2 * right.m0 + left.m5 * right.m1 + left.m8 * right.m2;
	q_float m3 = left.m0 * right.m3 + left.m3 * right.m4 + left.m6 * right.m5;
	q_float m4 = left.m1 * right.m3 + left.m4 * right.m4 + left.m7 * right.m5;
	q_float m5 = left.m2 * right.m3 + left.m5 * right.m4 + left.m8 * right.m5;
	q_float m6 = left.m0 * right.m6 + left.m3 * right.m7 + left.m6 * right.m8;
	q_float m7 = left.m1 * right.m6 + left.m4 * right.m7 + left.m7 * right.m8;
	q_float m8 = left.m2 * right.m6 + left.m5 * right.m7 + left.m8 * right.m8;

	q_matrix33 result = {
		m0, m3, m6,
		m1, m4, m7,
		m2, m5, m8
	};
	return result;
}

// Multiply Matrix34 function
QM_API q_matrix34 qmMatrix33MultiplyMatrix34(q_matrix33 left, q_matrix34 right)
{
	q_float m0 = left.m0 * right.m0 + left.m3 * right.m1 + left.m6 * right.m2;
	q_float m1 = left.m1 * right.m0 + left.m4 * right.m1 + left.m7 * right.m2;
	q_float m2 = left.m2 * right.m0 + left.m5 * right.m1 + left.m8 * right.m2;
	q_float m3 = left.m0 * right.m3 + left.m3 * right.m4 + left.m6 * right.m5;
	q_float m4 = left.m1 * right.m3 + left.m4 * right.m4 + left.m7 * right.m5;
	q_float m5 = left.m2 * right.m3 + left.m5 * right.m4 + left.m8 * right.m5;
	q_float m6 = left.m0 * right.m6 + left.m3 * right.m7 + left.m6 * right.m8;
	q_float m7 = left.m1 * right.m6 + left.m4 * right.m7 + left.m7 * right.m8;
	q_float m8 = left.m2 * right.m6 + left.m5 * right.m7 + left.m8 * right.m8;
	q_float m9 = left.m0 * right.m9 + left.m3 * right.m10 + left.m6 * right.m11;
	q_float m10 = left.m1 * right.m9 + left.m4 * right.m10 + left.m7 * right.m11;
	q_float m11 = left.m2 * right.m9 + left.m5 * right.m10 + left.m8 * right.m11;

	q_matrix34 result = {
		m0, m3, m6, m9,
		m1, m4, m7, m10,
		m2, m5, m8, m11
	};
	return result;
}

// Transpose function
QM_API q_matrix33 qmMatrix33Transpose(q_matrix33 mat)
{
	q_matrix33 result = {
		mat.m0, mat.m1, mat.m2,
		mat.m3, mat.m4, mat.m5,
		mat.m6, mat.m7, mat.m8
	};
	return result;
}

// Inverse function
QM_API q_matrix33 qmMatrix33Inverse(q_matrix33 mat)
{
	q_float det = ( // qmMatrix33Determinant(mat)
		mat.m0 * mat.m4 * mat.m8 +
		mat.m1 * mat.m5 * mat.m6 +
		mat.m2 * mat.m3 * mat.m7 -
		mat.m0 * mat.m5 * mat.m7 -
		mat.m1 * mat.m3 * mat.m8 -
		mat.m2 * mat.m4 * mat.m6
	);
	q_float inv = 1 / det;

	q_float m0 = (mat.m4 * mat.m8 - mat.m5 * mat.m7) * inv;
	q_float m1 = (mat.m2 * mat.m7 - mat.m1 * mat.m8) * inv;
	q_float m2 = (mat.m1 * mat.m5 - mat.m2 * mat.m4) * inv;
	q_float m3 = (mat.m5 * mat.m6 - mat.m3 * mat.m8) * inv;
	q_float m4 = (mat.m0 * mat.m8 - mat.m2 * mat.m6) * inv;
	q_float m5 = (mat.m2 * mat.m3 - mat.m0 * mat.m5) * inv;
	q_float m6 = (mat.m3 * mat.m7 - mat.m4 * mat.m6) * inv;
	q_float m7 = (mat.m1 * mat.m6 - mat.m0 * mat.m7) * inv;
	q_float m8 = (mat.m0 * mat.m4 - mat.m1 * mat.m3) * inv;

	q_matrix33 result = {
		m0, m3, m6,
		m1, m4, m7,
		m2, m5, m8
	};
	return result;
}

// Determinant function
QM_API q_float qmMatrix33Determinant(q_matrix33 mat)
{
	return (
		mat.m0 * mat.m4 * mat.m8 +
		mat.m1 * mat.m5 * mat.m6 +
		mat.m2 * mat.m3 * mat.m7 -
		mat.m0 * mat.m5 * mat.m7 -
		mat.m1 * mat.m3 * mat.m8 -
		mat.m2 * mat.m4 * mat.m6
	);
}

// Trace function
QM_API q_float qmMatrix33Trace(q_matrix33 mat)
{
	return mat.m0 + mat.m4 + mat.m8;
}

// Equal function
QM_API q_bool qmMatrix33Equal(q_matrix33 left, q_matrix33 right)
{
	return Q_BOOL(
		equalf(left.m0, right.m0) &&
		equalf(left.m1, right.m1) &&
		equalf(left.m2, right.m2) &&
		equalf(left.m3, right.m3) &&
		equalf(left.m4, right.m4) &&
		equalf(left.m5, right.m5) &&
		equalf(left.m6, right.m6) &&
		equalf(left.m7, right.m7) &&
		equalf(left.m8, right.m8)
	);
}

//// Matrix34 functions ////

// Zero matrix function
QM_API q_matrix34 qmMatrix34Zero(q_void)
{
	q_matrix34 result = {
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	};
	return result;
}

// One matrix function
QM_API q_matrix34 qmMatrix34One(q_void)
{
	q_matrix34 result = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};
	return result;
}

// Add function
QM_API q_matrix34 qmMatrix34Add(q_matrix34 left, q_matrix34 right)
{
	q_matrix34 result = {
		left.m0 + right.m0, left.m3 + right.m3, left.m6 + right.m6, left.m9 + right.m9,
		left.m1 + right.m1, left.m4 + right.m4, left.m7 + right.m7, left.m10 + right.m10,
		left.m2 + right.m2, left.m5 + right.m5, left.m8 + right.m8, left.m11 + right.m11
	};
	return result;
}

// Subtract function
QM_API q_matrix34 qmMatrix34Subtract(q_matrix34 left, q_matrix34 right)
{
	q_matrix34 result = {
		left.m0 - right.m0, left.m3 - right.m3, left.m6 - right.m6, left.m9 - right.m9,
		left.m1 - right.m1, left.m4 - right.m4, left.m7 - right.m7, left.m10 - right.m10,
		left.m2 - right.m2, left.m5 - right.m5, left.m8 - right.m8, left.m11 - right.m11
	};
	return result;
}

// Multiply Vector4 function
QM_API q_vector3 qmMatrix34MultiplyVector4(q_matrix34 mat, q_vector4 vec)
{
	q_vector3 result = {
		mat.m0 * vec.x + mat.m3 * vec.y + mat.m6 * vec.z + mat.m9 * vec.w,
		mat.m1 * vec.x + mat.m4 * vec.y + mat.m7 * vec.z + mat.m10 * vec.w,
		mat.m2 * vec.x + mat.m5 * vec.y + mat.m8 * vec.z + mat.m11 * vec.w
	};
	return result;
}

// Multiply Matrix42 function
QM_API q_matrix32 qmMatrix34MultiplyMatrix42(q_matrix34 left, q_matrix42 right)
{
	q_float m0 = left.m0 * right.m0 + left.m3 * right.m1 + left.m6 * right.m2 + left.m9 * right.m3;
	q_float m1 = left.m1 * right.m0 + left.m4 * right.m1 + left.m7 * right.m2 + left.m10 * right.m3;
	q_float m2 = left.m2 * right.m0 + left.m5 * right.m1 + left.m8 * right.m2 + left.m11 * right.m3;
	q_float m3 = left.m0 * right.m4 + left.m3 * right.m5 + left.m6 * right.m6 + left.m9 * right.m7;
	q_float m4 = left.m1 * right.m4 + left.m4 * right.m5 + left.m7 * right.m6 + left.m10 * right.m7;
	q_float m5 = left.m2 * right.m4 + left.m5 * right.m5 + left.m8 * right.m6 + left.m11 * right.m7;

	q_matrix32 result = {
		m0, m3,
		m1, m4,
		m2, m5
	};
	return result;
}

// Multiply Matrix43 function
QM_API q_matrix33 qmMatrix34MultiplyMatrix43(q_matrix34 left, q_matrix43 right)
{
	q_float m0 = left.m0 * right.m0 + left.m3 * right.m1 + left.m6 * right.m2 + left.m9 * right.m3;
	q_float m1 = left.m1 * right.m0 + left.m4 * right.m1 + left.m7 * right.m2 + left.m10 * right.m3;
	q_float m2 = left.m2 * right.m0 + left.m5 * right.m1 + left.m8 * right.m2 + left.m11 * right.m3;
	q_float m3 = left.m0 * right.m4 + left.m3 * right.m5 + left.m6 * right.m6 + left.m9 * right.m7;
	q_float m4 = left.m1 * right.m4 + left.m4 * right.m5 + left.m7 * right.m6 + left.m10 * right.m7;
	q_float m5 = left.m2 * right.m4 + left.m5 * right.m5 + left.m8 * right.m6 + left.m11 * right.m7;
	q_float m6 = left.m0 * right.m8 + left.m3 * right.m9 + left.m6 * right.m10 + left.m9 * right.m11;
	q_float m7 = left.m1 * right.m8 + left.m4 * right.m9 + left.m7 * right.m10 + left.m10 * right.m11;
	q_float m8 = left.m2 * right.m8 + left.m5 * right.m9 + left.m8 * right.m10 + left.m11 * right.m11;

	q_matrix33 result = {
		m0, m3, m6,
		m1, m4, m7,
		m2, m5, m8
	};
	return result;
}

// Multiply Matrix44 function
QM_API q_matrix34 qmMatrix34MultiplyMatrix44(q_matrix34 left, q_matrix44 right)
{
	q_float m0 = left.m0 * right.m0 + left.m3 * right.m1 + left.m6 * right.m2 + left.m9 * right.m3;
	q_float m1 = left.m1 * right.m0 + left.m4 * right.m1 + left.m7 * right.m2 + left.m10 * right.m3;
	q_float m2 = left.m2 * right.m0 + left.m5 * right.m1 + left.m8 * right.m2 + left.m11 * right.m3;
	q_float m3 = left.m0 * right.m4 + left.m3 * right.m5 + left.m6 * right.m6 + left.m9 * right.m7;
	q_float m4 = left.m1 * right.m4 + left.m4 * right.m5 + left.m7 * right.m6 + left.m10 * right.m7;
	q_float m5 = left.m2 * right.m4 + left.m5 * right.m5 + left.m8 * right.m6 + left.m11 * right.m7;
	q_float m6 = left.m0 * right.m8 + left.m3 * right.m9 + left.m6 * right.m10 + left.m9 * right.m11;
	q_float m7 = left.m1 * right.m8 + left.m4 * right.m9 + left.m7 * right.m10 + left.m10 * right.m11;
	q_float m8 = left.m2 * right.m8 + left.m5 * right.m9 + left.m8 * right.m10 + left.m11 * right.m11;
	q_float m9 = left.m0 * right.m12 + left.m3 * right.m13 + left.m6 * right.m14 + left.m9 * right.m15;
	q_float m10 = left.m1 * right.m12 + left.m4 * right.m13 + left.m7 * right.m14 + left.m10 * right.m15;
	q_float m11 = left.m2 * right.m12 + left.m5 * right.m13 + left.m8 * right.m14 + left.m11 * right.m15;

	q_matrix34 result = {
		m0, m3, m6, m9,
		m1, m4, m7, m10,
		m2, m5, m8, m11
	};
	return result;
}

// Transpose function
QM_API q_matrix43 qmMatrix34Transpose(q_matrix34 mat)
{
	q_matrix43 result = {
		mat.m0, mat.m1, mat.m2,
		mat.m3, mat.m4, mat.m5,
		mat.m6, mat.m7, mat.m8,
		mat.m9, mat.m10, mat.m11
	};
	return result;
}

// Equal function
QM_API q_bool qmMatrix34Equal(q_matrix34 left, q_matrix34 right)
{
	return Q_BOOL(
		equalf(left.m0, right.m0) &&
		equalf(left.m1, right.m1) &&
		equalf(left.m2, right.m2) &&
		equalf(left.m3, right.m3) &&
		equalf(left.m4, right.m4) &&
		equalf(left.m5, right.m5) &&
		equalf(left.m6, right.m6) &&
		equalf(left.m7, right.m7) &&
		equalf(left.m8, right.m8) &&
		equalf(left.m9, right.m9) &&
		equalf(left.m10, right.m10) &&
		equalf(left.m11, right.m11)
	);
}

//// Matrix42 functions ////

// Zero matrix function
QM_API q_matrix42 qmMatrix42Zero(q_void)
{
	q_matrix42 result = {
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f
	};
	return result;
}

// One matrix function
QM_API q_matrix42 qmMatrix42One(q_void)
{
	q_matrix42 result = {
		1.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 1.0f
	};
	return result;
}

// Add function
QM_API q_matrix42 qmMatrix42Add(q_matrix42 left, q_matrix42 right)
{
	q_matrix42 result = {
		left.m0 + right.m0, left.m4 + right.m4,
		left.m1 + right.m1, left.m5 + right.m5,
		left.m2 + right.m2, left.m6 + right.m6,
        left.m3 + right.m3, left.m7 + right.m7
	};
	return result;
}

// Subtract function
QM_API q_matrix42 qmMatrix42Subtract(q_matrix42 left, q_matrix42 right)
{
	q_matrix42 result = {
		left.m0 - right.m0, left.m4 - right.m4,
		left.m1 - right.m1, left.m5 - right.m5,
		left.m2 - right.m2, left.m6 - right.m6,
		left.m3 - right.m3, left.m7 - right.m7
	};
	return result;
}

// Multiply Vector2 function
QM_API q_vector4 qmMatrix42MultiplyVector2(q_matrix42 mat, q_vector2 vec)
{
	q_vector4 result = {
		mat.m0 * vec.x + mat.m4 * vec.y,
        mat.m1 * vec.x + mat.m5 * vec.y,
        mat.m2 * vec.x + mat.m6 * vec.y,
        mat.m3 * vec.x + mat.m7 * vec.y
	};
	return result;
}

// Multiply Matrix22 function
QM_API q_matrix42 qmMatrix42MultiplyMatrix22(q_matrix42 left, q_matrix22 right)
{
	q_float m0 = left.m0 * right.m0 + left.m4 * right.m1;
	q_float m1 = left.m1 * right.m0 + left.m5 * right.m1;
	q_float m2 = left.m2 * right.m0 + left.m6 * right.m1;
	q_float m3 = left.m3 * right.m0 + left.m7 * right.m1;
	q_float m4 = left.m0 * right.m2 + left.m4 * right.m3;
	q_float m5 = left.m1 * right.m2 + left.m5 * right.m3;
	q_float m6 = left.m2 * right.m2 + left.m6 * right.m3;
	q_float m7 = left.m3 * right.m2 + left.m7 * right.m3;

	q_matrix42 result = {
		m0, m4,
		m1, m5,
		m2, m6,
		m3, m7
	};
	return result;
}

// Multiply Matrix23 function
QM_API q_matrix43 qmMatrix42MultiplyMatrix23(q_matrix42 left, q_matrix23 right)
{
	q_float m0 = left.m0 * right.m0 + left.m4 * right.m1;
	q_float m1 = left.m1 * right.m0 + left.m5 * right.m1;
	q_float m2 = left.m2 * right.m0 + left.m6 * right.m1;
	q_float m3 = left.m3 * right.m0 + left.m7 * right.m1;
	q_float m4 = left.m0 * right.m2 + left.m4 * right.m3;
	q_float m5 = left.m1 * right.m2 + left.m5 * right.m3;
	q_float m6 = left.m2 * right.m2 + left.m6 * right.m3;
	q_float m7 = left.m3 * right.m2 + left.m7 * right.m3;
	q_float m8 = left.m0 * right.m4 + left.m4 * right.m5;
	q_float m9 = left.m1 * right.m4 + left.m5 * right.m5;
	q_float m10 = left.m2 * right.m4 + left.m6 * right.m5;
	q_float m11 = left.m3 * right.m4 + left.m7 * right.m5;

	q_matrix43 result = {
		m0, m4, m8,
		m1, m5, m9,
		m2, m6, m10,
        m3, m7, m11
	};
	return result;
}

// Multiply Matrix24 function
QM_API q_matrix44 qmMatrix42MultiplyMatrix24(q_matrix42 left, q_matrix24 right)
{
	q_float m0 = left.m0 * right.m0 + left.m4 * right.m1;
	q_float m1 = left.m1 * right.m0 + left.m5 * right.m1;
	q_float m2 = left.m2 * right.m0 + left.m6 * right.m1;
	q_float m3 = left.m3 * right.m0 + left.m7 * right.m1;
	q_float m4 = left.m0 * right.m2 + left.m4 * right.m3;
	q_float m5 = left.m1 * right.m2 + left.m5 * right.m3;
	q_float m6 = left.m2 * right.m2 + left.m6 * right.m3;
	q_float m7 = left.m3 * right.m2 + left.m7 * right.m3;
	q_float m8 = left.m0 * right.m4 + left.m4 * right.m5;
	q_float m9 = left.m1 * right.m4 + left.m5 * right.m5;
	q_float m10 = left.m2 * right.m4 + left.m6 * right.m5;
	q_float m11 = left.m3 * right.m4 + left.m7 * right.m5;
	q_float m12 = left.m0 * right.m6 + left.m4 * right.m7;
	q_float m13 = left.m1 * right.m6 + left.m5 * right.m7;
	q_float m14 = left.m2 * right.m6 + left.m6 * right.m7;
	q_float m15 = left.m3 * right.m6 + left.m7 * right.m7;

	q_matrix44 result = {
		m0, m4, m8, m12,
        m1, m5, m9, m13,
        m2, m6, m10, m14,
        m3, m7, m11, m15
	};
	return result;
}

// Transpose function
QM_API q_matrix24 qmMatrix42Transpose(q_matrix42 mat)
{
	q_matrix24 result = {
		mat.m0, mat.m1, mat.m2, mat.m3,
		mat.m4, mat.m5, mat.m6, mat.m7
	};
	return result;
}

// Equal function
QM_API q_bool qmMatrix42Equal(q_matrix42 left, q_matrix42 right)
{
	return Q_BOOL(
		equalf(left.m0, right.m0) &&
		equalf(left.m1, right.m1) &&
        equalf(left.m2, right.m2) &&
        equalf(left.m3, right.m3) &&
        equalf(left.m4, right.m4) &&
        equalf(left.m5, right.m5) &&
		equalf(left.m6, right.m6) &&
        equalf(left.m7, right.m7)
	);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
