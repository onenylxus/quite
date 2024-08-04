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
	#if defined(_WIN32)
		#if defined(Q_EXPORT_SHARED_LIBRARY)
			#define QM_API __declspec(dllexport)
		#elif defined(Q_IMPORT_SHARED_LIBRARY)
			#define QM_API __declspec(dllimport)
		#endif /* defined(Q_EXPORT_SHARED_LIBRARY)... */
	#elif defined(Q_EXPORT_SHARED_LIBRARY)
		#define QM_API __attribute__((visibility("default")))
	#else
		#define QM_API extern inline
	#endif /* defined(_WIN32)... */
#elif defined(Q_MATH_STATIC_INLINE)
	#define QM_API static inline
#else
	#define QM_API inline
#endif /* defined(Q_MATH_IMPLEMENTATION)... */

#include <math.h>
#include "quite.h"

//// Epsilon ////

#ifndef Q_EPSILON
	#define Q_EPSILON 1.192092896e-7f;
#endif /* Q_EPSILON */

//// Angles ////

#ifndef Q_PI
	#define Q_PI 3.14159265358979323846;
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
	} q_vector2, qt_vec2;

	typedef struct q_vector3
	{
		q_float x;
		q_float y;
		q_float z;
	} q_vector3, qt_vec3;

	typedef struct q_vector4
	{
		q_float x;
		q_float y;
		q_float z;
		q_float w;
	} q_vector4, qt_vec4;
#endif /* Q_VECTOR */

#ifndef Q_MATRIX
	#define Q_MATRIX

	typedef struct q_matrix22
	{
		q_float m0, m2;
		q_float m1, m3;
	} q_matrix22, qt_mat22, qt_mat2;

	typedef struct q_matrix23
	{
		q_float m0, m2, m4;
		q_float m1, m3, m5;
	} q_matrix23, qt_mat23;

	typedef struct q_matrix24
	{
		q_float m0, m2, m4, m6;
		q_float m1, m3, m5, m7;
	} q_matrix24, qt_mat24;

	typedef struct q_matrix32
	{
		q_float m0, m3;
		q_float m1, m4;
		q_float m2, m5;
	} q_matrix32, qt_mat32;

	typedef struct q_matrix33
	{
		q_float m0, m3, m6;
		q_float m1, m4, m7;
		q_float m2, m5, m8;
	} q_matrix33, qt_mat33, qt_mat3;

	typedef struct q_matrix34
	{
		q_float m0, m3, m6, m9;
		q_float m1, m4, m7, m10;
		q_float m2, m5, m8, m11;
	} q_matrix34, qt_mat34;

	typedef struct q_matrix42
	{
		q_float m0, m4;
		q_float m1, m5;
		q_float m2, m6;
		q_float m3, m7;
	} q_matrix42, qt_mat42;

	typedef struct q_matrix43
	{
		q_float m0, m4, m8;
		q_float m1, m5, m9;
		q_float m2, m6, m10;
		q_float m3, m7, m11;
	} q_matrix43, qt_mat43;

	typedef struct q_matrix44
	{
		q_float m0, m4, m8, m12;
		q_float m1, m5, m9, m13;
		q_float m2, m6, m10, m14;
		q_float m3, m7, m11, m15;
	} q_matrix44, qt_mat44, qt_mat4;
#endif /* Q_MATRIX */

//// Quaternion type ////

#ifndef Q_QUATERNION
	#define Q_QUATERNION

	typedef q_vector4 q_quaternion, qt_quat;
#endif /* Q_QUATERNION */

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
	return max < min ? value : fminf(fmaxf(value, min), max);
}

// Wrap function
QM_API q_float qmFloatWrap(q_float value, q_float min, q_float max)
{
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
	return (value - inStart) * (outEnd - outStart) / (inEnd - inStart) + outStart;
}

// Equal function
QM_API q_bool qmFloatEqual(q_float left, q_float right)
{
	q_float epsilon = Q_EPSILON;
	return Q_BOOL(fabsf(left - right) <= epsilon * fmaxf(fmaxf(fabsf(left), fabsf(right)), 1.0f));
}

//// Vector2 functions ////

// Zero vector function
QM_API q_vector2 qmVector2Zero(q_void)
{
	q_vector2 result = {
		0.0f,
		0.0f
	};
	return result;
}

