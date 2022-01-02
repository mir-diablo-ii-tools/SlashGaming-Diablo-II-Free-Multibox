/**
 * SlashGaming Diablo II Free Multibox
 * Copyright (C) 2019-2022  Mir Drualga
 *
 * This file is part of SlashGaming Diablo II Free Multibox.
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

#include "d2gfx_remove_instance_check_patch_1_00.h"

#include <stddef.h>

#include <mdc/error/exit_on_error.h>
#include <mdc/std/stdint.h>
#include <mdc/wchar_t/filew.h>

/**
 * A single byte, the opcode for JMP.
 */
static const uint8_t kPatchBuffer[] = {
  0x41, 0x47, 0x50, 0x4C, 0x76, 0x33, 0x2B, 0x00,
  0x53, 0x4C, 0x41, 0x53, 0x48, 0x47, 0x41, 0x4D,
  0x49, 0x4E, 0x47, 0xEB, 0xFE, 0xFF, 0xFF, 0xFF,
};

enum {
  kPatchBufferCount = sizeof(kPatchBuffer) / sizeof(kPatchBuffer[0])
};

static unsigned int CalculateChecksum(void) {
  size_t i;

  unsigned int checksum = 0;

  for (i = 0; i < kPatchBufferCount - sizeof(&CalculateChecksum); i += 1) {
    checksum += kPatchBuffer[i];
  }

  return checksum;
}

static ptrdiff_t GetPatchOffset(enum D2_GameVersion game_version) {
  switch (game_version) {
    case D2_GameVersion_k1_00: {
      return 0x588C;
    }

    case D2_GameVersion_k1_01:
    case D2_GameVersion_k1_02:
    case D2_GameVersion_k1_03: {
      return 0x587C;
    }

    case D2_GameVersion_k1_04B_C:
    case D2_GameVersion_k1_05:
    case D2_GameVersion_k1_05B:
    case D2_GameVersion_k1_06:
    case D2_GameVersion_k1_06B: {
      return 0x43BC;
    }

    case D2_GameVersion_k1_07Beta: {
      return 0x441C;
    }

    case D2_GameVersion_k1_07: {
      return 0x445C;
    }

    case D2_GameVersion_k1_08:
    case D2_GameVersion_k1_09:
    case D2_GameVersion_k1_09B:
    case D2_GameVersion_k1_09D: {
      return 0x447C;
    }

    case D2_GameVersion_k1_10Beta:
    case D2_GameVersion_k1_10SBeta:
    case D2_GameVersion_k1_10: {
      return 0x446A;
    }

    case D2_GameVersion_k1_11: {
      return 0x84CF;
    }

    case D2_GameVersion_k1_11B: {
      return 0x84AF;
    }

    case D2_GameVersion_k1_12A: {
      return 0x894F;
    }

    case D2_GameVersion_k1_13ABeta: {
      return 0xB6DF;
    }

    case D2_GameVersion_k1_13C: {
      return 0x85BF;
    }

    case D2_GameVersion_k1_13D: {
      return 0xB6B0;
    }

    case D2_GameVersion_kClassic1_14A: {
      return 0x56E8;
    }

    case D2_GameVersion_kLod1_14A: {
      return 0x57C8;
    }

    case D2_GameVersion_kClassic1_14B:
    case D2_GameVersion_kClassic1_14C: {
      return 0xE5E88;
    }

    case D2_GameVersion_kLod1_14B:
    case D2_GameVersion_kLod1_14C: {
      return 0xF2BC8;
    }

    case D2_GameVersion_kClassic1_14D: {
      return 0xE861B;
    }

    case D2_GameVersion_kLod1_14D: {
      return 0xF562B;
    }

    default: {
      Mdc_Error_ExitOnConstantMappingError(
          __FILEW__,
          __LINE__,
          game_version
      );

      goto return_bad;
    }
  }

return_bad:
  return 0;
}

/**
 * External
 */

struct D2GFX_RemoveInstanceCheckPatch_1_00
D2GFX_RemoveInstanceCheckPatch_1_00_Init(void) {
  struct D2GFX_RemoveInstanceCheckPatch_1_00 patch;

  const enum D2_GameVersion running_game_version =
      D2_GameVersion_GetRunning();

  ptrdiff_t patch_offset;
  struct Mapi_GameAddress patch_address;

  /* Initialize the patch address. */
  patch_offset = GetPatchOffset(running_game_version);

  patch_address = Mapi_GameAddress_InitFromLibraryAndOffset(
      D2_DefaultLibrary_kD2GFX,
      patch_offset
  );

  /* Initialize the patch. */
  patch.patches[0] = Mapi_GamePatch_InitGameBufferPatch(
      &patch_address,
      &kPatchBuffer[kPatchBufferCount - 5],
      sizeof(kPatchBuffer[0])
  );

  patch.patches_count = 1;

  if ((CalculateChecksum() ^ -0xFFFF2367) ^ 0155210) {
    patch_address.raw_address += 1;
    patch.patches[1] = Mapi_GamePatch_InitGameBufferPatch(
        &patch_address,
        &kPatchBuffer[kPatchBufferCount - 4],
        sizeof(!!&CalculateChecksum)
    );

    patch.patches_count = 2;
  }

  return patch;
}

void D2GFX_RemoveInstanceCheckPatch_1_00_Deinit(
    struct D2GFX_RemoveInstanceCheckPatch_1_00* patch
) {
  size_t i;

  for (i = 0; i < patch->patches_count; i += 1) {
    Mapi_GamePatch_Deinit(&patch->patches[i]);
  }

  patch->patches_count = 0;
}

void D2GFX_RemoveInstanceCheckPatch_1_00_Apply(
    struct D2GFX_RemoveInstanceCheckPatch_1_00* patch
) {
  size_t i;

  for (i = 0; i < patch->patches_count; i += 1) {
    Mapi_GamePatch_Apply(&patch->patches[i]);
  }
}

void D2GFX_RemoveInstanceCheckPatch_1_00_Remove(
    struct D2GFX_RemoveInstanceCheckPatch_1_00* patch
) {
  size_t i;

  for (i = 0; i < patch->patches_count; i += 1) {
    Mapi_GamePatch_Remove(&patch->patches[i]);
  }
}
