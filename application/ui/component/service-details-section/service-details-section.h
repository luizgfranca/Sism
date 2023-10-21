#pragma once

#include "gtkmm/box.h"
#include "gtkmm/label.h"
#include "gtkmm/window.h"
#include "../title-header/title-header.h"

#include "../../../controller/system-services-controller.h"

namespace application::ui::component {
    class ServiceDetailsSection : public Gtk::Box{
    private:
        TitleHeader m_serviceproperty_title;

        Gtk::Label m_serviceproperty_description;
        Gtk::Label m_serviceproperty_loaded;
        Gtk::Label m_serviceproperty_state;
        Gtk::Label m_serviceproperty_followed;
        Gtk::Label m_serviceproperty_object_path;
        Gtk::Label m_serviceproperty_job_type;
        Gtk::Label m_serviceproperty_job_object_path;

        void setup_components();
        void setup_style();

        void configure();    
        
    public:
        ServiceDetailsSection();
        void set_service(provider::systemd::Unit service_unit);
    };
}
