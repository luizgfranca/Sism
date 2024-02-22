#include "gtkmm/box.h"
#include "gtkmm/label.h"
#include <gtkmm.h>
#include <string>
#include "../../../../module/logger/logger.h"


namespace application::ui::component {

    template <typename ValueType, typename UIComponentType>
    class PropertyValueListRow : public Gtk::ListBoxRow {
        std::string m_property;
        ValueType m_value;

        Gtk::Box m_content_box;
        Gtk::Label m_property_label;
        UIComponentType m_value_widget;

        void setup_value_widget_signal_handlers() {}

        void setup_components() {
            set_child(m_content_box);
            m_content_box.append(m_property_label);
            m_content_box.append(m_value_widget);

            setup_value_widget_signal_handlers();
        }

        void setup_style() {
            set_activatable(false);
    
            m_content_box.set_hexpand(true);
            
            m_property_label.add_css_class("heading");
            m_property_label.set_halign(Gtk::Align::START);
            
            m_value_widget.set_halign(Gtk::Align::END);
            m_value_widget.set_hexpand(true);
        }

        void update_content() {
            m_property_label.set_text(m_property);
        }

        ValueType on_value_widget_interaction(ValueType new_input_value) {
            module::logger::debug("value_widget_interaction new_input_value={}", new_input_value);
            set_value(new_input_value);
            return new_input_value;
        }
    public:
        std::function<void(ValueType old_value,ValueType mew_value)> on_interaction;

        PropertyValueListRow(std::string initial_property_name, ValueType initial_value) {
            m_property = initial_property_name;
            m_value = initial_value;

            setup_components();
            setup_style();
            update_content();
        }

        void set_property_name(std::string property_name) {
            m_property = property_name;
            update_content();
        }

        void set_value(ValueType value) {
            m_value = value;
            update_content();
        }
    };
}