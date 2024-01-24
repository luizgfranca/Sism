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
#include <cstdlib>
#include <iostream>
#include <sdbus-c++/IProxy.h>
#include <string>
#include <vector>
#include "dto/unit-operation-mode.h"
#include "properties.h"
#include "interface-properties.h"
#include "method-names.h"

#include <systemd/sd-bus.h>

#include <stdio.h>

// from example in reference 
// https://www.freedesktop.org/software/systemd/man/latest/sd_bus_call_method.html#
#define _cleanup_(f) __attribute__((cleanup(f)))

using namespace provider::dbus::systemd;

void log_sd_bus_call(
    const char * method_name,
    const char * destination,
    const char * path,
    const char * interface,
    const char * member,
    std::vector<const char *>* params
) {
    printf(
        "%s(\n  %s,\n  %s,\n  %s,\n  %s,\n",
        method_name,
        destination,
        path,
        interface,
        member
    );
    for(auto param : *params) {
        printf("    %s,\n", param);
    }
    printf(")\n");
}

SystemdManager::SystemdManager() {
    this->proxy = sdbus::createProxy(
        DESTINATION_NAME, 
        OBJECT_PATH
    );

    auto response = sd_bus_open_system(&m_sd_bus_connection);
    if(response < 0) {
        std::cout << "ERROR INSTANTIATING DBUS\n";
    } else {
        std::cout << "SUCCESS INSTANTIATING DBUS\n";
    }

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
    // i don't really know why these things are needed yet, but it is in the reference example
    // https://www.freedesktop.org/software/systemd/man/latest/sd_bus_call_method.html#
    _cleanup_(sd_bus_flush_close_unrefp) sd_bus *bus = NULL;
    _cleanup_(sd_bus_error_free) sd_bus_error error = SD_BUS_ERROR_NULL;
    _cleanup_(sd_bus_message_unrefp) sd_bus_message *reply = NULL;
    
    int result = -1;

    result = sd_bus_call_method(
        this->m_sd_bus_connection, 
        DESTINATION_NAME.c_str(), 
        OBJECT_PATH.c_str(), 
        manager::INTERFACE_NAME.c_str(), 
        manager::method::STOP_UNIT_METHOD.c_str(), 
        &error, 
        &reply, 
        "ss",
        unit_name.c_str(),
        to_string(mode).c_str()
    );

    log_sd_bus_call(
        "sd_bus_call_method", 
        DESTINATION_NAME.c_str(), 
        OBJECT_PATH.c_str(), 
        manager::INTERFACE_NAME.c_str(), 
        manager::method::STOP_UNIT_METHOD.c_str(), 
        new std::vector{unit_name.c_str(), to_string(mode).c_str()}
    );
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