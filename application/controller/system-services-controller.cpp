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