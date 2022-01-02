# SlashGaming Diablo II Multibox Patch
# Copyright (C) 2019-2022  Mir Drualga
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Additional permissions under GNU Affero General Public License version 3
# section 7
#
# If you modify this Program, or any covered work, by linking or combining
# it with Diablo II (or a modified version of that game and its
# libraries), containing parts covered by the terms of Blizzard End User
# License Agreement, the licensors of this Program grant you additional
# permission to convey the resulting work. This additional permission is
# also extended to any combination of expansions, mods, and remasters of
# the game.
#
# If you modify this Program, or any covered work, by linking or combining
# it with any Graphics Device Interface (GDI), DirectDraw, Direct3D,
# Glide, OpenGL, or Rave wrapper (or modified versions of those
# libraries), containing parts not covered by a compatible license, the
# licensors of this Program grant you additional permission to convey the
# resulting work.
#
# If you modify this Program, or any covered work, by linking or combining
# it with any library (or a modified version of that library) that links
# to Diablo II (or a modified version of that game and its libraries),
# containing parts not covered by a compatible license, the licensors of
# this Program grant you additional permission to convey the resulting
# work.

cmake_minimum_required(VERSION 3.11)

# Name of the project, also is the name of the file
project(SGD2FreeMultibox)

# Define requirements for C
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Enable NASM
set(CMAKE_ASM_NASM_OBJECT_FORMAT win32)
enable_language(ASM_NASM)

# Remove MinGW compiled binary "lib" prefix
if (MINGW)
    set(CMAKE_IMPORT_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
endif (MINGW)

# List all of the source files here
set(PATCH_FILES
    "src/patches/patches.c"
    "src/patches/patches.h"

    "src/patches/required/required_patches.c"
    "src/patches/required/required_patches.h"

    # D2GFX remove instance check patch
    "src/patches/required/d2gfx_remove_instance_check_patch/d2gfx_remove_instance_check_patch_1_00.c"
    "src/patches/required/d2gfx_remove_instance_check_patch/d2gfx_remove_instance_check_patch_1_00.h"

    "src/patches/required/d2gfx_remove_instance_check_patch/d2gfx_remove_instance_check_patch.c"
    "src/patches/required/d2gfx_remove_instance_check_patch/d2gfx_remove_instance_check_patch.h"
)

set(SOURCE_FILES
    # Include files
    "include/dllexport_define.inc"
    "include/dllexport_undefine.inc"
    "include/license.h"
    "include/sgd2fml_mod_exports.h"

    # Resource files
    "resource/resource.rc"

    # Source files
    "src/dll_main.c"
    "src/license.c"
    "src/sgd2fml_mod_exports.c"

    "${PATCH_FILES}"
)

# Output DLL
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} SGD2MAPIc MDCc)
add_dependencies(${PROJECT_NAME} SGD2MAPIc MDCc)

# Output DLL (static linking)
add_library(${PROJECT_NAME}.static SHARED ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}.static libSGD2MAPIc libMDCc)
add_dependencies(${PROJECT_NAME}.static libSGD2MAPIc libMDCc)

# Project source listing
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})
