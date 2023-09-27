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

#include "../../provider/systemd/systemd-provider.h"
#include <memory>

namespace module::services {

    // TODO: create service abstraction to be more platform agnostic
    class SystemServicesManager {
        provider::systemd::SystemdProvider m_systemd_provider;
    public:
        std::shared_ptr<std::vector<provider::systemd::Unit>> get_services_list();
        void start_service(const provider::systemd::Unit& service);
        void stop_service(const provider::systemd::Unit& service);
        void restart_service(const provider::systemd::Unit& service);
    };

}