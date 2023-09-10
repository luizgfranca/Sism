/*
 *   SISM - Services manager for GNU/Linux based operating systems
 *   Copyright (C) 2023 Luiz Gustavo <luizgfc@proton.me>
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

#include <cstdint>
#include <string>

namespace provider::dbus::systemd::dto {
    enum UnitOperationMode : uint8_t {
        // the call will start the unit and its dependencies, 
        // possibly replacing already queued jobs that conflict with this. 
        REPLACE, 

        // the call will start the unit and its dependencies, 
        // but will fail if this would change an already queued job.
        FAIL, 

        // the call will start the unit in question and terminate all units that aren't dependencies of it. 
        ISOLATE, 
        
        //It is not recommended to make use of the latter two options
        IGNORE_DEPENDENCIES, // it will start a unit but ignore all its dependencies.
        IGNORE_REQUIREMENTS, //  it will start a unit but only ignore the requirement dependencies. 
    };

    std::string to_string(UnitOperationMode mode);
}