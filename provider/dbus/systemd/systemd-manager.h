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

// REFERENCE DOCUMENTATION: https://www.freedesktop.org/wiki/Software/systemd/dbus/

#pragma once

#include <memory>
#include <sdbus-c++/IProxy.h>
#include "dto/dto.h"

namespace provider::dbus::systemd {

    /*
     * TODO make this into an abstract class, and separate the implementation
     *      this will enable us to mock systemd behavior to build tests
    */
    class SystemdManager {
        std::unique_ptr<sdbus::IProxy> proxy;
    public:
        SystemdManager();

        /*
         * Note that units may be known by multiple names at the same name, 
         * and hence there might be more unit names loaded than actual units behind them. 
         * TODO: identify this situation and present it to the user
        */

        std::shared_ptr<std::vector<std::string>> get_unit_paths_property();

        list_units_response_t list_units();
        list_unit_files_response_t list_unit_files();

        void stop_unit(std::string unit_name, UnitOperationMode mode);
        void start_unit(std::string unit_name, UnitOperationMode mode);
        void reload_or_restart_unit(std::string unit_name, UnitOperationMode mode);
    };
}