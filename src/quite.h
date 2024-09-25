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

#ifndef Q_BOOL
	#define Q_BOOL(b) ((b) ? q_true : q_false)
#endif /* Q_BOOL */

//// String type ////

typedef const char *q_str;

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
