#include "property-value-list-row.h"
#include "gtkmm/label.h"
#include "gtkmm/switch.h"

using namespace application::ui::component;

template <>
void PropertyValueListRow<std::string, Gtk::Label>::update_content() {
    m_property_label.set_text(m_property);
    m_value_widget.set_text(m_value);
}

template <>
void PropertyValueListRow<bool, Gtk::Switch>::update_content() {
    m_property_label.set_text(m_property);
    m_value_widget.set_active(m_value);
}