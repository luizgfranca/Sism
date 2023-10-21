#pragma once

#include "gtkmm/box.h"
#include "gtkmm/frame.h"
#include "gtkmm/label.h"
#include "gtkmm/listbox.h"
#include "gtkmm/window.h"
#include "../title-header/title-header.h"

#include "../../../controller/system-services-controller.h"
#include "../property-value-list-row/property-value-list-row.h"

namespace application::ui::component {
    class ServiceDetailsSection : public Gtk::Box{
    private:
        TitleHeader m_serviceproperty_title;
        Gtk::Label m_serviceproperty_description;

        Gtk::Frame m_property_list_frame;
        Gtk::ListBox m_property_listbox;
        PropertyValueListRow m_serviceproperty_loaded = PropertyValueListRow("Loaded");
        PropertyValueListRow m_serviceproperty_state = PropertyValueListRow("State");
        PropertyValueListRow m_serviceproperty_definition_file_path = PropertyValueListRow("Definition file");
        
        void setup_components();
        void setup_style();

        void configure();    
        
    public:
        ServiceDetailsSection();
        void set_service(provider::systemd::Unit service_unit);
    };
}
