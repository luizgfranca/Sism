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
#include <sdbus-c++/IProxy.h>

using namespace client::dbus::systemd;

const char* DBUS_SYSTEMD_DESTINATION_NAME = "org.freedesktop.systemd1";
const char* DBUS_SYSTEMD_OBJECT_PATH = "/org/freedesktop/systemd1";
const char* DBUS_SYSTEMD_MANAGER_INTERFACE = "org.freedesktop.systemd1.Manager";

const char* DBUS_SYSTEMD_MANAGER_LIST_UNITS_METHOD = "ListUnits";
const char* DBUS_SYSTEMD_MANAGER_STOP_UNIT_METHOD = "StopUnit";
const char* DBUS_SYSTEMD_MANAGER_START_UNIT_METHOD = "StartUnit";
const char* DBUS_SYSTEMD_MANAGER_RELOAD_OR_RESTART_UNIT_METHOD = "ReloadOrRestartUnit";

const char* DEFAULT_MODE = "replace";

SystemdManager::SystemdManager() {
    this->proxy = sdbus::createProxy(
        DBUS_SYSTEMD_DESTINATION_NAME, 
        DBUS_SYSTEMD_OBJECT_PATH
    );

    proxy->finishRegistration();
}

list_units_response_t SystemdManager::list_units() {
    list_units_response_t result;
    proxy->callMethod(DBUS_SYSTEMD_MANAGER_LIST_UNITS_METHOD)
        .onInterface(DBUS_SYSTEMD_MANAGER_INTERFACE)
        .storeResultsTo(result);

    return result;
}

void SystemdManager::stop_unit(std::string unit_name) {
    sdbus::ObjectPath result;
    proxy->callMethod(DBUS_SYSTEMD_MANAGER_STOP_UNIT_METHOD)
        .onInterface(DBUS_SYSTEMD_MANAGER_INTERFACE)
        .withArguments(unit_name, DEFAULT_MODE)
        .storeResultsTo(result);
}


void SystemdManager::start_unit(std::string unit_name) {
    sdbus::ObjectPath result;
    proxy->callMethod(DBUS_SYSTEMD_MANAGER_START_UNIT_METHOD)
        .onInterface(DBUS_SYSTEMD_MANAGER_INTERFACE)
        .withArguments(unit_name, DEFAULT_MODE)
        .storeResultsTo(result);
}

void SystemdManager::reload_or_restart_unit(std::string unit_name) {
    sdbus::ObjectPath result;
    proxy->callMethod(DBUS_SYSTEMD_MANAGER_RELOAD_OR_RESTART_UNIT_METHOD)
        .onInterface(DBUS_SYSTEMD_MANAGER_INTERFACE)
        .withArguments(unit_name, DEFAULT_MODE)
        .storeResultsTo(result);
}