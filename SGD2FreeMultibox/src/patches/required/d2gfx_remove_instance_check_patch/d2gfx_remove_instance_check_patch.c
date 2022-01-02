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

#include "d2gfx_remove_instance_check_patch.h"

#include <mdc/malloc/malloc.h>
#include <sgd2mapi.h>

struct D2GFX_RemoveInstanceCheckPatch
D2GFX_RemoveInstanceCheckPatch_Init(void) {
  struct D2GFX_RemoveInstanceCheckPatch patch;

  enum D2_GameVersion running_game_version;

  running_game_version = D2_GameVersion_GetRunning();

  switch (running_game_version) {
    case D2_GameVersion_k1_00:
    case D2_GameVersion_k1_01:
    case D2_GameVersion_k1_02:
    case D2_GameVersion_k1_03:
    case D2_GameVersion_k1_04B_C:
    case D2_GameVersion_k1_05:
    case D2_GameVersion_k1_05B:
    case D2_GameVersion_k1_06:
    case D2_GameVersion_k1_06B:
    case D2_GameVersion_k1_07Beta:
    case D2_GameVersion_k1_07:
    case D2_GameVersion_k1_08:
    case D2_GameVersion_k1_09:
    case D2_GameVersion_k1_09B:
    case D2_GameVersion_k1_09D:
    case D2_GameVersion_k1_10Beta:
    case D2_GameVersion_k1_10SBeta:
    case D2_GameVersion_k1_10:
    case D2_GameVersion_k1_11:
    case D2_GameVersion_k1_11B:
    case D2_GameVersion_k1_12A:
    case D2_GameVersion_k1_13ABeta:
    case D2_GameVersion_k1_13C:
    case D2_GameVersion_k1_13D:
    case D2_GameVersion_kClassic1_14A:
    case D2_GameVersion_kLod1_14A:
    case D2_GameVersion_kClassic1_14B:
    case D2_GameVersion_kClassic1_14C:
    case D2_GameVersion_kLod1_14B:
    case D2_GameVersion_kLod1_14C:
    case D2_GameVersion_kClassic1_14D:
    case D2_GameVersion_kLod1_14D: {
      patch.patch.ptr_1_00 = Mdc_malloc(sizeof(*patch.patch.ptr_1_00));
      *patch.patch.ptr_1_00 = D2GFX_RemoveInstanceCheckPatch_1_00_Init();
      break;
    }
  }

  return patch;
}

void D2GFX_RemoveInstanceCheckPatch_Deinit(
    struct D2GFX_RemoveInstanceCheckPatch* patch
) {
  enum D2_GameVersion running_game_version;

  running_game_version = D2_GameVersion_GetRunning();

  switch (running_game_version) {
    case D2_GameVersion_k1_00:
    case D2_GameVersion_k1_01:
    case D2_GameVersion_k1_02:
    case D2_GameVersion_k1_03:
    case D2_GameVersion_k1_04B_C:
    case D2_GameVersion_k1_05:
    case D2_GameVersion_k1_05B:
    case D2_GameVersion_k1_06:
    case D2_GameVersion_k1_06B:
    case D2_GameVersion_k1_07Beta:
    case D2_GameVersion_k1_07:
    case D2_GameVersion_k1_08:
    case D2_GameVersion_k1_09:
    case D2_GameVersion_k1_09B:
    case D2_GameVersion_k1_09D:
    case D2_GameVersion_k1_10Beta:
    case D2_GameVersion_k1_10SBeta:
    case D2_GameVersion_k1_10:
    case D2_GameVersion_k1_11:
    case D2_GameVersion_k1_11B:
    case D2_GameVersion_k1_12A:
    case D2_GameVersion_k1_13ABeta:
    case D2_GameVersion_k1_13C:
    case D2_GameVersion_k1_13D:
    case D2_GameVersion_kClassic1_14A:
    case D2_GameVersion_kLod1_14A:
    case D2_GameVersion_kClassic1_14B:
    case D2_GameVersion_kClassic1_14C:
    case D2_GameVersion_kLod1_14B:
    case D2_GameVersion_kLod1_14C:
    case D2_GameVersion_kClassic1_14D:
    case D2_GameVersion_kLod1_14D: {
      D2GFX_RemoveInstanceCheckPatch_1_00_Deinit(patch->patch.ptr_1_00);
      Mdc_free(patch->patch.ptr_1_00);
      return;
    }
  }
}

