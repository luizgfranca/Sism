#include "service-property.h"
#include "cairomm/fontoptions.h"
#include "gtkmm/cssprovider.h"
#include "gtkmm/enums.h"
#include <string>

using namespace component;

void ServiceProperty::configure() {
    auto text_size_provider = Gtk::CssProvider::create();
    text_size_provider->load_from_data("#label-name, #label-value{font-size: 1.2rem}");

    m_name_label.set_margin_start(10);
    m_name_label.set_margin_top(2);
    m_name_label.set_name("label-name");
    m_name_label.get_style_context()->add_provider(text_size_provider, 1);
    
    m_value_label.set_margin_start(10);
    m_value_label.set_margin_top(2);
    m_value_label.set_name("label-value");
    m_value_label.get_style_context()->add_provider(text_size_provider, 1);

    set_vexpand(false);

    append(m_name_label);
    append(m_value_label);
}

void ServiceProperty::set_name(std::string name) {
    m_name_label.set_markup("<b>" + name + "</b>");
}

void ServiceProperty::set_value(std::string value) {
    m_value_label.set_label(value);
}

ServiceProperty::ServiceProperty() {
    configure();
}

ServiceProperty::ServiceProperty(std::string name, std::string value) {
    configure();
    set_name(name);
    set_value(value);
}

