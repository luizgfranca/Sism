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


#include <string>
namespace provider::dbus::systemd::manager::method {
    const std::string LIST_UNITS_METHOD = "ListUnits";
    const std::string STOP_UNIT_METHOD = "StopUnit";
    const std::string START_UNIT_METHOD = "StartUnit";
    const std::string RELOAD_OR_RESTART_UNIT_METHOD = "ReloadOrRestartUnit";
}