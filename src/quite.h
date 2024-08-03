// Quite - Programming library for C applications
// Copyright (C) 2024 Nicholas Ng
//
// src/quite.h
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

#ifndef QUITE_H
#define QUITE_H

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif /* defined(_MSC_VER) && (_MSC_VER > 1000) */

//// Version ////

#define Q_MAJOR_VERSION 0
#define Q_MINOR_VERSION 1
#define Q_PATCH_VERSION 0
#define Q_VERSION "0.1.0-dev"

//// API ////

#if defined(_WIN32)
	#if defined(Q_EXPORT_SHARED_LIBRARY)
		#define Q_API __declspec(dllexport)
	#elif defined(Q_IMPORT_SHARED_LIBRARY)
		#define Q_API __declspec(dllimport)
	#endif /* defined(Q_EXPORT_SHARED_LIBRARY)... */
#else
	#define Q_API __attribute__((visibility("default")))
#endif /* defined(_WIN32) */

#ifndef Q_API
	#define Q_API
#endif /* Q_API */

//// Base types ////

typedef void q_void, *q_voidp;
typedef q_voidp q_handle;

#define q_null NULL

//// Integer types ////

typedef unsigned char q_u8, *q_u8p;
typedef unsigned short q_u16, *q_u16p;
typedef unsigned q_u32, *q_u32p;
typedef unsigned long long q_u64, *q_u64p;

typedef signed char q_i8, *q_i8p;
typedef short q_i16, *q_16p;
typedef int q_i32, *q_i32p;
typedef long long q_i64, *q_i64p;

#define q_u8_max ((q_u8) ~((q_u8)0))
#define q_i8_max ((q_i8)(q_u8_max >> 1))
#define q_i8_min ((q_i8)~q_i8_max)

#define q_u16_max ((q_u16) ~((q_u16)0))
#define q_i16_max ((q_i16)(q_u16_max >> 1))
#define q_i16_min ((q_i16)~q_i16_max)

#define q_u32_max ((q_u32) ~((q_u32)0))
#define q_i32_max ((q_i32)(q_u32_max >> 1))
#define q_i32_min ((q_i32)~q_i32_max)

#define q_u64_max ((q_u64) ~((q_u64)0))
#define q_i64_max ((q_i64)(q_u64_max >> 1))
#define q_i64_min ((q_i64)~q_i64_max)

typedef q_u8 q_uchar, *q_ucharp;
typedef q_u16 q_ushort, *q_ushortp;
typedef q_u32 q_uint, *q_uintp;
typedef q_u64 q_ulong, *q_ulongp;

typedef q_i8 q_char, *q_charp;
typedef q_i16 q_short, *q_shortp;
typedef q_i32 q_int, *q_intp;
typedef q_i64 q_long, *q_longp;

#define q_uchar_max q_u8_max
#define q_char_max q_i8_max
#define q_char_min q_i8_min

#define q_ushort_max q_u16_max
#define q_short_max q_i16_max
#define q_short_min q_i16_min

#define q_uint_max q_u32_max
#define q_int_max q_i32_max
#define q_int_min q_i32_min

#define q_ulong_max q_u64_max
#define q_long_max q_i64_max
#define q_long_min q_i64_min

//// Floating point types ////

typedef float q_float, *q_floatp;
typedef double q_double, *q_doublep;
typedef long double q_ldouble, *q_ldoublep;

//// Boolean type ////

typedef enum q_bool
{
	q_false,
	q_true
} q_bool;

//// Angles ////

#ifndef Q_PI
	#define Q_PI 3.141592653589793;
#endif

#ifndef Q_DEG
	#define Q_DEG(a) ((a) * 180.0f / Q_PI)
#endif

#ifndef Q_RAD
	#define Q_RAD(a) ((a) * Q_PI / 180.0f)
#endif

//// Vector and matrix types ////

#ifndef Q_VECTOR
	#define Q_VECTOR

	typedef struct q_vector2
	{
		q_float x;
		q_float y;
	} q_vector2, q_vec2;

	typedef struct q_vector3
	{
		q_float x;
		q_float y;
		q_float z;
	} q_vector3, q_vec3;

	typedef struct q_vector4
	{
		q_float x;
		q_float y;
		q_float z;
		q_float w;
	} q_vector4, q_vec4;
#endif /* Q_VECTOR */

#ifndef Q_MATRIX
	#define Q_MATRIX

	typedef struct q_matrix22
	{
		q_float m0, m2;
		q_float m1, m3;
	} q_matrix22, q_mat22, q_mat2;

	typedef struct q_matrix23
	{
		q_float m0, m2, m4;
		q_float m1, m3, m5;
	} q_matrix23, q_mat23;

	typedef struct q_matrix24
	{
		q_float m0, m2, m4, m6;
		q_float m1, m3, m5, m7;
	} q_matrix24, q_mat24;

	typedef struct q_matrix32
	{
		q_float m0, m3;
		q_float m1, m4;
		q_float m2, m5;
	} q_matrix32, q_mat32;

	typedef struct q_matrix33
	{
		q_float m0, m3, m6;
		q_float m1, m4, m7;
		q_float m2, m5, m8;
	} q_matrix33, q_mat33, q_mat3;

	typedef struct q_matrix34
	{
		q_float m0, m3, m6, m9;
		q_float m1, m4, m7, m10;
		q_float m2, m5, m8, m11;
	} q_matrix34, q_mat34;

	typedef struct q_matrix42
	{
		q_float m0, m4;
		q_float m1, m5;
		q_float m2, m6;
		q_float m3, m7;
	} q_matrix42, q_mat42;

	typedef struct q_matrix43
	{
		q_float m0, m4, m8;
		q_float m1, m5, m9;
		q_float m2, m6, m10;
		q_float m3, m7, m11;
	} q_matrix43, q_mat43;

	typedef struct q_matrix44
	{
		q_float m0, m4, m8, m12;
		q_float m1, m5, m9, m13;
		q_float m2, m6, m10, m14;
		q_float m3, m7, m11, m15;
	} q_matrix44, q_mat44, q_mat4;
#endif /* Q_MATRIX */

//// Quaternion type ////

#ifndef Q_QUATERNION
	#define Q_QUATERNION

	typedef q_vector4 q_quaternion, q_quat;
#endif /* Q_QUATERNION */

//// Functions ////

// Prevent function name mangling
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ... */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* QUITE_H */
