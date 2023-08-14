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

#include "../client/dbus/systemd/systemd-manager.h"
#include <memory>
#include <mutex>

namespace application {
    class State { 
        client::dbus::systemd::SystemdManager* m_systemd_manager;
        client::dbus::systemd::list_units_response_t m_units_list;
        
        std::mutex m_mutation_lock;

        void load();
        void sort_units();
    public:
        State(client::dbus::systemd::SystemdManager& systemd_manager);
        void refresh();
        client::dbus::systemd::list_units_response_t& get_units_list();
        client::dbus::systemd::list_units_response_t& get_services_list();
    };
}
