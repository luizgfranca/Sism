#include "systemd-provider.h"
#include <iostream>
#include <memory>

using namespace provider::systemd;

SystemdProvider::SystemdProvider() {
    m_dbus_systemd_manager_interface = std::make_unique<dbus::systemd::SystemdManager>();
}

void SystemdProvider::start_unit(const Unit& unit) {
    m_dbus_systemd_manager_interface->start_unit(
        unit.name, 
        provider::dbus::systemd::dto::UnitOperationMode::REPLACE
    );
}

void SystemdProvider::stop_unit(const Unit& unit) {
    m_dbus_systemd_manager_interface->stop_unit(
        unit.name, 
        provider::dbus::systemd::dto::UnitOperationMode::REPLACE
    );
}

void SystemdProvider::reload_or_restart_unit(const Unit& unit) {
    m_dbus_systemd_manager_interface->reload_or_restart_unit(
        unit.name, 
        provider::dbus::systemd::dto::UnitOperationMode::REPLACE
    );
}

std::unique_ptr<std::vector<Unit>> SystemdProvider::list_units() {
    auto response = m_dbus_systemd_manager_interface->list_units();   
    return std::move(Unit::from_dbus_list_units_response(response));
}