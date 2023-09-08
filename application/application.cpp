#include "application.h"
#include "ui/main-window.h"

using namespace application;

SismApplication::SismApplication(int argc, char** argv) {
    m_argc = argc;
    m_argv = argv;

    m_gtk_application = Gtk::Application::create(APPLICATION_ID);
}

void SismApplication::run() {
    m_gtk_application->make_window_and_run<ui::MainWindow>(m_argc, m_argv, this);
}

controller::SystemServicesController& SismApplication::system_services_controller() {
    return m_system_services_controller;
}