void D2GFX_RemoveInstanceCheckPatch_Apply(
    struct D2GFX_RemoveInstanceCheckPatch* patch
) {
  enum D2_GameVersion running_game_version;

  running_game_version = D2_GameVersion_GetRunning();

  switch (running_game_version) {
    case D2_GameVersion_k1_00:
    case D2_GameVersion_k1_01:
    case D2_GameVersion_k1_02:
    case D2_GameVersion_k1_03:
    case D2_GameVersion_k1_04B_C:
    case D2_GameVersion_k1_05:
    case D2_GameVersion_k1_05B:
    case D2_GameVersion_k1_06:
    case D2_GameVersion_k1_06B:
    case D2_GameVersion_k1_07Beta:
    case D2_GameVersion_k1_07:
    case D2_GameVersion_k1_08:
    case D2_GameVersion_k1_09:
    case D2_GameVersion_k1_09B:
    case D2_GameVersion_k1_09D:
    case D2_GameVersion_k1_10Beta:
    case D2_GameVersion_k1_10SBeta:
    case D2_GameVersion_k1_10:
    case D2_GameVersion_k1_11:
    case D2_GameVersion_k1_11B:
    case D2_GameVersion_k1_12A:
    case D2_GameVersion_k1_13ABeta:
    case D2_GameVersion_k1_13C:
    case D2_GameVersion_k1_13D:
    case D2_GameVersion_kClassic1_14A:
    case D2_GameVersion_kLod1_14A:
    case D2_GameVersion_kClassic1_14B:
    case D2_GameVersion_kClassic1_14C:
    case D2_GameVersion_kLod1_14B:
    case D2_GameVersion_kLod1_14C:
    case D2_GameVersion_kClassic1_14D:
    case D2_GameVersion_kLod1_14D: {
      D2GFX_RemoveInstanceCheckPatch_1_00_Apply(patch->patch.ptr_1_00);
      return;
    }
  }
}

void D2GFX_RemoveInstanceCheckPatch_Remove(
    struct D2GFX_RemoveInstanceCheckPatch* patch
) {
  enum D2_GameVersion running_game_version;

  running_game_version = D2_GameVersion_GetRunning();

  switch (running_game_version) {
    case D2_GameVersion_k1_00:
    case D2_GameVersion_k1_01:
    case D2_GameVersion_k1_02:
    case D2_GameVersion_k1_03:
    case D2_GameVersion_k1_04B_C:
    case D2_GameVersion_k1_05:
    case D2_GameVersion_k1_05B:
    case D2_GameVersion_k1_06:
    case D2_GameVersion_k1_06B:
    case D2_GameVersion_k1_07Beta:
    case D2_GameVersion_k1_07:
    case D2_GameVersion_k1_08:
    case D2_GameVersion_k1_09:
    case D2_GameVersion_k1_09B:
    case D2_GameVersion_k1_09D:
    case D2_GameVersion_k1_10Beta:
    case D2_GameVersion_k1_10SBeta:
    case D2_GameVersion_k1_10:
    case D2_GameVersion_k1_11:
    case D2_GameVersion_k1_11B:
    case D2_GameVersion_k1_12A:
    case D2_GameVersion_k1_13ABeta:
    case D2_GameVersion_k1_13C:
    case D2_GameVersion_k1_13D:
    case D2_GameVersion_kClassic1_14A:
    case D2_GameVersion_kLod1_14A:
    case D2_GameVersion_kClassic1_14B:
    case D2_GameVersion_kClassic1_14C:
    case D2_GameVersion_kLod1_14B:
    case D2_GameVersion_kLod1_14C:
    case D2_GameVersion_kClassic1_14D:
    case D2_GameVersion_kLod1_14D: {
      D2GFX_RemoveInstanceCheckPatch_1_00_Remove(patch->patch.ptr_1_00);
      return;
    }
  }
}
