// Quite - Programming library for C applications
// Copyright (C) 2024 Nicholas Ng
//
// src/qutils.h
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

#ifndef QUTILS_H
#define QUTILS_H

#if defined(_MSC_VER) && (_MSC_VER > 1000)
#pragma once
#endif /* defined(_MSC_VER) && (_MSC_VER > 1000) */

#include <stdlib.h> // malloc, calloc, realloc, free
#include "quite.h"

//// Log management ////

#define Q_LOG_MAX_LENGTH 256

typedef enum
{
	Q_LOG_NONE,
	Q_LOG_TRACE,
	Q_LOG_DEBUG,
	Q_LOG_INFO,
	Q_LOG_WARN,
	Q_LOG_ERROR,
	Q_LOG_ALL
} q_log_level;

#if defined(Q_ENABLE_LOGGING)
	#define Q_LOG(l, ...) quLog(l, __VA_ARGS__)
#else
	#define Q_LOG(l, ...) (q_void)0
#endif /* Q_ENABLE_LOGGING */

//// Memory management ////

#ifndef Q_MALLOC
	#define Q_MALLOC(s) malloc(s)
#endif /* Q_MALLOC */

#ifndef Q_CALLOC
	#define Q_CALLOC(n, s) calloc(n, s)
#endif /* Q_CALLOC */

#ifndef Q_REALLOC
	#define Q_REALLOC(p, s) realloc(p, s)
#endif /* Q_REALLOC */

#ifndef Q_FREE
	#define Q_FREE(p) free(p)
#endif /* Q_FREE */

//// Functions ////

// Prevent function name mangling
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

// Log management
Q_API q_void quLog(q_int level, q_str message, ...);

// Memory management
Q_API q_handle quAlloc(q_uint size);
Q_API q_handle quRealloc(q_handle handle, q_uint size);
Q_API q_void quFree(q_handle handle);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* QUTILS_H */
