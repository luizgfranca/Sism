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
#include <cctype>
#include <memory>
#include <algorithm>
#include <string>
#include <cctype>

using namespace application;

// https://en.cppreference.com/w/cpp/string/byte/toupper
std::string str_toupper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), 
        [](unsigned char c){ return std::toupper(c); }
    );
    return s;
}

void State::sort_units() {
    
    std::sort(
        m_units_list.begin(), 
        m_units_list.end(),
        [](
            client::dbus::systemd::list_units_response_unit_t a, 
            client::dbus::systemd::list_units_response_unit_t b
        ) {
            return str_toupper(b.get<0>()) > str_toupper(a.get<0>());
        }
    );
}

void State::load() {
    assert(m_systemd_manager != nullptr);
    m_units_list = m_systemd_manager->list_units();
    sort_units();
}

State::State(client::dbus::systemd::SystemdManager& systemd_manager) {
    m_systemd_manager = &systemd_manager;
    m_mutation_lock.lock();
    load();
    m_mutation_lock.unlock();
}

void State::refresh() {
    m_mutation_lock.lock();
    load();
    m_mutation_lock.unlock();
}

client::dbus::systemd::list_units_response_t& State::get_units_list() {
    return m_units_list;
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