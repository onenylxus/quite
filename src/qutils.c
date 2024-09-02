// Quite - Programming library for C applications
// Copyright (C) 2024 Nicholas Ng
//
// src/qutils.c
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

#include <stdarg.h> // va_list, va_start, va_end
#include <stdio.h> // stdout, vprintf
#include <string.h> // strcpy, strcat
#include "qutils.h"

//// Global variables ////

static q_int qu_log_level = Q_LOG_INFO;

//// Log management ////

// Log message
Q_API q_void quLog(q_int level, q_str message, ...)
{
	// Check log level
	if (level == Q_LOG_NONE || level == Q_LOG_ALL)
	{
		q_str name = level == Q_LOG_ALL ? "all" : "none";
		return quLog(Q_LOG_WARN, "cannot log with level %s", name);
	}
	if (level < qu_log_level)
	{
		return;
	}

	// Start processing arguments
	va_list args;
	va_start(args, message);

	// Print message
	q_char buffer[Q_LOG_MAX_LENGTH] = { 0 };
	switch (level)
	{
	case Q_LOG_TRACE:
		strcpy(buffer, "trace: ");
		break;
	case Q_LOG_DEBUG:
		strcpy(buffer, "debug: ");
		break;
	case Q_LOG_INFO:
		strcpy(buffer, "info: ");
		break;
	case Q_LOG_WARN:
		strcpy(buffer, "warn: ");
		break;
	case Q_LOG_ERROR:
		strcpy(buffer, "error: ");
		break;
	}

	q_uint length = strlen(message);
	memcpy(buffer + strlen(buffer), message, length < Q_LOG_MAX_LENGTH - 10 ? length : Q_LOG_MAX_LENGTH - 10);
	strcat(buffer, "\n");
	vprintf(buffer, args);
	fflush(stdout);

	// Stop processing arguments
	va_end(args);
}

//// Memory management ////

// Allocate memory to handle
Q_API q_handle quAlloc(q_uint size)
{
	q_handle result = Q_CALLOC(size, 1);
	return result;
}

// Reallocate memory in handle
Q_API q_handle quRealloc(q_handle handle, q_uint size)
{
	q_handle result = Q_REALLOC(handle, size);
    return result;
}

// Free memory from handle
Q_API q_void quFree(q_handle handle)
{
    Q_FREE(handle);
}
