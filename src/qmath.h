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

// Equal function
QM_API q_bool qmFloatEqual(q_float left, q_float right)
{
	q_float epsilon = Q_EPSILON;
	return fabsf(left - right) <= epsilon * fmaxf(fmaxf(fabsf(left), fabsf(right)), 1.0f) ? q_true : q_false;
}

// Clamp function
QM_API q_float qmFloatClamp(q_float value, q_float min, q_float max)
{
	return max < min ? value : value < min ? min : value > max ? max : value;
}

// Wrap function
QM_API q_float qmFloatWrap(q_float value, q_float min, q_float max)
{
	return max == min ? min : value - (max - min) * floorf((value - min) / (max - min));
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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
