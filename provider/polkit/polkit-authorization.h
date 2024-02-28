/*
 *   SISM - Services manager for GNU/Linux based operating systems
 *   Copyright (C) 2024 Luiz Gustavo <luizgfc@proton.me>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Affero General Public License as
 *   published by the Free Software Foundation, either version 3 of the
 *   License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Affero General Public License for more details.
 *
 *   You should have received a copy of the GNU Affero General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#pragma once

#include <string>
#include <vector>



namespace provider::polkit {
    enum PolkitAction {
        SYSTEMD1_MANAGE_UNIT_FILES
    };

    const std::vector<std::string> action_id_strings = {
        "org.freedesktop.systemd1.manage-unit-files"
    };

    template <typename T>
    std::string to_string(T v) { return "none"; };

    template <>
    inline std::string to_string<PolkitAction>(PolkitAction action) {
        if(action >= action_id_strings.size()) {
            return "none";
        }

        return action_id_strings[action];
    };
};