# Quite - Programming library for C applications
# Copyright (C) 2024 Nicholas Ng
#
# src/CMakeLists.txt
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.0)
project(quite C)

set(QUITE_HEADER_FILES
	quite.h
	qmath.h
	qutils.h
)

set(QUITE_SOURCE_FILES
	quite.c
	qutils.c
)

add_library(${PROJECT_NAME} ${QUITE_SOURCE_FILES} ${QUITE_HEADER_FILES})
