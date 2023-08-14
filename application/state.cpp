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