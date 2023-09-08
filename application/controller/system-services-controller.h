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