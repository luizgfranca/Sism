#include "service-details-section.h"
#include "gtkmm/builder.h"

using namespace application::ui::component;

void ServiceDetailsSection::configure() {
    set_orientation(Gtk::Orientation::VERTICAL);
    append(*(new component::ServiceProperty("Service details", "")));
    append(m_serviceproperty_title);
    append(m_serviceproperty_description);
    append(m_serviceproperty_loaded);
    append(m_serviceproperty_state);
    append(m_serviceproperty_followed);
    append(m_serviceproperty_object_path);
    append(*(new component::ServiceProperty("", "")));
    append(*(new component::ServiceProperty("Job currently processing", "")));
    append(m_serviceproperty_job_type);
    append(m_serviceproperty_job_object_path);
}

ServiceDetailsSection::ServiceDetailsSection() {
    configure();
}

void ServiceDetailsSection::set_service(provider::systemd::Unit service_unit) {
    
    m_serviceproperty_title.set_value(service_unit.name);
    m_serviceproperty_description.set_value(service_unit.description);
    m_serviceproperty_loaded.set_value(service_unit.load_state);
    m_serviceproperty_state.set_value(service_unit.active_state + " / " + service_unit.sub_state);
    m_serviceproperty_followed.set_value(service_unit.follows);
    m_serviceproperty_object_path.set_value(service_unit.object_path);
    
    if(!service_unit.has_running_job()) {
        m_serviceproperty_job_type.set_visible(false);
        m_serviceproperty_job_object_path.set_visible(false);
    } else {
        m_serviceproperty_job_type.set_visible(true);
        m_serviceproperty_job_object_path.set_visible(true);
        m_serviceproperty_job_type.set_value(service_unit.get_running_job()->name);
        m_serviceproperty_job_object_path.set_value(service_unit.get_running_job()->path);
    }
}