#pragma once

#include "gtkmm/box.h"
#include "gtkmm/frame.h"
#include "gtkmm/label.h"
#include "gtkmm/listbox.h"
#include "gtkmm/switch.h"
#include "gtkmm/window.h"
#include "../title-header/title-header.h"

#include "../../../controller/system-services-controller.h"
#include "../property-value-list-row/property-value-list-row.h"
#include <functional>

namespace application::ui::component {
    class ServiceDetailsSection : public Gtk::Box{
    private:
        TitleHeader m_serviceproperty_title;
        Gtk::Label m_serviceproperty_description;

        Gtk::Frame m_property_list_frame;
        Gtk::ListBox m_property_listbox;
        PropertyValueListRow<std::string, Gtk::Label> m_serviceproperty_loaded{"Loaded", ""};
        PropertyValueListRow<std::string, Gtk::Label> m_serviceproperty_state{"State", ""};
        PropertyValueListRow<std::string, Gtk::Label> m_serviceproperty_definition_file_path{"Definition file", ""};
        
        Gtk::Label m_settings_subsection_title;
        Gtk::Frame m_settings_list_frame;
        Gtk::ListBox m_settings_listbox;
        PropertyValueListRow<bool, Gtk::Switch> m_setting_auto_start_on_system_startup{"Auto start on system startup", true};

        std::function<bool(void)> m_on_enable_unit_request;
        
        void setup_components();
        void setup_style();

        void configure();    
        
    public:
        ServiceDetailsSection();
        void set_service(provider::systemd::Unit& service_unit);
        void set_on_enable_unit_request(std::function<bool(void)> handler);

    };
}
