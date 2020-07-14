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

#include "license.h"

#include <stddef.h>
#include <stdio.h>

static const char* kLicenseLines[] = {
    u8"SlashGaming Diablo II MultiBox Patch",
    u8"Copyright (C) 2019-2020  Mir Drualga",
    u8"",
    u8"This program is free software: you can redistribute it and/or modify",
    u8"it under the terms of the GNU Affero General Public License as published",
    u8"by the Free Software Foundation, either version 3 of the License, or",
    u8"(at your option) any later version.",
    u8"",
    u8"This program is distributed in the hope that it will be useful,",
    u8"but WITHOUT ANY WARRANTY; without even the implied warranty of",
    u8"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the",
    u8"GNU Affero General Public License for more details.",
    u8"",
    u8"You should have received a copy of the GNU Affero General Public License",
    u8"along with this program.  If not, see <http://www.gnu.org/licenses/>.",
    u8"",
    u8"Additional permissions under GNU Affero General Public License version 3",
    u8"section 7 have also been granted; please check the LICENSE file for more",
    u8"information."
};

enum {
  NUM_LICENSE_LINES = sizeof(kLicenseLines) / sizeof(kLicenseLines[0])
};

void PrintLicenseNotice() {
  for (size_t i = 0; i < NUM_LICENSE_LINES; i += 1) {
    printf("%s \n", kLicenseLines[i]);
  }
}