// One vector function
QM_API q_vector2 qmVector2One(q_void)
{
	q_vector2 result = {
		1.0f,
		1.0f
	};
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
	q_float length = sqrtf(vec.x * vec.x + vec.y * vec.y);

	q_vector2 result = {
		vec.x / length,
		vec.y / length
	};
	return length != 0 ? result : vec;
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
		max.x < min.x ? vec.x : fminf(fmaxf(vec.x, min.x), max.x),
		max.y < min.y ? vec.y : fminf(fmaxf(vec.y, min.y), max.y)
	};
	return result;
}

// Clamp on vector magnitude function
QM_API q_vector2 qmVector2ClampMag(q_vector2 vec, q_float min, q_float max)
{
	q_float scl = max < min ? 1.0f : fminf(fmaxf(vec.x * vec.x + vec.y * vec.y, min), max);

	q_vector2 result = {
		vec.x * scl,
		vec.y * scl
	};
	return result;
}

// Linear interpolation function
QM_API q_vector2 qmVector2Lerp(q_float value, q_vector2 start, q_vector2 end)
{
	q_vector2 result = {
		start.x + value * (end.x - start.x),
		start.y + value * (end.y - start.y)
	};
	return result;
}

// Reflect vector on normal function
QM_API q_vector2 qmVector2Reflect(q_vector2 vec, q_vector2 normal)
{
	q_float dprod = vec.x * normal.x + vec.y * normal.y;

	q_vector2 result = {
		vec.x - normal.x * 2.0f * dprod,
		vec.y - normal.y * 2.0f * dprod
	};
	return result;
}

// Refract vector on normal function
QM_API q_vector2 qmVector2Refract(q_vector2 vec, q_vector2 normal, q_float index)
{
	q_float dprod = vec.x * normal.x + vec.y * normal.y;
	q_float diff = 1.0f - index * index * (1.0f - dprod * dprod);
	if (diff < 0)
	{
		return vec;
	}

	q_vector2 result = {
		vec.x * index - normal.x * (dprod * index + sqrtf(diff)),
		vec.y * index - normal.y * (dprod * index + sqrtf(diff))
	};
	return result;
}

// Move vector to target function
QM_API q_vector2 qmVector2Move(q_vector2 vec, q_vector2 target, q_float dist)
{
	q_float cdist = sqrtf((target.x - vec.x) * (target.x - vec.x) + (target.y - vec.y) * (target.y - vec.y));

	q_vector2 result = {
		vec.x + dist / cdist * (target.x - vec.x),
		vec.y + dist / cdist * (target.y - vec.y)
	};
	return dist > 0 && dist <= cdist ? result : vec;
}

// Rotate vector function
QM_API q_vector2 qmVector2Rotate(q_vector2 vec, q_float angle)
{
	q_vector2 result = {
		vec.x * cosf(angle) - vec.y * sinf(angle),
		vec.x * sinf(angle) + vec.y * cosf(angle)
	};
	return result;
}

// Length function
QM_API q_float qmVector2Length(q_vector2 vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

// Squared length function
QM_API q_float qmVector2LengthSq(q_vector2 vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

// Dot product function
QM_API q_float qmVector2DotProduct(q_vector2 left, q_vector2 right)
{
	return left.x * right.x + left.y * right.y;
}

// Distance function
QM_API q_float qmVector2Distance(q_vector2 left, q_vector2 right)
{
	return sqrtf((left.x - right.x) * (left.x - right.x) + (left.y - right.y) * (left.y - right.y));
}

// Squared distance function
QM_API q_float qmVector2DistanceSq(q_vector2 left, q_vector2 right)
{
	return (left.x - right.x) * (left.x - right.x) + (left.y - right.y) * (left.y - right.y);
}

// Angle function
QM_API q_float qmVector2Angle(q_vector2 left, q_vector2 right)
{
	return atan2f(left.x * right.y - left.y * right.x, left.x * right.x + left.y * right.y);
}

// Line angle function
QM_API q_float qmVector2LineAngle(q_vector2 start, q_vector2 end)
{
	return -atan2f(end.y - start.y, end.x - start.x);
}

// Equal function
QM_API q_bool qmVector2Equal(q_vector2 left, q_vector2 right)
{
	q_float epsilon = Q_EPSILON;

	return Q_BOOL(
		fabsf(left.x - right.x) <= epsilon * fmaxf(fmaxf(fabsf(left.x), fabsf(right.x)), 1.0f) &&
		fabsf(left.y - right.y) <= epsilon * fmaxf(fmaxf(fabsf(left.y), fabsf(right.y)), 1.0f)
	);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
