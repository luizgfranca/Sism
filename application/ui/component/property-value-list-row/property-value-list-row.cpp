#include "property-value-list-row.h"
#include "gtkmm/label.h"
#include "gtkmm/switch.h"
#include "sigc++/functors/mem_fun.h"

using namespace application::ui::component;

template <>
void PropertyValueListRow<std::string, Gtk::Label>::update_content() {
    m_property_label.set_text(m_property);
    m_value_widget.set_text(m_value);
}

template <>
void PropertyValueListRow<bool, Gtk::Switch>::update_content() {
    m_property_label.set_text(m_property);
    m_value_widget.set_state(m_value);
}

template <>
void PropertyValueListRow<bool, Gtk::Switch>::setup_value_widget_signal_handlers() {
    m_value_widget.signal_state_set()
        .connect(sigc::mem_fun(
                *this, 
                &PropertyValueListRow<bool, Gtk::Switch>::on_value_widget_interaction
            ), 
            false
        );
}