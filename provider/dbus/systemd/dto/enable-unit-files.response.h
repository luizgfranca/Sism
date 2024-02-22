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

#include <sdbus-c++/Types.h>
#include <vector>

namespace provider::dbus::systemd {

    typedef sdbus::Struct<
        std::string, 
        std::string, 
        std::string
    > enable_unit_files_response_changes_t;

    typedef struct enable_unit_files_response {
        bool carries_install_info;
        std::vector<enable_unit_files_response_changes_t> changes;
    } enable_unit_files_response_t;

}