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


#include "systemd-provider.h"
#include <format>
#include <iostream>
#include <memory>

using namespace provider::systemd;

SystemdProvider::SystemdProvider() {
    m_dbus_systemd_manager_interface = std::make_unique<dbus::systemd::SystemdManager>();
    m_unit_paths = m_dbus_systemd_manager_interface->get_unit_paths_property();

    std::cout << "loading unit paths\n";
    for(auto i : *m_unit_paths) {
        std::cout << std::format("{}\n", i);
    }
}

void SystemdProvider::start_unit(const Unit& unit) {
    m_dbus_systemd_manager_interface->start_unit(
        unit.name, 
        provider::dbus::systemd::UnitOperationMode::REPLACE
    );
}

void SystemdProvider::stop_unit(const Unit& unit) {
    m_dbus_systemd_manager_interface->stop_unit(
        unit.name, 
        provider::dbus::systemd::UnitOperationMode::REPLACE
    );
}

void SystemdProvider::reload_or_restart_unit(const Unit& unit) {
    m_dbus_systemd_manager_interface->reload_or_restart_unit(
        unit.name, 
        provider::dbus::systemd::UnitOperationMode::REPLACE
    );
}

std::unique_ptr<std::vector<Unit>> SystemdProvider::list_units() {
    auto response = m_dbus_systemd_manager_interface->list_units();   
    return std::move(Unit::from_dbus_list_units_response(response));
}