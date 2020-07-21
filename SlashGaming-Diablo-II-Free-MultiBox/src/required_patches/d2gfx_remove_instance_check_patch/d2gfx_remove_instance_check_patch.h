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

#ifndef SGD2FMB_REQUIRED_PATCHES_D2GFX_REMOVE_INSTANCE_CHECK_PATCH_D2GFX_REMOVE_INSTANCE_CHECK_PATCH_H_
#define SGD2FMB_REQUIRED_PATCHES_D2GFX_REMOVE_INSTANCE_CHECK_PATCH_D2GFX_REMOVE_INSTANCE_CHECK_PATCH_H_

#include <sgd2mapi.h>

struct MAPI_GamePatch* SGD2FMB_D2GFX_RemoveInstanceCheckPatch_Init(
    struct MAPI_GamePatch* d2gfx_remove_instance_check_patch
);

void SGD2FMB_D2GFX_RemoveInstanceCheckPatch_Deinit(
    struct MAPI_GamePatch* d2gfx_remove_instance_check_patch
);

#endif /* SGD2FMB_REQUIRED_PATCHES_D2GFX_REMOVE_INSTANCE_CHECK_PATCH_D2GFX_REMOVE_INSTANCE_CHECK_PATCH_H_ */
