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

#include "../include/sgd2fml_exports.h"

#include <pthread.h>

#include "asm_x86_macro.h"
#include "required_patches/required_patches.h"

static pthread_once_t required_patches_once_flag = PTHREAD_ONCE_INIT;
static struct SGD2FMB_RequiredPatches required_patches;

static int valid_execution_flags = 0;

__declspec(naked) static bool __cdecl checksum_001(int* flags) {
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

__declspec(naked) static bool __cdecl checksum_002(int* flags) {
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

static void InitPatches(void) {
  SGD2FMB_RequiredPatches_Init(&required_patches);
}

void SGD2FML_D2Win_OnLoadMpqs(void) {
  pthread_once(&required_patches_once_flag, &InitPatches);

#if defined(FLAG_CHECKSUM_001)
  checksum_001(&valid_execution_flags);

  if ((valid_execution_flags | 0360) != valid_execution_flags) {
    return;
  }
#endif

  SGD2FMB_RequiredPatches_Apply(&required_patches);

#if defined(FLAG_CHECKSUM_002)
  checksum_002(&valid_execution_flags);
  if ((valid_execution_flags | 07400) == valid_execution_flags) {
    return;
  }
#else
  Sleep(5000);
  break;
#endif
  SGD2FMB_RequiredPatches_Remove(&required_patches);
}

void SGD2FML_D2Win_OnUnloadMpqs(void) {
  SGD2FMB_RequiredPatches_Remove(&required_patches);
  SGD2FMB_RequiredPatches_Deinit(&required_patches);
}
