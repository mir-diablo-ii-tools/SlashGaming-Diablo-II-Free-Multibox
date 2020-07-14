/**
 * SlashGaming Diablo II Free MultiBox
 * Copyright (C) 2019-2020  Mir Drualga
 *
 * This file is part of SlashGaming Diablo II Free MultiBox.
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
#include "asm_x86_macro.h"

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

static int valid_execution_flags = 0;

__declspec(naked) static bool __cdecl
checksum_001(int* flags) {
  ASM_X86(xor eax, eax)
  ASM_X86(pushad)
  ASM_X86(mov ebp, esp)
  ASM_X86(push ebx)
  ASM_X86(dec esp)
  ASM_X86(inc ecx)
  ASM_X86(push ebx)
  ASM_X86(dec eax)
  ASM_X86(inc edi)
  ASM_X86(inc ecx)
  ASM_X86(dec ebp)
#define FLAG_CHECKSUM_001
  ASM_X86(dec ecx)
  ASM_X86(dec esi)
  ASM_X86(inc edi)
  ASM_X86(mov esp, ebp)
  ASM_X86(add esp, 1)
  ASM_X86(popad)
  ASM_X86(mov eax, dword ptr[esp + 0x04])
  ASM_X86(or dword ptr[eax], 240)
  ASM_X86(ret)
}

__declspec(naked) static bool __cdecl
checksum_002(int* flags) {
  ASM_X86(sub esp, 4)
  ASM_X86(lea eax, [esp])
  ASM_X86(pushad)
  ASM_X86(push eax)
  ASM_X86(mov ebp, esp)
  ASM_X86(sub esp, 0x200 - 0x1)
  ASM_X86(lea eax, [esp - 0x1])
  ASM_X86(mov ecx, eax)
  ASM_X86(mov esi, eax)
  ASM_X86(mov ebx, eax)
  ASM_X86(dec esp)
#define FLAG_CHECKSUM_002
  ASM_X86(imul esp, [ebx + 0x65], 0x6465736e)
  ASM_X86(mov esp, eax)
  ASM_X86(and [ecx + 0x47], al)
  ASM_X86(push eax)
  ASM_X86(dec esp)
  ASM_X86(and [esi + 0x33], dh)
  ASM_X86(sub esp, [eax])
  ASM_X86(mov esp, ebp)
  ASM_X86(pop eax)
  ASM_X86(mov eax, esp)
  ASM_X86(popad)
  ASM_X86(add esp, 4)
  ASM_X86(mov eax, dword ptr[esp + 0x04])
  ASM_X86(or dword ptr[eax], 3840)
  ASM_X86(ret)
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpvReserved
) {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH: {
#if defined(FLAG_CHECKSUM_001)
      checksum_001(&valid_execution_flags);

      if ((valid_execution_flags | 0360) != valid_execution_flags) {
        return FALSE;
      }
#endif

      if (valid_execution_flags) {
      }

      struct MAPI_GamePatch* patches = GetPatches();

      for (int i = 0; i < kNumPatches; i += 1) {
        MAPI_GamePatch_Apply(&patches[i]);
      }

#if defined(FLAG_CHECKSUM_002)
      checksum_002(&valid_execution_flags);
      if ((valid_execution_flags | 07400) == valid_execution_flags) {
        break;
      }
#else
      Sleep(5000);
      break;
#endif
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
      case VERSION_1_00: {
        offset = 0x588C;
        break;
      }

      case VERSION_1_01:
      case VERSION_1_02:
      case VERSION_1_03: {
        offset = 0x587C;
        break;
      }

      case VERSION_1_04B_C:
      case VERSION_1_05:
      case VERSION_1_05B:
      case VERSION_1_06:
      case VERSION_1_06B: {
        offset = 0x43BC;
        break;
      }

      case VERSION_1_07_BETA: {
        offset = 0x441C;
        break;
      }

      case VERSION_1_07: {
        offset = 0x445C;
        break;
      }

      case VERSION_1_08:
      case VERSION_1_09:
      case VERSION_1_09B:
      case VERSION_1_09D: {
        offset = 0x447C;
        break;
      }

      case VERSION_1_10_BETA:
      case VERSION_1_10S_BETA:
      case VERSION_1_10: {
        offset = 0x446A;
        break;
      }

      case VERSION_1_11: {
        offset = 0x84CF;
        break;
      }

      case VERSION_1_11B: {
        offset = 0x84AF;
        break;
      }

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

      case CLASSIC_1_14A: {
        offset = 0x56E8;
        break;
      }

      case LOD_1_14A: {
        offset = 0x57C8;
        break;
      }

      case CLASSIC_1_14B:
      case CLASSIC_1_14C: {
        offset = 0xE5E88;
        break;
      }

      case LOD_1_14B:
      case LOD_1_14C: {
        offset = 0xF2BC8;
        break;
      }

      case CLASSIC_1_14D: {
        offset = 0xE861B;
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
