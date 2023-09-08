#pragma once

#include <memory>
#include <vector>
#include "unit.h"
#include "../dbus/systemd/systemd-manager.h"

namespace provider::systemd {
    class SystemdProvider {
        std::unique_ptr<dbus::systemd::SystemdManager> m_dbus_systemd_manager_interface;

    public:
        // TODO use dependency injection for Systemd interfaces
        SystemdProvider();

        std::unique_ptr<std::vector<Unit>> list_units();
        void start_unit(const Unit& unit);
        void stop_unit(const Unit& unit);
        void reload_or_restart_unit(const Unit& unit);
    };
}

