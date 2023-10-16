#pragma once

#include "gtkmm/box.h"
#include "gtkmm/window.h"
#include "../../../controller/system-services-controller.h"
#include "../service-property/service-property.h"

namespace application::ui::component {
    class ServiceDetailsSection : public Gtk::Box{
    private:
        component::ServiceProperty m_serviceproperty_title = component::ServiceProperty("Title:", "example.service");
        component::ServiceProperty m_serviceproperty_description = component::ServiceProperty("Description:", "Example service description");
        component::ServiceProperty m_serviceproperty_loaded = component::ServiceProperty("Loaded:", "loaded");
        component::ServiceProperty m_serviceproperty_state = component::ServiceProperty("State:", "running/start");
        component::ServiceProperty m_serviceproperty_followed = component::ServiceProperty("Following:", "other.service");
        component::ServiceProperty m_serviceproperty_object_path = component::ServiceProperty("Object path:", "?");
        
        component::ServiceProperty m_serviceproperty_job_type = component::ServiceProperty("Type:", "type");
        component::ServiceProperty m_serviceproperty_job_object_path = component::ServiceProperty("Object Path:", "type");

        void configure();    
        
    public:
        ServiceDetailsSection();
        void set_service(provider::systemd::Unit service_unit);
    };
}
