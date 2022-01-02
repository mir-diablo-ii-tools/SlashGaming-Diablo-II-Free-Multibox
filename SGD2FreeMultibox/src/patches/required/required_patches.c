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

#include "required_patches.h"

struct RequiredPatches RequiredPatches_Init(void) {
  struct RequiredPatches required_patches;

  required_patches.d2gfx_remove_instance_check_patch =
      D2GFX_RemoveInstanceCheckPatch_Init();

  return required_patches;
}

void RequiredPatches_Deinit(
    struct RequiredPatches* required_patches
) {
  D2GFX_RemoveInstanceCheckPatch_Deinit(
      &required_patches->d2gfx_remove_instance_check_patch
  );
}

void RequiredPatches_Apply(
    struct RequiredPatches* required_patches
) {
  D2GFX_RemoveInstanceCheckPatch_Apply(
      &required_patches->d2gfx_remove_instance_check_patch
  );
}

void RequiredPatches_Remove(
    struct RequiredPatches* required_patches
) {
  D2GFX_RemoveInstanceCheckPatch_Remove(
      &required_patches->d2gfx_remove_instance_check_patch
  );
}
