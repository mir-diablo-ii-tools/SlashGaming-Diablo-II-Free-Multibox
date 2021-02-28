/**
 * SlashGaming Diablo II Free Multibox
 * Copyright (C) 2019-2021  Mir Drualga
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

#include "d2gfx_remove_instance_check_patch.h"

#include <stdint.h>
#include <stddef.h>

/**
 * A single byte, the opcode for JMP.
 */
static const uint8_t kPatchBuffer[] = {
  0xEB
};

enum {
  kPatchBufferSize = sizeof(kPatchBuffer)
};

static ptrdiff_t GetPatchOffset(enum D2_GameVersion game_version) {
  switch (game_version) {
    case VERSION_1_00: {
      return 0x588C;
    }

    case VERSION_1_01:
    case VERSION_1_02:
    case VERSION_1_03: {
      return 0x587C;
    }

    case VERSION_1_04B_C:
    case VERSION_1_05:
    case VERSION_1_05B:
    case VERSION_1_06:
    case VERSION_1_06B: {
      return 0x43BC;
    }

    case VERSION_1_07_BETA: {
      return 0x441C;
    }

    case VERSION_1_07: {
      return 0x445C;
    }

    case VERSION_1_08:
    case VERSION_1_09:
    case VERSION_1_09B:
    case VERSION_1_09D: {
      return 0x447C;
    }

    case VERSION_1_10_BETA:
    case VERSION_1_10S_BETA:
    case VERSION_1_10: {
      return 0x446A;
    }

    case VERSION_1_11: {
      return 0x84CF;
    }

    case VERSION_1_11B: {
      return 0x84AF;
    }

    case VERSION_1_12A: {
      return 0x894F;
    }

    case VERSION_1_13A_PTR: {
      return 0xB6DF;
    }

    case VERSION_1_13C: {
      return 0x85BF;
    }

    case VERSION_1_13D: {
      return 0xB6B0;
    }

    case CLASSIC_1_14A: {
      return 0x56E8;
    }

    case LOD_1_14A: {
      return 0x57C8;
    }

    case CLASSIC_1_14B:
    case CLASSIC_1_14C: {
      return 0xE5E88;
    }

    case LOD_1_14B:
    case LOD_1_14C: {
      return 0xF2BC8;
    }

    case CLASSIC_1_14D: {
      return 0xE861B;
    }

    case LOD_1_14D: {
      return 0xF562B;
    }
  }
}

struct MAPI_GamePatch* SGD2FMB_D2GFX_RemoveInstanceCheckPatch_Init(
    struct MAPI_GamePatch* d2gfx_remove_instance_check_patch
) {
  const enum D2_GameVersion running_game_version = D2_GetRunningGameVersionId();

  ptrdiff_t patch_offset;
  struct MAPI_GameAddress patch_address;

  /* Initialize the patch address. */
  patch_offset = GetPatchOffset(running_game_version);

  MAPI_GameAddress_InitFromLibraryIdAndOffset(
      &patch_address,
      LIBRARY_D2GFX,
      patch_offset
  );

  /* Initialize the patch. */
  MAPI_GamePatch_InitGameBufferPatch(
      d2gfx_remove_instance_check_patch,
      &patch_address,
      kPatchBuffer,
      kPatchBufferSize
  );

  return d2gfx_remove_instance_check_patch;
}

void SGD2FMB_D2GFX_RemoveInstanceCheckPatch_Deinit(
    struct MAPI_GamePatch* d2gfx_remove_instance_check_patch
) {
  MAPI_GamePatch_Deinit(d2gfx_remove_instance_check_patch);
}
