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


#pragma once

#include "../module//services/system-services-manager.h"

namespace application::controller {
    class SystemServicesController {
        // TOOD: Use dependency injection
        module::services::SystemServicesManager m_manager;

        std::shared_ptr<std::vector<provider::systemd::Unit>> m_services;

    public:
        void refresh();
        std::shared_ptr<std::vector<provider::systemd::Unit>> get_services();
        void start(const provider::systemd::Unit& service);
        void stop(const provider::systemd::Unit& service);
        void restart(const provider::systemd::Unit& service);
    };
}