#include "systemd-manager.h"
#include <sdbus-c++/IProxy.h>

using namespace client::dbus::systemd;

const char* DBUS_SYSTEMD_DESTINATION_NAME = "org.freedesktop.systemd1";
const char* DBUS_SYSTEMD_OBJECT_PATH = "/org/freedesktop/systemd1";
const char* DBUS_SYSTEMD_MANAGER_INTERFACE = "org.freedesktop.systemd1.Manager";

const char* DBUS_SYSTEMD_MANAGER_LIST_UNITS_METHOD = "ListUnits";
const char* DBUS_SYSTEMD_MANAGER_STOP_UNIT_METHOD = "StopUnit";
const char* DBUS_SYSTEMD_MANAGER_START_UNIT_METHOD = "StartUnit";

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
        .withArguments(unit_name, "replace")
        .storeResultsTo(result);
}


void SystemdManager::start_unit(std::string unit_name) {
    sdbus::ObjectPath result;
    proxy->callMethod(DBUS_SYSTEMD_MANAGER_START_UNIT_METHOD)
        .onInterface(DBUS_SYSTEMD_MANAGER_INTERFACE)
        .withArguments(unit_name, "replace")
        .storeResultsTo(result);
}