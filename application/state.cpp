#include "state.h"
#include <memory>

using namespace application;


void State::load() {
    if(this->m_systemd_manager != nullptr) {
        this->m_units_list = this->m_systemd_manager->list_units();
    }
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