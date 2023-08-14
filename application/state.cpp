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

#include "state.h"
#include <cassert>
#include <memory>

using namespace application;


void State::load() {
    assert(this->m_systemd_manager != nullptr);
    this->m_units_list = this->m_systemd_manager->list_units();
}

State::State(client::dbus::systemd::SystemdManager& systemd_manager) {
    this->m_systemd_manager = &systemd_manager;
    this->load();
}

void State::refresh() {
    this->load();
}

client::dbus::systemd::list_units_response_t& State::get_units_list() {
    return this->m_units_list;
}

client::dbus::systemd::list_units_response_t& State::get_services_list() {
    client::dbus::systemd::list_units_response_t* services_list = new client::dbus::systemd::list_units_response_t;

     for(auto unit : get_units_list()) {
       if(unit.get<0>().ends_with(".service")) {
         services_list->push_back(unit);
       }
     }

     return *services_list;
}