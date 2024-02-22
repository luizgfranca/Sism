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

#include "systemd-manager.h"
#include <algorithm>
#include <memory>
#include <sdbus-c++/IProxy.h>
#include <sdbus-c++/IConnection.h>
#include <sdbus-c++/sdbus-c++.h>
#include <vector>
#include "properties.h"
#include "interface-properties.h"
#include "method-names.h"

using namespace provider::dbus::systemd;

SystemdManager::SystemdManager() {
    auto connection = sdbus::createSystemBusConnection();
    
    this->proxy = sdbus::createProxy(
        std::move(connection),
        DESTINATION_NAME, 
        OBJECT_PATH
    );

    proxy->finishRegistration();
}

list_units_response_t SystemdManager::list_units() {
    list_units_response_t result;
    proxy->callMethod(manager::method::LIST_UNITS_METHOD)
        .onInterface(manager::INTERFACE_NAME)
        .storeResultsTo(result);

    return result;
}

list_unit_files_response_t SystemdManager::list_unit_files() {
    list_unit_files_response_t result;
    proxy->callMethod(manager::method::LIST_UNIT_FILES_METHOD)
        .onInterface(manager::INTERFACE_NAME)
        .storeResultsTo(result);

    return result;
}


void SystemdManager::stop_unit(std::string unit_name, UnitOperationMode mode) {
    sdbus::ObjectPath result;
    proxy->callMethod(manager::method::STOP_UNIT_METHOD)
        .onInterface(manager::INTERFACE_NAME)
        .withArguments(unit_name, to_string(mode))
        .storeResultsTo(result);
}


void SystemdManager::start_unit(std::string unit_name, UnitOperationMode mode) {
    sdbus::ObjectPath result;
    proxy->callMethod(manager::method::START_UNIT_METHOD)
        .onInterface(manager::INTERFACE_NAME)
        .withArguments(unit_name, to_string(mode))
        .storeResultsTo(result);
}

void SystemdManager::reload_or_restart_unit(std::string unit_name, UnitOperationMode mode) {
    sdbus::ObjectPath result;
    proxy->callMethod(manager::method::RELOAD_OR_RESTART_UNIT_METHOD)
        .onInterface(manager::INTERFACE_NAME)
        .withArguments(unit_name, to_string(mode))
        .storeResultsTo(result);
}

std::shared_ptr<std::vector<std::string>> SystemdManager::get_unit_paths_property() {
    return std::make_shared<std::vector<std::string>>(
        proxy->getProperty(manager::property_name::UNITS_PATH)
            .onInterface(manager::INTERFACE_NAME)
            .get<std::vector<std::string>>()
    );
}

std::shared_ptr<enable_unit_files_response_t> SystemdManager::enable_unit_files(
    std::vector<std::string>& unit_files, 
    bool runtime, 
    bool force
) {
    auto enable_unit_files_response = std::make_shared<enable_unit_files_response_t>();
    
    proxy->callMethod(manager::method::ENABLE_UNIT_FILES)
        .onInterface(manager::INTERFACE_NAME)
        .withArguments(unit_files, runtime, force)
        .storeResultsTo(
            enable_unit_files_response->carries_install_info, 
            enable_unit_files_response->changes
        );

    return enable_unit_files_response;
}