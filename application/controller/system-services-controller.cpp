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


#include "system-services-controller.h"


using namespace application::controller;


void SystemServicesController::refresh() {
    m_services = provider::systemd::Unit::filter_by_type(m_manager.get_services_list(), "service");
    provider::systemd::Unit::sort_by_name_inplace(m_services);
}

void SystemServicesController::start(const provider::systemd::Unit& service) {
    m_manager.start_service(service);
}

void SystemServicesController::stop(const provider::systemd::Unit& service) {
    m_manager.stop_service(service);
}

void SystemServicesController::restart(const provider::systemd::Unit& service) {
    m_manager.restart_service(service);
}

std::shared_ptr<std::vector<provider::systemd::Unit>> SystemServicesController::get_services() {
    if(!m_services) {
        refresh();
    }

    return m_services;
}