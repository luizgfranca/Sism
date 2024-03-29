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
#include "policykit-1-authority.h"
#include "unit.h"
#include <format>
#include <memory>
#include "../../module/logger/logger.h"

using namespace provider::systemd;

SystemdProvider::SystemdProvider() {
    m_dbus_systemd_manager_interface = std::make_unique<dbus::systemd::SystemdManager>();
    m_polkit_provider = std::make_unique<polkit::PolkitProvider>();
    m_unit_paths = m_dbus_systemd_manager_interface->get_unit_paths_property();

    module::logger::debug("loading unit paths");
    for(auto i : *m_unit_paths) {
        module::logger::debug("{}", i);
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

std::shared_ptr<std::vector<Unit>> SystemdProvider::list_loaded_or_once_loaded_units() {
    auto response = m_dbus_systemd_manager_interface->list_units();   
    return std::move(Unit::from_dbus_list_units_response(response));
}

std::shared_ptr<std::vector<Unit>> SystemdProvider::list_all_units() {
    auto list_units_response = m_dbus_systemd_manager_interface->list_units();
    auto list_unit_files_response = m_dbus_systemd_manager_interface->list_unit_files();
    
    return Unit::from_dbus_list_units_and_list_files_response(
        list_units_response,
        list_unit_files_response
    );
}

bool SystemdProvider::enable_unit(const Unit& unit) {
    if(unit.unit_file == nullptr) {
        return false;
    }

    auto is_authrized = m_polkit_provider->request_authorization(
        polkit::PolkitAction::SYSTEMD1_MANAGE_UNIT_FILES
    );

    if (!is_authrized) {
        return false;
    }

    std::vector<std::string> unit_file_name{unit.unit_file->complete_path};
    auto response = m_dbus_systemd_manager_interface->enable_unit_files(
        unit_file_name, 
        false, 
        false
    );

    module::logger::debug("enable unit result:");
    for(auto change : response->changes) {
        module::logger::debug("  changes=({}, {}, {})", change.get<0>(), change.get<1>(), change.get<2>());
    }

    return response->changes.size() > 0;
}

bool SystemdProvider::disable_unit(const Unit& unit) {
    if(unit.unit_file == nullptr) {
        return false;
    }

    auto is_authrized = m_polkit_provider->request_authorization(
        polkit::PolkitAction::SYSTEMD1_MANAGE_UNIT_FILES
    );

    if (!is_authrized) {
        return false;
    }

    std::vector<std::string> unit_file_name{unit.unit_file->name};
    auto response = m_dbus_systemd_manager_interface->disable_unit_files(
        unit_file_name, 
        false
    );

    module::logger::debug("enable unit result:");
    for(auto change : *response) {
        module::logger::debug("  changes=({}, {}, {})", change.get<0>(), change.get<1>(), change.get<2>());
    }

    return response->size() > 0;
}