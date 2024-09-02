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

#if defined(Q_ENABLE_TYPE_ALIAS)
	typedef q_void qt_v;
#endif /* defined(Q_ENABLE_TYPE_ALIAS) */

//// Integer types ////

typedef unsigned char q_uchar, *q_ucharp;
typedef unsigned short q_ushort, *q_ushortp;
typedef unsigned q_uint, *q_uintp;
typedef unsigned long long q_ulong, *q_ulongp;

typedef signed char q_char, *q_charp;
typedef short q_short, *q_shortp;
typedef int q_int, *q_intp;
typedef long long q_long, *q_longp;

#define q_uchar_max ((q_uchar) ~((q_uchar)0))
#define q_char_max ((q_char)(q_uchar_max >> 1))
#define q_char_min ((q_char)~q_char_max)

#define q_ushort_max ((q_ushort) ~((q_ushort)0))
#define q_short_max ((q_short)(q_ushort_max >> 1))
#define q_short_min ((q_short)~q_short_max)

#define q_uint_max ((q_uint) ~((q_uint)0))
#define q_int_max ((q_int)(q_uint_max >> 1))
#define q_int_min ((q_int)~q_int_max)

#define q_ulong_max ((q_ulong) ~((q_ulong)0))
#define q_long_max ((q_long)(q_ulong_max >> 1))
#define q_long_min ((q_long)~q_long_max)

#if defined(Q_ENABLE_TYPE_ALIAS)
	typedef q_uchar qt_u8;
	typedef q_ushort qt_u16;
	typedef q_uint qt_u32;
	typedef q_uint qt_u64;

	typedef q_ucharp qt_u8p;
	typedef q_ushortp qt_u16p;
	typedef q_uintp qt_u32p;
	typedef q_uintp qt_u64p;

	typedef q_char qt_i8;
	typedef q_short qt_i16;
	typedef q_int qt_i32;
	typedef q_int qt_i64;

	typedef q_charp qt_i8p;
	typedef q_shortp qt_i16p;
	typedef q_intp qt_i32p;
	typedef q_intp qt_i64p;

	#define qt_u8_max q_uchar_max
	#define qt_i8_max q_char_max
	#define qt_i8_min q_char_min

	#define qt_u16_max q_ushort_max
	#define qt_i16_max q_short_max
	#define qt_i16_min q_short_min

	#define qt_u32_max q_uint_max
	#define qt_i32_max q_int_max
	#define qt_i32_min q_int_min

	#define qt_u64_max q_ulong_max
	#define qt_i64_max q_long_max
	#define qt_i64_min q_long_min
#endif /* defined(Q_ENABLE_TYPE_ALIAS) */

//// Floating point types ////

typedef float q_float, *q_floatp;
typedef double q_double, *q_doublep;
typedef long double q_ldouble, *q_ldoublep;

#if defined(Q_ENABLE_TYPE_ALIAS)
	typedef q_float qt_f;
	typedef q_double qt_d;
	typedef q_ldouble qt_ld;

	typedef q_floatp qt_fp;
	typedef q_doublep qt_dp;
	typedef q_ldoublep qt_ldp;
#endif /* defined(Q_ENABLE_TYPE_ALIAS) */

//// Boolean type ////

typedef enum q_bool
{
	q_false,
	q_true
} q_bool;

#if defined(Q_ENABLE_TYPE_ALIAS)
	typedef q_bool qt_b;
#endif /* defined(Q_ENABLE_TYPE_ALIAS) */

#ifndef Q_BOOL
	#define Q_BOOL(b) ((b) ? q_true : q_false)
#endif /* Q_BOOL */

//// String type ////

typedef const char *q_str;

#if defined(Q_ENABLE_TYPE_ALIAS)
	typedef q_str qt_s;
#endif /* defined(Q_ENABLE_TYPE_ALIAS) */

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
