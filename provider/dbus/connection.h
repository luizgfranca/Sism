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

// REFERENCE DOCUMENTATION: https://www.freedesktop.org/wiki/Software/systemd/dbus/

#pragma once

#include <sdbus-c++/IConnection.h>

namespace provider::dbus {
    class DBusConnection {
    private:
        std::unique_ptr<sdbus::IConnection> m_connection;
        
        DBusConnection() {
            m_connection = sdbus::createSystemBusConnection();
        }

    public:
        static DBusConnection& instance() {
            static DBusConnection connection;
            return connection;
        }

        sdbus::IConnection& get_system_bus_connection() { return (*m_connection); }

        DBusConnection(DBusConnection const&) = delete;
        void operator=(DBusConnection const&) = delete;
    };
}