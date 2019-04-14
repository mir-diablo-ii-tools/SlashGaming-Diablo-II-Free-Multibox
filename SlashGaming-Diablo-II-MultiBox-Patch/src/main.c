/**
 * SlashGaming Diablo II MultiBox Patch
 * Copyright (C) 2019  Mir Drualga
 *
 * This file is part of SlashGaming Diablo II MultiBox Patch.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Additional permissions under GNU Affero General Public License version 3
 *  section 7
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with Diablo II (or a modified version of that game and its
 *  libraries), containing parts covered by the terms of Blizzard End User
 *  License Agreement, the licensors of this Program grant you additional
 *  permission to convey the resulting work. This additional permission is
 *  also extended to any combination of expansions, mods, and remasters of
 *  the game.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any Glide wrapper (or a modified version of that library),
 *  containing parts not covered by a compatible license, the licensors of
 *  this Program grant you additional permission to convey the resulting
 *  work.
 */

#include <windows.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <sgd2mapi.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * Declarations
 */

/**
 * A single byte, the opcode for JMP.
 */
const uint8_t patch_buffer_01[] = {
  0xEB
};

enum {
  kNumPatches = 1
};

struct MAPI_GamePatch* GetPatches();
struct MAPI_GameAddress* GetGameAddresses();

/**
 * Definitions
 */

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpvReserved
) {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH: {
      struct MAPI_GamePatch* patches = GetPatches();

      for (int i = 0; i < kNumPatches; i += 1) {
        MAPI_GamePatch_Apply(&patches[i]);
      }
      break;
    }

    case DLL_PROCESS_DETACH: {
      struct MAPI_GamePatch* patches = GetPatches();

      for (int i = 0; i < kNumPatches; i += 1) {
        MAPI_GamePatch_Remove(&patches[i]);
        MAPI_GamePatch_Deinit(&patches[i]);
      }
      break;
    }
  }

  return TRUE;
}

struct MAPI_GamePatch* GetPatches() {
  static bool is_init = false;
  static struct MAPI_GamePatch game_patches[kNumPatches];
  
  if (!is_init) {
    struct MAPI_GameAddress* game_addresses = GetGameAddresses();

    MAPI_GamePatch_InitGameBufferPatch(
        &game_patches[0],
        &game_addresses[0],
        patch_buffer_01,
        sizeof(patch_buffer_01)
    );

    is_init = true;
  }

  return &game_patches;
}

struct MAPI_GameAddress* GetGameAddresses() {
  static bool is_init = false;
  static struct MAPI_GameAddress game_addresses[kNumPatches];

  if (!is_init) {
    intptr_t offset;

    switch (D2_GetRunningGameVersionId()) {
      case VERSION_1_12A: {
        offset = 0x894F;
        break;
      }

      case VERSION_1_13A_BETA: {
        offset = 0xB6DF;
        break;
      }

      case VERSION_1_13C: {
        offset = 0x85BF;
        break;
      }

      case VERSION_1_13D: {
        offset = 0xB6B0;
        break;
      }

      case LOD_1_14A: {
        offset = 0x57C8;
        break;
      }

      case LOD_1_14B:
      case LOD_1_14C: {
        offset = 0xF2BC8;
        break;
      }

      case LOD_1_14D: {
        offset = 0xF562B;
        break;
      }
    }

    MAPI_GameAddress_InitFromLibraryIdAndOffset(
        &game_addresses[0],
        LIBRARY_D2GFX,
        offset
    );

    is_init = true;
  }

  return &game_addresses;
}

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
