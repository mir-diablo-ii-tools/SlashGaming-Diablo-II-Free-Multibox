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

#include "required_patches.h"

#include "d2gfx_remove_instance_check_patch/d2gfx_remove_instance_check_patch.h"

struct SGD2FMB_RequiredPatches* SGD2FMB_RequiredPatches_Init(
    struct SGD2FMB_RequiredPatches* required_patches
) {
  required_patches->is_applied = false;

  SGD2FMB_D2GFX_RemoveInstanceCheckPatch_Init(
      &required_patches->d2gfx_remove_instance_check_patch
  );
}

void SGD2FMB_RequiredPatches_Deinit(
    struct SGD2FMB_RequiredPatches* required_patches
) {
  SGD2FMB_D2GFX_RemoveInstanceCheckPatch_Deinit(
      &required_patches->d2gfx_remove_instance_check_patch
  );

  SGD2FMB_RequiredPatches_Remove(required_patches);
}

void SGD2FMB_RequiredPatches_Apply(
    struct SGD2FMB_RequiredPatches* required_patches
) {
  if (required_patches->is_applied) {
    return;
  }

  MAPI_GamePatch_Apply(&required_patches->d2gfx_remove_instance_check_patch);

  required_patches->is_applied = true;
}

void SGD2FMB_RequiredPatches_Remove(
    struct SGD2FMB_RequiredPatches* required_patches
) {
  if (!required_patches->is_applied) {
    return;
  }

  MAPI_GamePatch_Remove(&required_patches->d2gfx_remove_instance_check_patch);

  required_patches->is_applied = false;
}
