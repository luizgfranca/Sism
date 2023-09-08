#pragma once

#include "controller//system-services-controller.h"
#include "glibmm/refptr.h"
#include "gtkmm/application.h"

namespace application {

    const std::string APPLICATION_ID = "io.github.luizgfranca.sism";

    class SismApplication {
        // BOILERPLATE
        int m_argc;
        char** m_argv;
        Glib::RefPtr<Gtk::Application> m_gtk_application;

        // LOGIC
        controller::SystemServicesController m_system_services_controller;
    public:
        SismApplication(int argc, char** argv);

        controller::SystemServicesController& system_services_controller();

        void run();
    };
}

