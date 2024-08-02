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
